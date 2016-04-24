#include "iostream"
#include "vector"
#include "string"
#include "sstream"
#include "fstream"
#include "stack"
#include "ctype.h"
using namespace std;

string expression;
char lookahead;
int i = 0;
bool error = false;

void E();
void E_PRIME();
void T();
void T_PRIME();
void F();
void match(char);
void check(){
	if(lookahead=='x'){
		cout<<"ERROR!!";
		error = true;
	}

}
void E(){
	T();
	E_PRIME();
}

void E_PRIME(){
	if(lookahead=='+'){
		match('+');
		T();
		E_PRIME();
	}
	check();

		// return;
}

void T(){
	F();
	T_PRIME();
}

void T_PRIME(){
	if(lookahead=='*'){
		match('*');
		F();
		T_PRIME();
	}
	check();
	// else
		// return;
}

void F(){
	if(lookahead=='('){
		match('(');
		E();
		match(')');
	}
	else if(lookahead=='x'){
		match('x');
	}	
	else{
		cout<<"ERROR!!"<<endl;
		error = true;
	}
}
void match(char ch){
	if(lookahead == ch)
		lookahead=expression[++i];
	else{
		cout<<"ERROR!!"<<endl;
		error = true;
	}
}
int main(int argc, char const *argv[])
{
	cout<<"Enter expression : ";
	cin>>expression;
	expression+="$";
	lookahead=expression[0];
	E();
	if(!error)
		cout<<"parsing success"<<endl;
	return 0;
}
