#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <vector>
#include <map>
#include <string>
#include <stdio.h>
#define input "macro.txt"
#define output "macro_output.txt"
#define max_size 69
using namespace std;

ifstream fin(input);
ofstream fout(output);
string line;
string opc="START";
string l,opr;
string name,defline;
bool expanding;
bool firstflag;   //label for first line of expanded macro
int i;
int not_found = 2000;			//string not found returns 18446744073709551615

class argList{
public:
	string pos;
	string param;
	string arg;
	argList(int a,string param){
		stringstream ss;
		ss << a;
		pos = "?"+ss.str();
		this->param = param;
	}
};
class nametab{
public:
	string name;
	int macrolabel;
	vector<string> deflines;
	map<int,argList> argtab;
	nametab(string name,int macrolabel= 0x00){
		this->name = name;
	}
};

map<string, nametab> namtab;
map<string,nametab>::iterator itr; 						//iteraror fot namtab
map<int,argList>::iterator dummy;						//iterator for argtab

void macroprocessor(); // frwd ref
void processline();
void define();

void fillArgtab(string s,string delimiter){
	int i = 1;
	size_t last = 0; size_t next = 0; 
	while ((next = s.find(delimiter, last)) != string::npos) {
		map<int,argList>::iterator dummy=itr->second.argtab.find(i); 
		dummy->second.arg = s.substr(last, next-last); 
		i++;
		last = next + 1; 
	}
	map<int,argList>::iterator dummy=itr->second.argtab.find(i); 
	dummy->second.arg  = s.substr(last);
}
void fillParams(string s,string delimiter){
	size_t last = 0; size_t next = 0; 
	int i=1;
	while ((next = s.find(delimiter, last)) != string::npos) { 
		(itr->second).argtab.insert(pair<int,argList>(i,argList(i,s.substr(last, next-last))));
		i++;
		last = next + 1; 
	} 
		(itr->second).argtab.insert(pair<int,argList>(i,argList(i,s.substr(last))));
}
string myreplace(string &s,const string &toReplace,const string &replaceWith)
{
	if(s.find(toReplace)>not_found)
    	return s;
    return(s.replace(s.find(toReplace), toReplace.length(), replaceWith));
}
void read(){
	getline(fin,line);
		while(line[0] == ';')
			getline(fin,line);
		istringstream ss(line);
		if(line[0]=='\t'){
			l = '\t';
			ss>>opc>>opr;
		}
		else
			ss>>l>>opc>>opr;
}
void getline(){

	if(expanding){
		line = itr->second.deflines[i];
		itr = namtab.find(name);					//substitute arguments from ARGTAB 
		for (dummy=itr->second.argtab.begin(); dummy!=itr->second.argtab.end(); ++dummy)
			myreplace(line,dummy->second.pos,dummy->second.arg);
	}
	else
		read();
}
void expand(){

	expanding = true;
	itr = namtab.find(opc);
	name = opc;
	string firstLine = itr->second.deflines[0];
	fillArgtab(opr,","); 								// seprate arguments from macro list and fill ARGTAB;
	fout<<"."<<line<<endl;  //write invocation as comment in expanded file
	
	int size =  itr->second.deflines.size();
	size--;
	firstflag =true;
	for (i = 1; i < size; ++i){
		getline();
		processline();
	}
   	expanding = false;
}
void processline(){

	itr = namtab.find(opc);		//search namtab for opcode ,if found expand
	if(itr!= namtab.end() && !expanding) 
		expand();
	else if(opc=="MACRO")
		define();
	else {
		if(firstflag){
			firstflag = false;
			line=l+line; 
		}
		fout<<line<<endl;
	}
}
void define(){
	namtab.insert(pair<string,nametab>(l,nametab(l)));  //enter name of macro into NAMTAB
	itr = namtab.find(l);
	(itr->second).deflines.push_back(line);				//insert macro prototye into DEFTAB
	fillParams(opr,",");
	int level=1;
	while(level>0){
		getline();
		for (dummy=itr->second.argtab.begin(); dummy!=itr->second.argtab.end(); ++dummy)
			myreplace(line,dummy->second.param,dummy->second.pos);
		itr->second.deflines.push_back(line);
		if(opc=="MACRO")
			level++;
		else if(opc=="MEND")
			level--;
	}
}
void macroprocessor(){
		expanding = false;
		while(opc!="END"){
			getline();
			processline();
		}
}
int main(){
	macroprocessor();
	for (itr = namtab.begin();itr!=namtab.end();itr++){
		fout << endl <<endl;
		fout<<"NAMTAB OF MACRO : " << itr->first <<  endl;
		fout<<"DEFTAB OF MACRO : " << endl;
		for (int i = 0; i < itr->second.deflines.size(); ++i)
			fout<< itr->second.deflines[i]<<endl;
	}
	fin.close();
	fout.close();
	return 0;
}