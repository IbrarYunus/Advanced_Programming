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
using namespace std;

/*Color Definitions*/
#define RED     "\033[31m" 
#define RESET   "\033[0m"


/* Variable Storage Class*/
class variableStorage // Standard way of defining the class
{
public:
	string types ;
	string values ;
public:
	void _setVariable(string _types, string _value)
	{
		// types = _types;
		// values = _value;
	}
};


/*Globals*/
std::map<string, variableStorage> variableHash;
vector<string> tokens {"LET", "print"};
vector<string> operators{"+","-","*","/","="};
string line;
string line2;
int lineCounter = 1;
string curKeyword = "";
string word2;
int LET = 0;
int AM = 0;
int DISP = 0;
string _tempStore;

/*Declarations*/
void FileParser(string name);
int Lexer();
int Checker(string word);
bool isNUM(const std::string& mystring);
void hashDebug();
int GetResult( char * rpn ); 



/*Maximum variables per line can be 100*/
variableStorage myVars[100];


/*check command line arguments only*/
int main( int argc, char *argv[])
{
    
  if(argv[1] == NULL)
    cout<<"! Syntax is <Interpreter> <File Name> \n";
  else
  {
    FileParser(argv[1]);
  }

  hashDebug();		
  cout<<"\n";
}

/*Parses the File anf passe a line to the tokenizer*/
void FileParser(string name) 
{
  std::ifstream fp(name);
  if(fp == NULL)
  {
    cout<<"! File Not Found\n";
    exit(0);
  }

  while (getline(fp, line))
  {
  	//cout<<lineCounter<<" ";
  	cout<<line<<"\n";
  	if(line.length() > 0)
  	{
  		Lexer();
  		cout<<"\n";
  	}
  	lineCounter++;
  }
}



/*Tokenizez a lines into variables, keywords and values*/
int Lexer()
{				
	if(line[line.length()-1] != ';')										//Uses Line to track 1
	 {
	 	cout<<RED<<"\nsyntax error at line: "<< lineCounter<<"\n"<<RESET;
	 	exit(0);
	 }

 	stringstream strstr(line);												//Construting a string stream
	
	line2 = line;
	/* Tokenizer */	

 	istream_iterator<std::string> it(strstr);								// tokenize as white separated stream of strings
 	istream_iterator<std::string> end;
 	vector<std::string> results(it, end);

 	/* Keyword Checking*/
 	for( int i = 0; i < results.size(); i++)
 	{
 		word2 = results[i];

 		Checker(results[i]);
 	}

}


/*Called by Lexer(), checks if a string is a variable, value or a keyword*/
int Checker(string word)
{
	static int counter = 0;
	int firstTime = 0;

	if(std::find(tokens.begin(), tokens.end(), word)!=tokens.end())						
	{
		cout<<word<<" "<<" is a key word\n";
		if(word == "LET")
		{
			LET = 1;
			firstTime++;
		}

		if( word == "print")
		{
			if(firstTime != 0)
			{
				cout<<RED<<"\nsyntax error at line: "<< lineCounter<<"\n"<<RESET;
	 			exit(0);
			}
			else
			{
				cout<<"Display Mode\n";
				DISP++;
			}
		}
	}

	else if(std::find(operators.begin(), operators.end(), word)!=operators.end())
	{
		cout<<word<<" "<<" is a operator\n";
		if(LET == 1)
		{
			if(word != "=")
			{
				cout<<RED<<"\nsyntax error at line: "<< lineCounter<<"\n"<<RESET;
	 			exit(0);
	 		}
		}
		firstTime++;
	}

	else if ( word == ";")
	{
		cout<<"LET = 0\n";
		LET = 0;
		firstTime++;
	}

	else if( !isNUM(word))
	{
		if (!(word.find("\"") != std::string::npos)) 
		{
			cout<<word<<" "<<" is a variable\n";
			if( DISP > 0)
			{
				cout<<variableHash[word].values<<"\n";
			}
			if(LET == 1)
			{
				_tempStore = word;
			}

		}

		else
		{
			myVars[counter].types = "str";
			cout<<word<<" "<<" is a string\n";		
			if(LET == 1)
			{
				
				myVars[counter].values = word;
				variableHash[_tempStore] = myVars[counter];
				counter++;
			}
		}

		firstTime++;		
	}

	else 
	{	
		if( isNUM(word))
		{
			myVars[counter].types = "int";
			cout<<word<<" "<<" is a number\n";
		}

		if(LET == 1)
		{
			
			myVars[counter].values = word;
			variableHash[_tempStore] = myVars[counter];
			counter++;
		}
		firstTime++;
	}
;	
}


/*To check if a string contains a number*/
bool isNUM(const std::string& mystring)
{
    return !mystring.empty() && std::find_if(mystring.begin(), 
        mystring.end(), [](char c) { return !std::isdigit(c); }) == mystring.end();
}



void hashDebug()
{
	cout<<"\nChecking HashMap "<<"A has "<<variableHash["A"].values<<" END";
	cout<<"\nChecking HashMap "<<"B has "<<variableHash["B"].values<<" END";

}


/*Infix Calculator*/
int GetResult( string mystring ) 
{
    std::stack<int> tempHolder;

    int tmp1, tmp2; int length = mystring.size();

    for (int i = 0; i < length; i++)
    {
        if (isdigit(mystring[i]))
        {
            tempHolder.push(mystring[i] - '0');
        }
        else
        {
            switch(mystring[i])
            {
                case '+':
                    tmp1 = tempHolder.top();
                    tempHolder.pop();
                    tmp2 = tempHolder.top();
                    tempHolder.pop();
                    tempHolder.push(tmp2 + tmp1);
                    break;


                case '*':
                    tmp1 = tempHolder.top();
                    tempHolder.pop();
                    tmp2 = tempHolder.top();
                    tempHolder.pop();
                    tempHolder.push(tmp2 * tmp1);
                    break;

                case '-':
                    tmp1 = tempHolder.top();
                    tempHolder.pop();
                    tmp2 = tempHolder.top();
                    tempHolder.pop();
                    tempHolder.push(tmp2 - tmp1);
                    break;


                case '/':
                    tmp1 = tempHolder.top();
                    tempHolder.pop();
                    tmp2 = tempHolder.top();
                    tempHolder.pop();
                    tempHolder.push(tmp2 / tmp1);
                    break;
                default:
                    break;
            }
        }
    }

    return tempHolder.top();
}
