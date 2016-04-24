#include "iostream"
#include "vector"
#include "string"
#include "sstream"
#include "fstream"
#include "stack"
#include "ctype.h"
using namespace std;

bool isOperand(char c){
	if(isdigit(c) || isalpha(c))
		return true;
	return false;
}
bool isOperator(char c){
	if(c=='+' || c=='-' || c=='/' || c=='*' || c=='=') return true;
	return false;
}
int isp(char e)
{
	if(e=='+'){return 2;}
	else if(e=='-'){return 2;}
	else if(e=='*'){return 3;}
	else if(e=='/'){return 3;}
	else if(e=='^'){return 4;}
	else if(e=='='){return 0;}
	return 0;
}
int icp(char e)
{
	if(e=='+'){return 2;}
	else if(e=='-'){return 2;}
	else if(e=='*'){return 3;}
	else if(e=='/'){return 3;}
	else if(e=='^'){return 5;}
	else if(e=='='){return 0;}
	return 0;
}
string toPostfix(string expression){
	string postfix="";
	stack<char> st;
	for (int i = 0; i < expression.length(); ++i){
			if(expression[i]==' ') continue;
			if(isOperand(expression[i]))
				postfix+=expression[i];
			else if(isOperator(expression[i])){
				while(!st.empty() && st.top()!='(' && icp(expression[i]) <= isp(st.top())){
					postfix+=st.top();
					st.pop();
				}
				st.push(expression[i]);
			}
			else if(expression[i]=='(')
				st.push(expression[i]);
			else if(expression[i]==')'){
				while(!st.empty() && st.top()!= '('){
					postfix+=st.top();
					st.pop();
				}
				st.pop();
			}
		
	}
	while(!st.empty()) {
		postfix += st.top();
		st.pop();
	}
	cout<<postfix<<endl;
	return postfix;

}
void genIntermediate(string input){
	stack<string> st;
	int count = 1;
	for (int i = 0; i < input.length(); ++i)
		if(!isOperator(input[i]))
			st.push(string(1, input[i]));
		else{
			string second = st.top(); st.pop();
			string first = st.top(); st.pop();
			string lhs = "t" + to_string(count++);
			if(input[i]!='=')
				cout<< lhs << " = " <<first << input[i] << second<<endl;
			else
				cout<< first << " = " << second<<endl;
			st.push(lhs);
		}

}
int main(int argc, char const *argv[])
{
	fstream f("input");
	string expression, element;
	while(getline(f,expression)){
		stringstream ss(expression);
		cout<<"INPUT:"<<expression<<endl;
		genIntermediate(toPostfix(expression));
	}
	return 0;
}