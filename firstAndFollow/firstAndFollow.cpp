#include "iostream"
#include "vector"
#include "map"
#include "set"
#include "string"
#include "sstream"
#include "fstream"
#include "stack"
#include "ctype.h"
using namespace std;

/*
E → TD
D → +TD | ε
T → FG
G → *FG | ε
F → (E) | id

FIRST(E) = {'(',id}
FIRST(D) = {+,ε}
FIRST(T) = {'(',id}
FIRST(G) = {*,ε}
FIRST(F) = {'(',id}


FOLLOW(E) = {$,)}
FOLLOW(D) = {$,)}
FOLLOW(T) = {+,$,)}
FOLLOW(G) = {+,$,)}
FOLLOW(F) = {*,+,$,)}
*/
std::vector<string> allProductions;
std::map<string, string > productionToLhs;
std::map<string, vector<string> > productionMap;
std::map<string, set<char> > firstMap;
std::map<string, set<char> > followMap;

set<char> findFirst(string in){
		set<char> firstSet;

		if(in=="d" || in=="(" || in==")" || in=="*" || in=="+"){
			firstSet.insert(in[0]);
			return firstSet;
		}
		for (std::vector<string>::iterator iter = productionMap[in].begin(); iter != productionMap[in].end(); ++iter)
		{	
			int i=0;
			string s = *iter;
				if(productionMap.find(string(1, s[i]))!=productionMap.end()){
					set<char> resSet = findFirst(string(1, s[i]));
					firstSet.insert(resSet.begin(), resSet.end());
					while(i<s.length() && resSet.find('e')!=resSet.end()){
						resSet = findFirst(string(1, s[++i]));
						firstSet.insert(resSet.begin(), resSet.end());
					}
				}
				else{
					firstSet.insert(s[i]);
				}
		}
		firstMap[in] = firstSet;
		return firstSet;
}

set<char> findFollow(string in){
	string startSymbol;
	fstream f("input");
	f>>startSymbol;
	set<char> followSet;
	if(in==startSymbol){
		followSet.insert('$');
	}
	for (std::vector<string>::iterator i = allProductions.begin(); i != allProductions.end(); ++i)
	{
		string production = *i;
		set<char> firstSet;
		int index = production.find(in);
		if(index!=string::npos){
			if(index<(production.length()-1)){
				do{
					followSet.erase('e');
					if(index==(production.length()-1) && firstMap.find(string(1, production[index]))!=firstMap.end()){
						string lhs = productionToLhs[production];
						if(lhs[0]!= production[index]){
							set<char> resSet = findFollow(lhs);
							followSet.insert(resSet.begin(), resSet.end());
						}
						index++;
					}
					else{
						firstSet = findFirst(string(1, production[++index]));
						followSet.insert(firstSet.begin(), firstSet.end());
					}
				}while(index<production.length() && firstSet.find('e')!=firstSet.end() &&
					firstMap.find(string(1, production[index]))!=firstMap.end());
			}
			if(index==(production.length()-1) && firstMap.find(string(1, production[index]))!=firstMap.end()){
				string lhs = productionToLhs[production];
				if(lhs[0]!= production[index]){
					set<char> resSet = findFollow(lhs);
					followSet.insert(resSet.begin(), resSet.end());
				}
			}
		}
	}
	followSet.erase('e');
	followMap[in] = followSet;
	return followSet;
}
int main(int argc, char const *argv[])
{
	fstream f("input");
	string line, elemnt;
	std::vector<string> inputs;
	while(getline(f, line)){
		std::vector<string> productions;
		stringstream ss(line);
		while(getline(ss, elemnt, ' '))
			inputs.push_back(elemnt);
		for(std::vector<string>::iterator iter=++inputs.begin();iter!=inputs.end();iter++){
			if(*iter=="|" || *iter=="→") continue;
			productions.push_back(*iter);
			allProductions.push_back(*iter);
			productionToLhs[*iter] = *inputs.begin();
		}
		productionMap[*inputs.begin()] = productions;
		inputs.clear();
		productions.clear();
	}
	f.close();

	// productions
	for (std::map<string, vector<string> > ::iterator i = productionMap.begin(); i != productionMap.end(); ++i)
	{
		cout<< i->first << " → ";
		for (std::vector<string>::iterator j = (i->second).begin(); j != (i->second).end(); ++j)
			{
				cout<< *j<< " ";
			}
		cout<< endl;	
	}
		
	
	// for first
	cout<<"FIRST"<<endl;
	for (std::map<string, vector<string> > ::iterator i = productionMap.begin(); i != productionMap.end(); ++i)
		findFirst(i->first);
	for (std::map<string, set<char> > ::iterator i = firstMap.begin(); i != firstMap.end(); ++i)
	{
		cout<< i->first << " → ";
		for (std::set<char>::iterator j = (i->second).begin(); j != (i->second).end(); ++j)
				cout<< *j<< " ";
		cout<< endl;	
	}
	// for follow
	cout<<"FOLLOW"<<endl;
	for (std::map<string, vector<string> > ::iterator i = productionMap.begin(); i != productionMap.end(); ++i){
		string key = i->first;
		findFollow(key);
	}
	for (std::map<string, set<char> > ::iterator i = followMap.begin(); i != followMap.end(); ++i)
	{
		cout<< i->first << " → ";
		for (std::set<char>::iterator j = (i->second).begin(); j != (i->second).end(); ++j)
				cout<< *j<< " ";
		cout<< endl;	
	}
	// for (std::map<string, string > ::iterator i = productionToLhs.begin(); i != productionToLhs.end(); ++i)
	// {
	// 	cout<< i->first << "    "<< i->second<<endl;
	// }
	return 0;
}