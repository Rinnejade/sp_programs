#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <ctype.h>
#include <vector>
#include <map>
#include <string>
#define input "LAinput.txt"
#define output "LAoutput.txt"

using namespace std;

string strline;
string status;
string strings[20];
int n;
int line=0;
char delimiter = ' ';


void splitTokens(string s,string str[]){
	int i = 0;
	int last = 0; int next = 0; 
	while ((next = s.find(delimiter, last)) != string::npos) {
		str[i] = s.substr(last, next-last);
		// if(delimiter != str[i])
			i++;
		last = next + 1; 
	}
	str[i]= s.substr(last);
	// if(delimiter != str[i])
		n = i+1;
}

bool keycheck(string str)
{
    string keyword[] ={"int","main()","float","if","include","stdio.h"};
    int flag=0;
    if(!(str[0]>=97 && str[0]<=122))     
        return false;
    for(int i=0;i<6;i++)
        if(str == keyword[i])
            return true;
    return false;
} 

int opcheck(string str)
{
     string reloperators[8] ={"=","==",">","<",">=","<="};
     string mathoperators[5] ={"+","*","/","-","%"};
     string operators[5]={"{","}",";",",","#"};
     
    
    for(int i=0;i<5;i++)
        if(str == operators[i])
        {
            status = "operator";
          	return 1;
        }
    
    
    for(int i=0;i<8;i++)
        if(str == reloperators[i])
        {
  	        status =  "relational operator";
          	return 1;
        }
    for(int i=0;i<5;i++)
        if(str == mathoperators[i])
        {
            status =  "mathematical operator";
            return 1;
        }
    return 0;
}
                   
         
             
int ischar(char c)
{
    if((c>=65 && c<=90) || (c>=97 && c<=122))
             return 1;
    return 0; 
}          
                     

int isnum(char c)
{
    if(c>=48 && c<=57)
             return 1;
        return 0;
}
    
int isnums(string str)
{
    int flag=0;
    for(int i = 0;i<str.length();i++)
    {
         if(!isnum(str[i]))
         {
                           if(str[i] != 46) 
                           {
                                     flag=1;
                                     break;
                           }
         }
    }
    
    if(flag == 1)
            return 0;
    else
            return 1;
}

int isidentifier(string str)
{
	if(isnum(str[0]))
		return 1;
    int flag =0;
     for(int i=1;i<str.length();i++)
     {
      if(!ischar(str[i]))
      {
       if(!isnum(str[i]))
       {
        if(str[i] != 95)
        {
           if(str[i] == 91)
           {
                     i++;
                     for(;str[i]!= 93;)
                     {
                      if(!isnum(str[i]))
                      {
                                        flag =1;
                                        break;
                      }
                      i++;
                     }
           }
           else
           {         
                     flag = 1;
                     
           }
           if(flag ==1)
                   break;
        }
      }
     }
    }
    
    return flag;
}


int main(){
	ifstream fin(input);
	while(getline(fin,strline)){
		splitTokens(strline,strings);
		line++;
		cout<<"---------\n";
    	cout<<"LINE  :" <<line<<"\n";
		for (int i = 0; i < n ; ++i)
		{
			if(keycheck(strings[i]))
				cout<<strings[i]<<"\t --> reserved word\n";  
			else if(isnums(strings[i]))
				cout<<strings[i]<<"\t --> number \n";
			else if(opcheck(strings[i]))
				cout<<strings[i]<<"\t --> "<< status <<" \n";
			else if(!isidentifier(strings[i]))
				cout<<strings[i]<<"\t --> identifier \n";
			else
				cout<<strings[i]<<"\t --> error \n";
		}
	}
}