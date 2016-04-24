#include "iostream"
#include "vector"
#include "string"
#include "sstream"
#include "fstream"
#include "stack"
using namespace std;
int p(string input){
	if(input=="$"){return 0;}
	if(input=="x"){return 5;}
	if(input=="+"){return 1;}
	if(input=="-"){return 1;}
	if(input=="*"){return 2;}
	if(input=="/"){return 2;}
	else return -1;
}

void parseInput(vector<string> inputs){
	stack<char> st;
	stack<char> reversest;
	st.push('$');
	stack<string> stringStack;
	for(std::vector<string>::iterator iter=inputs.begin();iter!=inputs.end();iter++){
		if(p(st.top()) < p(*iter))
			st.push(*iter);
		else{
			while(!st.empty() && p(*iter) <= p(st.top())){
				reversest.push(st.top());
				st.pop();
			}
			string ex="(";
			while(!reversest.empty()){
				ex+=reversest.top();
				reversest.pop();
			}
			ex+=")";
			
		}
	}
}
int main(int argc, char const *argv[])
{
	fstream f("input");
	string line, element;
	std::vector<string> inputs;
	while(getline(f, line)){
		stringstream ss(line);
		// inputs.push_back("$");
		while(getline(ss,element,' ')){
			inputs.push_back(element);
		}
		// inputs.push_back("$");
		parseInput(inputs);
		// inputs.clear();
	}
	return 0;
}