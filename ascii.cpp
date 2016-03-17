#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <stdlib.h>
using namespace std;

void B_to_A(const char*);   //function for converting Binary to ASCII

int main(void)
{
	char text[501];
	cout << " Enter the text/code you want to convert: ";
	cin >> text;
	
	B_to_A(text);    //if the user chose Binary -->ASCII , to go A_to_B()
	
	cout << " Conversion finished" << endl;  
	
	return 0;
}

void B_to_A(const char* input)
{
	int length = strlen(input);     //get length of string
	
	int binary[4];    //array used to store 1 byte of binary number (1 character)
	int asciiNum = 0;      //the ascii number after conversion from binary
	char ascii;      //the ascii character itself
	
	int add=0;
	cout << " ";
	
	int z = 0;   //counter used
	
	for(int x = 0; x < length / 5; x++)     //reading in bytes. total characters = length / 8
	{
		add = input[z]-'0';
		for(int a = 0; a < 5; a++)      //store info into binary[0] through binary[7]
		{
			binary[a] = (int) input[z] - 48;      //z never resets
			z++;
		}
		int power[6];    //will set powers of 2 in an array
		int counter = 3;        //power starts at 2^0, ends at 2^7
		for(int x = 1; x < 5; x++)
		{
			power[x] = counter;      //power[] = {7, 6, 5, ..... 1, 0}
			counter--;    //decrement counter each time
		}
		
		for(int y = 1; y < 5; y++)    //will compute asciiNum
		{
			double a = binary[y];    //store the element from binary[] as "a"
			double b = power[y];    //store the lement from power[] as "b"
			
			asciiNum += a* pow(2, b);   //asciiNum = sum of a * 2^power where 0 <= power <= 7, power is int
		}

		asciiNum = asciiNum + 64;
		if(add==1) asciiNum = asciiNum + 16;

		ascii = asciiNum;   //assign the asciiNum value to ascii, to change it into an actual character
		if(asciiNum==64) ascii = ' ';
		asciiNum = 0;    //reset asciiNum for next loop
		
		cout << ascii;	//display the ascii character
	}
}
