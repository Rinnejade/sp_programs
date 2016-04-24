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
vector<string> reduce(string input){
	vector<string> res;
	for (int i = 0; i < input.length(); ++i)
		if((input[i]!='>' && input[i]!='<') && !(input[i]!='$' && input[i-1]=='<' && input[i+1]=='>'))
			res.push_back(string(1, input[i]));
	return res;
}
int main(int argc, char const *argv[])
{
	fstream f("input");
	string line, element;
	std::vector<string> inputs;
	while(getline(f, line)){
		stringstream ss(line);
		inputs.push_back("$");
		while(getline(ss,element,' ')){
			inputs.push_back(element);
		}
		inputs.push_back("$");
		while(inputs.size()>2){
			string expression = "";
			for(vector<string>::iterator iter=inputs.begin();iter!=inputs.end();iter++){
				vector<string>::iterator after = iter;
				after++;
				if(after!=inputs.end()){
					if(p(*iter)< p(*after))
						expression+=*iter+"<";
					else
						expression+=*iter+">";
				}
				else
					expression+=*iter;
			}
			cout<<"expression " <<expression<<endl;
			inputs = reduce(expression);
		}
		inputs.clear();
		// inputs.clear();
	}
	return 0;
}