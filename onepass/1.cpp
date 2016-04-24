#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <map>
#include <vector>
#include <string.h>
#define input "source.txt"
#define output "out.txt"
using namespace std;
 
string label, opcode, operand;
string name;
ifstream fin(input);
ofstream fout(output);
string outl;
stringstream ss,s, ss_addr;

string hex_value;
string mod[10];
int mod_size=0;
int t_size=0;

string opc ,v, line;



int address = 0;

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
	
	stringstream st;
	st << hex << add;
	return st.str();
	
}
void onepass(){
	readLine();
	if(opcode == "START"){
		ss<< hex << operand;
		ss >> address;
		outl = "H^" + label + "^00" + operand + "^00";
		writeLine();
		//cout<< outl<<"\n";
	}
	outl = "T^00" + getHexaddress(address) + "^00";
	while(opcode!="END"){
		readLine();
		itr = symtab.find(operand);
		cout << " "<< getHexaddress(address)<< " "<< label << " "<< opcode<< " " << operand<<"\n";
		if(itr!=symtab.end()){
			
			(itr->second).frwd_list.push_back(address);
		
		}
		else{
			
			symtab.insert(pair<string,Symbol>(operand,Symbol(operand,0)));
			itr = symtab.find(operand);
			(itr->second).frwd_list.push_back(address);
				
		}
		if(optab.find(opcode)!= optab.end()){
			outl = outl + "^" + optab.find(opcode)->second+"0000"; t_size = t_size+3;
		}
		else if(opcode == "WORD" || opcode == "BYTE"){
			t_size = t_size+3;
			outl = outl + "^"+ "0000"+operand;
		}
		if(label!="\t"){
			Symbol sym = (symtab.find(label))->second;
			for(int i=0;i< (sym.frwd_list).size(); i++)
				mod[mod_size] = "T^00" + getHexaddress(sym.frwd_list[i]+1)+ "^04^" + getHexaddress(address);
			mod_size++;
		}
		if(optab.find(opcode)!= optab.end()) address+=3;
		else if(opcode=="WORD") address+=3;
		else if(opcode=="BYTE") address+= operand.length();
		else if(opcode=="RESW") address+= 3*atoi(operand.c_str());
		else if(opcode=="RESB") address+= atoi(operand.c_str());
		else if(opcode=="END") 	{myreplace(outl,"^00^","^"+getHexaddress(t_size)+"^"); writeLine(); t_size = 0;}
		else cout<<"ERROR CODE";
	}
	for(int i=0;i<mod_size;i++)
		fout<< mod[i]<<"\n";
	fout<< "E^"<< ss.str()<<"\n";
	
}
int main(){
	fillOptab();	
	onepass();
	fin.close();
	fout.close();
	cout << hex << "E";
	return 0;
}