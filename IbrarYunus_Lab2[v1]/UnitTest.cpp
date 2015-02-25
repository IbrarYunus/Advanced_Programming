// basic file operations
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <map>
#include <stack>
#include <assert.h>
#include "Interpreter.cpp"
using namespace std;

#define YELLOW     "\033[33m"
#define GREEN     "\033[32m" 
#define RESET   "\033[0m"

void _CheckParser();
void _CheckCode(string argv);

int main( int argc, char *argv[])
{

  if(argv[1] == NULL)
  {
    cout<<"! Syntax is <Interpreter> <File Name> \n";
    exit(0);

  }	
  else
  {
    //FileParser(argv[1]);
  }  

  _CheckParser();
  cout<<"\n\n";

  _CheckCode(argv[1]);
}


void _CheckParser()
{
	cout<<"Checking the Expression Parser >> Sending \" 2 + 4 + 5 \" \n";
	assert (expressionSolver("2 + 4 + 5") == 11);
	cout<<"Answer is 11\n";
	cout<<GREEN<<"PASSED\n"<<RESET;

	cout<<"Checking the Expression Parser >> Sending \" 2 + 4 - 5 \" \n";
	assert (expressionSolver("2 + 4 - 7") == -1);
	cout<<"Answer is -1\n";
	cout<<GREEN<<"PASSED\n"<<RESET;

}

void _CheckCode(string argv)
{
	cout<<YELLOW<<"DEBUG INFO\n";
	FileParser(argv);

	cout<<YELLOW<<"DEBUG INFO END\n"<<RESET;

	cout<<"Checking Values of Variables A and B\n";
	cout<<"\nChecking HashMap "<<"A has "<<variableHash["A"].values;
	cout<<"\nChecking HashMap "<<"B has "<<variableHash["B"].values;
	cout<<"\n";
	assert(variableHash["A"].values == "69");
	assert(variableHash["B"].values == "\"NG\"");
	cout<<GREEN<<"PASSED\n"<<RESET;

}