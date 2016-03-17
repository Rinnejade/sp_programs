#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <map>
#include <vector>
#include <string.h>
#define input "source.txt"
#define output "2out.txt"
#define intermediate "intermediate.txt"
using namespace std;
 
string label, opcode, operand;
string name;
ifstream fin(input);
ofstream fout(output);
fstream inter(intermediate);
string outl;
string objcode;
stringstream ss,s, ss_addr;

string hex_add;
string mod[10];
int mod_size=0;
int t_size=0;
int init;
string opc ,v, line;

int address = 0;
class Line{
public:
	string locctr;
	string label;
	string opcode;
	string operand;
	string objcode;
	Line(string locctr,string label,string opcode,string operand){
		this->locctr = locctr;
		this->label = label;
		this->opcode = opcode;
		this->operand = operand;
	}
};
class Symbol{
public:
	string name;
	int value;
	vector<int> frwd_list;
	
	Symbol(string name,int value){
		this->value = value;
		this->name = name;	
	}	
};

map<string,string> optab;
map<string,Symbol> symtab;
map<string,Symbol>:: iterator itr;
vector<Line> lines;

void fillOptab(){
	ifstream f("optab.txt");
	while(f){
		f >> opc >> v;
		optab[opc] = v;
	}
}
void readLine(){
	getline(fin,line);
	istringstream s(line);
	if(line[0]=='\t'){
		label = '\t';
		s>>opcode>>operand;
	}
	else
		s>>label>>opcode>>operand;
}

void writeLine(){
	fout<< outl<<"\n";
}
string myreplace(string &s,const string &toReplace,const string &replaceWith)
{
    return(s.replace(s.find(toReplace), toReplace.length(), replaceWith));
}
string getHexaddress(int add){
	string hex_addr;
	stringstream st;
	st << hex << add;
	hex_addr = st.str();
	return hex_addr;
}
void passone(){
	readLine();
	if(opcode == "START"){
		ss<< hex << operand;
		ss >> address;
		init = address;
		outl = "H^" + label + "^00" + operand;
		//writeLine();
		//cout<< outl<<"\n";
	}
	while(opcode!="END"){
		readLine();
		itr = symtab.find(label);
		inter << " "<< getHexaddress(address)<< " "<< label << " "<< opcode<< " " << operand<<"\n";
		Line ln(getHexaddress(address),label,opcode,operand);
		lines.push_back(ln);
		if(itr==symtab.end())
			symtab.insert(pair<string,Symbol>(label,Symbol(label,address)));
		if(optab.find(opcode)!= optab.end()) address+=3;
		else if(opcode=="WORD") address+=3;
		else if(opcode=="BYTE") address+= operand.length();
		else if(opcode=="RESW") address+= 3*atoi(operand.c_str());
		else if(opcode=="RESB") address+= atoi(operand.c_str());
		else if(opcode=="END") 	{}
		else cout<<"ERROR CODE";
	}
	init = address-init;
}
void passtwo(){
	outl = outl +"^"+ getHexaddress(init);
	writeLine();
	outl = "T^00" + lines[0].locctr +"^"+ getHexaddress(3*(lines.size()-2)); 
	for(int i =0;i< lines.size() ; i++){
		if(optab.find(lines[i].opcode)!= optab.end())
			objcode = optab.find(lines[i].opcode)->second;
		else if(lines[i].opcode == "WORD" || lines[i].opcode == "BYTE"){
			objcode = "0000"+ lines[i].operand ;
			outl = outl + "^"+ objcode;
		}
		if(symtab.find(lines[i].operand)!=symtab.end()){
			objcode = objcode + getHexaddress(symtab.find(lines[i].operand)->second.value);
			outl = outl + "^"+ objcode;
		}
		objcode ="";
	}	
	writeLine();
	outl = "E^" + ss.str();
	writeLine();
}
int main(){
	fillOptab();	
	passone();
	passtwo();
	fin.close();
	fout.close();
	inter.close();
	return 0;
}