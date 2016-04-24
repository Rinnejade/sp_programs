#include "iostream"
#include "vector"
#include "string"
#include "sstream"
#include "fstream"
#include "stack"
#include "ctype.h"
using namespace std;

int main(int argc, char const *argv[])
{
	string line,element;
	fstream f("input");
	while(getline(f,line)){
		std::vector<string> expression;
		stringstream ss(line);
		cout<<"line : "<<line<<endl;
		while(getline(ss, element, ' ')){
			expression.push_back(element);
		}
		for (vector<string>::iterator iter = expression.begin(); iter!= expression.end();iter++){
			vector<string>::iterator before = iter;
			vector<string>::iterator after = iter;
			after++;
			before--;
			if(*iter=="=")
				cout<<"MOV "<<*before<<", "<<*after<<"\n";
			else if(*iter=="+")
				cout<<"ADD "<<*expression.begin()<<", "<<*after<<"\n";
			else if(*iter=="-")
				cout<<"SUB "<<*expression.begin()<<", "<<*after<<"\n";
			else if(*iter=="*")
				cout<<"MUL "<<*expression.begin()<<", "<<*after<<"\n";
			else if(*iter=="/")
				cout<<"DIV "<<*expression.begin()<<", "<<*after<<"\n";
		}
		expression.clear();
		cout<<endl;
	}
	return 0;
}