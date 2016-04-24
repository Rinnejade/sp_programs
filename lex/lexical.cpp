#include "iostream"
#include "regex"
#include "fstream"
#include "sstream"
using namespace std;

					
#define OPERATOR "[OPERATOR]"
#define NEWLINE "[NEWLINE]"
#define VARIABLE "[VARIABLE]"
#define KEYWORD "[KEYWORD]"
#define NUMBER "[NUMBER]"
#define EQUAL "[EQUAL]"
#define IN "[IN OPERATOR]"
#define OUT "[OUT OPERATOR]"
#define ERROR "[ERROR]"

regex key("[cout | cin]");
regex var("[A-Za-z][A-Za-z0-9]*");
regex number("[0-9]+");
regex op("[\\+\\*\\-\\;]");
regex in(">>");
regex out("<<");
regex eq("=");
regex newline("\n");


bool analyze(string word){
	if(regex_match(word, key)) cout<<KEYWORD;
	else if(regex_match(word, var)) cout<<VARIABLE;
	else if(regex_match(word, op)) cout<<OPERATOR;
	else if(regex_match(word, newline)) cout<<NEWLINE;
	else if(regex_match(word, eq)) cout<<EQUAL;
	else if(regex_match(word, number)) cout<<NUMBER;
	else if(regex_match(word, in)) cout<<IN;
	else if(regex_match(word, out)) cout<<OUT;
	else cout<<ERROR;
}
int main(int argc, char const *argv[])
{
	fstream f("input");
	string line, word;
	while(getline(f, line)){
		cout<<line<<endl;
		stringstream ss(line);
		while(getline(ss, word, ' ')){
			analyze(word);
		}
		cout<<endl;
	}
	return 0;
}