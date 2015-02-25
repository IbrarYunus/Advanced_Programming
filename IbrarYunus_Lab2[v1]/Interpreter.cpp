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
vector<string> backUp;
string line;
string line2;
int lineCounter = 1;
string curKeyword = "";
string word2;
int LET = 0;
int AM = 0;
int DISP = 0;
string _tempStore;
int firstTime = 0;
string Artith;


/*Declarations*/
void FileParser(string name);
int Lexer();
int Checker(string word);
bool isNUM(const std::string& mystring);
void hashDebug();
int expressionSolver( string exp);


/*Maximum variables per line can be 100*/
variableStorage myVars[100];




/*Parses the File anf passe a line to the tokenizer*/
void FileParser(string name) 
{
  std::ifstream fp(name);
  if(fp == NULL)
  {
    cout<<"! File Not Found\n";						//If file not found
    exit(0);
  }

  while (getline(fp, line))							//reads teh file line by line
  {
  	cout<<line<<"\n";
  	if(line.length() > 0)							//Only parses the line if it has something
  	{
  		Lexer();
  		cout<<"\n";
  	}
  	lineCounter++;									//Used later in error handling
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
	
	line2 = line;															//duplicated as it is later used in handling arithmetic
	/* Tokenizer */	

 	istream_iterator<std::string> it(strstr);								// tokenize as white separated stream of strings
 	istream_iterator<std::string> end;
 	vector<std::string> results(it, end);

 	backUp = results;														//Duplicated for checking previous 'words' - for debug purposes only
 	/* Keyword Checking*/
 	firstTime = 0;															//Used later in Checker(), used to see if a variable is occured first time
 	for( int i = 0; i < results.size(); i++)
 	{
 		//word2 = results[i];

 		Checker(results[i]);												//The interpreter logic
 	}

}


/*Called by Lexer(), checks if a string is a variable, value or a keyword*/
int Checker(string word)
{
	static int counter = 0;														//Used to store variables


	if(std::find(tokens.begin(), tokens.end(), word)!=tokens.end())				//if teh word is a keyword		
	{
		cout<<word<<" "<<" is a key word\n";
		if(word == "LET")														//if it is LET then set the LET bit
		{
			LET = 1;
			firstTime++;
		}

		if( word == "print")													//If it is print then set the DISPlay bit
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
		firstTime++;															//To signify that the first word of the line has been parsed

	}

	else if(std::find(operators.begin(), operators.end(), word)!=operators.end())	// If the word belongs to one of the 4 opertors
	{
		cout<<word<<" "<<" is a operator\n";
		if(LET == 1)
		{
			if(word != "=")															// To error handle statements as:  LET A + B
			{
				cout<<RED<<"\nsyntax error at line: "<< lineCounter<<"\n"<<RESET;
	 			exit(0);
	 		}
		}
		firstTime++;															//To signify that the first word of the line has been parsed	
	}

	else if ( word == ";")														//To see if the delimiting character has been met
	{
		cout<<"LET = 0\n";
		LET = 0;
		firstTime++;
	}

	else if( !isNUM(word))														//If it is a variable
	{
		if (!(word.find("\"") != std::string::npos)) 
		{
			cout<<word<<" "<<" is a variable\n";
			if( DISP > 0)														//If DISP bit is set, then display is
			{
				cout<<variableHash[word].values<<"\n";
			}
			if(LET == 1)														//If let bit is set, then assign it to the incoming string
			{
				_tempStore = word;
			}

			if(firstTime == 0)													// in statements as C = A + B, a variables comes first
			{
				cout<< "Arithematic "<<"\n";
				
				//cout<<line2<<"\n";		
				for( int i = 2 ; i< backUp.size()-1; i++)
				{
					

					if(!isNUM(backUp[i]))										// To create a string to send to the expressio handler, 
						Artith.append(variableHash[backUp[i]].values);			//If the string is not a number then append it to the master string it's value from hashmap

					else
						Artith.append(backUp[i]);								//Else append it as is			

					if (std::find(operators.begin(), operators.end(), backUp[i])!=operators.end())
					{
						Artith.append(backUp[i]);								//If it is one of the operators then append it as is
					}

					Artith.append(" ");											// delimits teh literals with spaces
				}		
				cout<<Artith;
				stringstream ss;
				ss << expressionSolver(Artith);
				if ( variableHash.find(word) == variableHash.end() )			// To error handle statments as 
				{
					cout<<RED<<"\nsyntax error at line: "<< lineCounter<<"\n"<<RESET;
	 				exit(0);
				}
				variableHash[word].values = ss.str();

				cout<< "Arithematic END"<<"\n";

			}

		}

		else
		{
			myVars[counter].types = "str";									//Unfiniches part, for string concatenation and other stuff
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
		if( isNUM(word))													//Checks id the word is infact a number ( using atoi)
		{
			if(firstTime == 0)												//To error handle statements as 5 = C
			{
				cout<<RED<<"\nsyntax error at line: "<< lineCounter<<"\n"<<RESET;
	 			exit(0);
			}
			myVars[counter].types = "int";
			cout<<word<<" "<<" is a number\n";
		}

		if(LET == 1)														//Assignment for LET keyword happens here
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




//////////////Expression Parser
///

int expressionSolver( string exp)
{
	stringstream strstr(exp);				
	istream_iterator<std::string> it(strstr);								// tokenize as white separated stream of strings
 	istream_iterator<std::string> end;
 	vector<std::string> results(it, end);
 	int ADD = 0 ;
 	int MIN = 0 ;
 	int DIV = 0 ;
 	int MUL = 0 ;

 	int storage = 0;

	for( int i = 0; i < results.size(); i++)
	 	{
	 		if(isNUM(results[i]))
	 		{
	 			if( ADD == 1)
	 			{
	 				storage += atoi(results[i].c_str());

	 				ADD = 0 ; 
	 			}

	 			else if( MIN == 1)
	 			{
	 				storage -= atoi(results[i].c_str());

	 				MIN = 0 ; 
	 			}

	 			else if( MUL == 1)
	 			{
	 				storage *= atoi(results[i].c_str());

	 				MUL = 0 ; 
	 			}

	 			else if( DIV == 1)
	 			{
	 				storage /= atoi(results[i].c_str());

	 				DIV = 0 ; 
	 			}



	 			else
	 				storage = atoi(results[i].c_str());
	 		}

	 		if(results[i] == "+")
	 		{
	 			ADD = 1;
	 			//cout<<"ADD switch\n";
	 		}

	 		if(results[i] == "-")
	 		{
	 			MIN = 1;
	 			//cout<<"MIN switch\n";
	 		}


	 		if(results[i] == "/")
	 		{
	 			DIV = 1;
	 			//cout<<"DIV switch\n";
	 		}

	 		if(results[i] == "*")
	 		{
	 			MUL = 1;
	 			//cout<<"MUL switch\n";
	 		}

	 		//cout<<"RES :" <<storage<<"\n";
	 	}
	return storage; 	

}