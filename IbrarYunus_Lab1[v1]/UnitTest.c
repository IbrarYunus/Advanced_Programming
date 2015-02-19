//Unit Tests for MatrixCALC
///Ibrar Yunus 
///Test v.1

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "MatrixCalc.h"


//Function declarations
void Init();
void AdditionTest();
void MultiplicationTest();
void combinedTest();


//Holds the actual answers ( verified from other sources )
struct matrices multiplyTest[2];	
struct matrices additionTest[2];

// Calls all the other funtions
int main(void)
{
	printf("\n**UNIT TESTs**\n");
	Init();
	MultiplicationTest();
	AdditionTest();
	combinedTest();
}




//Initilizes the variables and calls filer
void Init()
{
	printf("Initializing\n");

	//// Real Multiplication Answers
	int **storage1;
	storage1 = CreateNewMatrix(2, 2);
	storage1[0][0] = 15;
	storage1[0][1] = 15;
	storage1[1][0] = 35;
	storage1[1][1] = 37;
	multiplyTest[0].matrix= storage1;

	int **storage2;
	storage2 = CreateNewMatrix(2, 3);
	storage2[0][0] = 3;
	storage2[0][1] = 3;
	storage2[0][2] = 3;
	storage2[1][0] = 7;
	storage2[1][1] = 7;
	storage2[1][2] = 7;

	multiplyTest[1].matrix = storage2;
	
	//// Real Addition Answers
	int **storage3;
	storage3 = CreateNewMatrix(2, 2);
	storage3[0][0] = 8;
	storage3[0][1] = 11;
	storage3[1][0] = 11;
	storage3[1][1] = 10;
	additionTest[0].matrix= storage3;

	/// Real Combined Answers
	int **storage4;
	storage4 = CreateNewMatrix(2, 2);
	storage4[0][0] = 17;
	storage4[0][1] = 17;
	storage4[1][0] = 38;
	storage4[1][1] = 39;
	additionTest[1].matrix= storage4;


	filer();			//retrives the matrices from the file
}


void MultiplicationTest()
{
	printf("%c[1;33m", 27);				//changes text color
	printf("\nMultiplication Test\n");
 	printf("%c[0m", 27);				//returns text color to normal

	///
	//Multiplication of 2 Matrices
	//


	printf("Matrix1 x Matrix3\n");


	///first test
	Operation_Choose(MATRIX[0],  MATRIX[2], '*');		//Operation chooser calls the mulitiplication function
	int i, j;



	//Assertion Test, if values differ the program will stop
	for ( i = 0; i< MATRIX[0].rows; i++)
	{
		for( j=0; j<MATRIX[2].cols; j++)
			assert(multiplyTest[0].matrix[i][j] == multiplyAnswer.matrix[i][j]);
	}


	printf("Matrix1 x Matrix5\n");
	//second test
    Operation_Choose(MATRIX[0],  MATRIX[4], '*');

    //Assertion Test, if values differ the program will stop
	for ( i = 0; i< MATRIX[0].rows; i++)
	{
		for( j=0; j<MATRIX[4].cols; j++)
			assert(multiplyTest[1].matrix[i][j] == multiplyAnswer.matrix[i][j]);
	}

	printf("%c[1;32m", 27);
	printf("PASSED\n");
	printf("%c[0m", 27);

}


void AdditionTest()
{
	printf("%c[1;33m", 27);
	printf("\nAddition Test\n");
	printf("%c[0m", 27);
	printf("Matrix1 + Matrix3 + Matrix4\n");			//as Operation chooser only accepts 2 matrices, addition of 3 matrices is done in 2 steps
	printf("Step 1 - Matrix1 + Matrix3\n");
	Operation_Choose(MATRIX[0],  MATRIX[2], '+');		//Operation chooser calls the addition function
	printf("Step2 - Answer + Matrix4\n");
	Operation_Choose(addiitonAnswer,  MATRIX[3], '+');	//Operation chooser calls the addition function

	int i, j;

	//Assertion Test, if values differ the program will stop
	for ( i = 0; i< MATRIX[0].rows; i++)
	{
		for( j=0; j<MATRIX[0].cols; j++)
			assert(additionTest[0].matrix[i][j] == addiitonAnswer.matrix[i][j]);
	}
	printf("%c[1;32m", 27);
	printf("PASSED\n");
	printf("%c[0m", 27);

}


void combinedTest()
{
	printf("%c[1;33m", 27);
	printf("\nCombined Test\n");
	printf("%c[0m", 27);
	printf("Matrix1 x Matrix3 + Matrix4\n");		//as Operation chooser only accepts 2 matrices, addition of 3 matrices is done in 2 steps
	printf("Step 1 - Matrix 1 x Matrix 3\n");
	Operation_Choose(MATRIX[0],  MATRIX[2], '*');	//Operation chooser calls the multiplication function
	printf("Step 2 - Answer + Matrix4 \n");
	Operation_Choose(multiplyAnswer,  MATRIX[3], '+');//Operation chooser calls the addition function

	int i, j;

	//Assertion Test, if values differ the program will stop
	for ( i = 0; i< MATRIX[0].rows; i++)
	{
		for( j=0; j<MATRIX[0].cols; j++)
			assert(additionTest[1].matrix[i][j] == addiitonAnswer.matrix[i][j]);
	}
	printf("%c[1;32m", 27);
	printf("PASSED\n");
	printf("%c[0m", 27);
}
