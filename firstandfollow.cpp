#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <vector>
#include <map>
#include <string>
#include <stdio.h>
#define input "CFG.txt"
using namespace std;

int n;
string s;
string delimiter = " | ";
ifstream fin(input);

class Symbol{
public:
	char c;
	int fisrt_n,follow_n;
	char first[10];
	char follow[10];
	std::vector<string> productions;
	Symbol(char c){
		this->c = c;
	}
};

void findFirst(char c){

}
void findFollow(char c){

}
void addtoFirst(char c){

}
void addtoFollow(char c){

}

int main(){
	while(getline(fin,s)){
		Symbol symbol = new Symbol(s[0].c_str());
		s.erase(0,5);
		size_t pos = 0;
		while ((pos = s.find(delimiter)) != std::string::npos) {
		    s.substr(0, pos);
		    s.erase(0, pos + delimiter.length());
		}
		std::cout << s << std::endl;
	}
	cout<<endl;
	return 0;
}