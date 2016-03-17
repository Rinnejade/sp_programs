#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <vector>
#include <map>
#include <string>
#define input "source.txt"
#define max_size 69
using namespace std;


class Line{
public:
	int locctr;
	string label;
	string opcode;
	string operand;
	string objcode;

	Line(int locctr,string label,string opcode,string operand,string objcode){
		this->label = label;
		this->locctr = locctr;
		this->opcode = opcode;
		this->operand = operand;
		this->objcode = objcode;
	}
};

class Symbol{
public:
	string name;
	int value;
	vector<int> frwd_ref;

	Symbol(string name,int value){
		this->name = name;
		this->value = value;
	}
};

class TextRecord{
public:
	int init;
	int size;
	vector<string> obj;
	TextRecord(int init,int size){
		this->size = size;
		this->init = init;
	}
};
	vector<Line> lines;
	vector<TextRecord> TextRecords;
	map<string,Symbol> symtab;
	map<string,string> optab;

void readOptab(){
	ifstream fin("optab.txt");
	string opcode;
	string op_strval;

	while(fin){
		fin>>opcode>>op_strval;
		optab[opcode] = op_strval;
	}
}


void read(){
	ifstream fin(input);
	int loc;
	int start;
	string line;
	string pgm_name;
	string l,opc,opr;
	string buffer,buf;
	string objcode="000000";
	string strloc; 

	map<string,Symbol>::iterator it;
	map<string,string>::iterator itr;


	// loc.setwidth	

	// first line
	getline(fin,line);
	istringstream ss(line);
	ss>>l>>opc>>opr;
	if (opc == "START"){
		pgm_name = opc;
		loc = atoi(opr.c_str());
		start = loc;
	}else
		loc = 0;
	Line ln(loc,l,opc,opr,objcode);
	lines.push_back(ln);

	cout<<"LOCCTR"<<loc<<endl;

	int init = loc;
	// initialize first text RECORD 
	TextRecord T(init,0);
	

	while(getline(fin,line)){
		while(line[0] == ';')
			getline(fin,line);
		istringstream ss(line);
		if(line[0]=='\t'){
			l = '\t';
			ss>>opc>>opr;
		}
		else
			ss>>l>>opc>>opr;
		// serach label in symtab , if found replace frwd ref lists
		it = symtab.find(l);			
		if(it != symtab.end()){
		    (it->second).value = loc;
			for(int i = 0;i< (it->second.frwd_ref).size();i++){
	        	// cout<<"T^"<< setw(6)  << setfill('0') << (it->second).frwd_ref[i]+1<<"^04^"<<loc<<endl;
	        	int f  = (it->second).frwd_ref[i]+1;   //crete new text record with new value
	        	TextRecord T(f,4);
	        	stringstream st;
		    	st<<loc;
		    	strloc = st.str();
	        	T.obj.push_back(strloc);
	        	TextRecords.push_back(T);
	    	}
		}
		// search optab with operand
		itr = optab.find(opc);
		if(itr!= optab.end()){
		   	buf = itr->second;	
		}
		else{
			buf ="00"; 
		}
		    objcode = buf+"0000";

		//search symtab with operand
		it = symtab.find(opr);
		if(it!= symtab.end()){
		    int v = it->second.value;              //if operand is symbol, found create objcode
		    stringstream st;
		    st<<v;
		    buffer = st.str();
			objcode = buf + buffer;
		}
		else{
			symtab.insert(pair<string,Symbol>(opr,Symbol(opr,0)));
		    it = symtab.find(opr);
		    (it->second).frwd_ref.push_back(loc);            //if operand is symbol, not found add to frwd_ref table
		}

		// itr = optab.find(opc);
		// if(itr!=optab.end())
		// {	// cout<< "^" << setw(6) << setfill('0') << objcode;
		if(opc!="RESW" && opc!="RESB" && opc!="END"){
			if(opc=="WORD")
				objcode = "0000"+opr;
			else if(opc=="BYTE")
				objcode = "0000"+opr;
			T.obj.push_back(objcode);
			T.size+=2;
		}
		// }
		Line ln(loc,l,opc,opr,objcode);
		lines.push_back(ln);
		if((loc-init) > max_size){
			// new text RECORD
			TextRecords.push_back(T);
			cout<<endl;
			init = loc;
			TextRecord T(init,0);
			// cout<<"T^"<< setw(6) << setfill('0') << init<<"^"<<"size";
		} 
		if(itr!= optab.end()) loc+=3;
		else if(opc=="WORD") loc+=3;
		else if(opc=="BYTE") loc+= opr.length();
		else if(opc=="RESW") loc+= 3*atoi(opr.c_str());
		else if(opc=="RESB") loc+= atoi(opr.c_str());
			
		else if(opc=="END") { TextRecords.push_back(T); break;}
		else{
			// cout<<"ERROR CODE";
			// exit(0);
		}
	}
		// output
		// head record
		cout<<"HEAD RECORD"<<endl;
		int len = loc-start;
		cout<<"H^"<<pgm_name<<"^"<< setw(6)  << setfill('0') << start<<"^";
		cout<< hex << len<<endl;	
		// text record
		for (int i = 0; i < TextRecords.size(); ++i)
		{
			cout<<"T^"<< dec<<  setw(6)  << setfill('0') <<  TextRecords[i].init<<"^"<< setw(2)  << setfill('0') << TextRecords[i].size;
			for (int j = 0; j < TextRecords[i].obj.size(); ++j)
				cout<<"^"<<TextRecords[i].obj[j];
			cout<<endl;
		}
		// end record
		cout<<"END RECORD"<<endl;
		cout<<"E^"<< setw(6)  << setfill('0') << dec << start<<endl;	
}

int main(){
	readOptab();
	read();
	for (int i = 0; i < lines.size(); ++i)
		cout<<lines[i].locctr<<"\t"<<lines[i].label<<"\t"<<lines[i].opcode<<"\t"<<lines[i].operand<<"\t"<<lines[i].objcode<<"\n";
	for (map<string,Symbol>::iterator it=symtab.begin(); it!=symtab.end(); ++it)
    	cout << it->first << " => " << it->second.name << " => " << it->second.value <<'\n';
	return 0;
}