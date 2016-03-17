#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <ctype.h>
#include <vector>
#include <map>
#include <string>
#define input "OR.txt"
using namespace std;

std::map<char, int> prioritymap;						// priority map for operators
std::map<char, int>::iterator itr;
std::map<char, int>::iterator itr2;

string line;
char  terminal_char; 
char leftassociative[] = {'+','-','*','/','('};
char rightassociative[] = {'^',')'};
char operationTable[20][20] ;

ifstream fin(input);
int precedence_value = 1;
int numOfOperators= 1;

bool isRightAssociative(char c){
	for (int i = 0; i < 2; ++i)
		if(c == rightassociative[i])
			return true;
	return false;
}
bool isLeftAssociative(char c){
	for (int i = 0; i < 5; ++i)
		if(c == leftassociative[i])
			return true;
	return false;
}
bool isOperator(char c){
	if(isLeftAssociative(c) || isRightAssociative(c))
		return true;	
	return false;
}
void fillprioritymap(){
	while(getline(fin,line)){
		for (int i = 0; i < line.length(); ++i)
			if(isOperator(line[i]))
				prioritymap[line[i]] = precedence_value;
			else
				terminal_char = line[i];
		precedence_value++;
	}
	prioritymap['$'] = -1;                           			// $ symbol least precedence
	prioritymap['('] = 0;										// ) least priority (greater than $)
	prioritymap[terminal_char] = ++precedence_value;			// terminating character highest precedence
}
void fillOpeartionTable(){
	for(itr= prioritymap.begin();itr!=prioritymap.end();itr++){
		operationTable[0][numOfOperators] = operationTable[numOfOperators][0] = itr->first;
		// cout<<  << "   " << itr-> second<<endl;
		numOfOperators++;	
	}
}
void printOperationTable(){
	for (int i = 0; i < numOfOperators; ++i){
		for (int j = 0; j < numOfOperators; ++j)
			cout << operationTable[i][j]<<"  	";
		cout<< endl;
	}
} 
char compare(char s,char t){
	if ( (prioritymap.find(s)->second) > (prioritymap.find(t)->second)  )
		return '>';
	else if((prioritymap.find(s)->second) < (prioritymap.find(t)->second))
		return '<';
	else if(isRightAssociative(s) )										//equal priority
		return '<';
	else if(isLeftAssociative(s)) 
		return '>';
	else 
		return '-';
}
void setOperationTable(){
	for (int i = 1; i < numOfOperators; ++i){
		for (int j = 1; j < numOfOperators; ++j)
			operationTable[i][j] = compare(operationTable[i][0],operationTable[0][j]);
	}
} 
int main(){
	fillprioritymap();
	fillOpeartionTable();
	for(itr= prioritymap.begin();itr!=prioritymap.end();itr++)
		cout<< itr->first << "   " << itr-> second<<endl;
	setOperationTable();
	printOperationTable();
	return 0;
}