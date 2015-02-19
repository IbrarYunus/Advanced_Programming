//MatrixCALC
///Ibrar Yunus 
///v.1

///Uses C libraries from Linux
///May not compile under Windows Environment



#define _CRT_SECURE_NO_WARNINGS				
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MatrixCalc.h"
//#define _CRT_SECURE_NO_DEPRECATE
//#define _CRT_SECURE_NO_WARNINGS
//#pragma warning (disable : 4996)


//Struct to store a matrix and it's number of rows and cols
// struct matrices 
// {
// 	int rows;
// 	int cols;;
// 	int** matrix;
// };


// struct matrices MATRIX[300];			//Stores all the matrices as read from the file
// struct matrices multiplyAnswer;			//Stores answer to a multiplication
// struct matrices addiitonAnswer;
// struct matrices subtractionAnswer;

// void filer();							//reads from the file and populates the matrices struct array


////Function declarations
// void PrintMat(int **mat, int rows, int cols);
// void Operation_Choose( struct matrices mat1, struct matrices mat2, char choice);
// int** Subtraction(int **mat1, int **mat2, int rows, int cols);
// int** Addition(int **mat1, int **mat2, int rows, int cols);
// void Multiplication(int** mat1, int** mat2, int m, int q , int p);
// int**  CreateNewMatrix(int rows, int cols);




//Temporary- to be removed
// int main(void)
// {
// 	printf("****MATRIX CALC*****\n");
// 	filer();
// 	Operation_Choose(MATRIX[0],  MATRIX[2], '*');
// }








void filer()
{
	FILE *fp;
	char str[800];

	fp = fopen("file.txt", "r");

	//If file does not exist, exist the program
	if (fp == NULL) {
		perror("Error opening file");
	}

	/////Initialize the matrices iterator
	int iterator = 0;			//Used to iterate over the array of matrices
	int num;					//To temporary store a string (that contains a  number) form the file

	///Read matrices one by one from the file and realize them as a C structure

	while (fgets(str, 800, fp) != NULL) {		//the max line size can be 800 characters
		/// Extracing from file logic
		//puts(str);
		char temp[800];							/// backup buffer
		strcpy(temp, str);						

		char* token3;							//to store temporary tokenized strings
		char* token;
		char* token2;

		token = strtok(str, " ");				// to separate the number of rows
		token2 = strtok(NULL, " ");				// to separate the number of cols
		

		token = strtok(token, "ROWS:");			
		token2 = strtok(token2, "COLS:");

		//token2 = strtok(str, " ");
		//token2 = strtok(token2, "COLS: ");
		printf("MATRIX%d has Rows: %s  Cols: %s\n", iterator+1, token, token2);

		///Conver the dimension value to int ( to malloc later)
		int rows = atoi(token);					//everything read is read a strings, this is to convert them to numbers
		int cols = atoi(token2);
		
		/// Temporary storage to hold the numbers
		int *storage;							// stores all the numbers serially (for now)
		storage = malloc((rows*cols) * sizeof(int));

		token3 =  strtok(temp, " ");			//uses the backup string to extract the numbers

		token3 =  strtok(NULL, " ");

		//starts from here
		
		//token3 =  strtok(NULL, " ");
		//printf(" TEST %s \n ", token3);
		int a;	
		int checker = 1;						//to check the end of line delimeter

		for(a = 0; a < (rows * cols); a++)
		{
			token3 =  strtok(NULL, " ");		// in file the numbers are separated with spaces
			//printf("-%s-", token3);

			if( (strcmp(token3, ";\n")) == 0 && (checker >= (rows *cols))) 			//checks for the ending delimeter, if it is met unexpectedly, the program quits
				{
					printf("Abnormal matrix, EXITING\n");
					exit(0);
				}
			num = atoi(token3);

			storage[checker -1] = num;			//put the read and converted numbers into the serial array  of numbers

			checker++;

		}
		
		//For tsting
		// int i;
		// for(i = 0; i< (rows *cols); i++)
		// 	printf("%d", storage[i]);
	

		///Reserving the space for matrices
		MATRIX[iterator].matrix = malloc(rows * sizeof(int *));
		if (MATRIX[iterator].matrix == NULL)
		{
			printf("ERROR_ cannot allocate memory\n");
		}

		int i;

		//reserving space for the elements of a matrix
		for (i = 0; i < rows; i++)
		{
			MATRIX[iterator].matrix[i] = malloc(cols * sizeof(int));
			if (MATRIX[iterator].matrix[i] == NULL)
			{
				printf("ERROR_ cannot allocate memory\n");		
			}
		}


		///Inputing values in them
		//that is copying from the temporary serial array
		int y, u;
		int z = 0;
		for (y = 0; y < rows; y++)
		{
			for (u = 0; u < cols; u++)
			{
				MATRIX[iterator].matrix[y][u] = storage[z];
				z++;
			}
		}

		//cols and rows are stored for later checks in matrix operations
		MATRIX[iterator].rows = rows;
		MATRIX[iterator].cols = cols;

		// for (y = 0; y < rows; y++)
		// {
		// 	for (u = 0; u < cols; u++)
		// 	{
		// 		printf(" %d",MATRIX.matrix[iterator][y][u]);
		// 	}
		// 	printf("\n");
		// }
 
		//for debugging
		PrintMat(MATRIX[iterator].matrix, rows, cols);
		//printf("\nEND\n");
		iterator++;

	}

	printf("Total Matrices Found in File: %d", iterator);
	fclose(fp);
	getc(stdin);
	
}



void PrintMat(int **mat, int rows, int cols)	
{
		printf("\n");
		int y, u;
		for (y = 0; y < rows; y++)			///takes the rows and cols as parameters and uses them to print the matrix
		{
			for (u = 0; u < cols; u++)
			{
				printf(" %d",mat[y][u]);
			}
			printf("\n");
		}
}


void Operation_Choose(struct matrices mat1, struct matrices mat2,  char choice)
{
	if(choice == '+')						//Simple Operation chooser
	{
		if((mat1.rows != mat2.rows) || (mat1.cols != mat2.cols))
		printf("Addition not possible");

		else
			Addition(mat1.matrix, mat2.matrix, mat1.rows, mat1.cols);
	}
	else if(choice == '-')
	{
		if((mat1.rows != mat2.rows) || (mat1.cols != mat2.cols))
		printf("Subtraction not possible");

		else
			Subtraction(mat1.matrix, mat2.matrix, mat1.rows, mat1.cols);
	}
	else if(choice == '*')
	{
		if(mat1.cols != mat2.rows)
			printf("Matrices cannot be multiplied\n");
		else
			Multiplication(mat1.matrix, mat2.matrix, mat1.rows, mat2.cols, mat2.rows);

	}
	else
		printf("Unknown Option");

	printf("\n");
}




////////////
//Subtraction Function
////////////
int** Subtraction(int **mat1, int **mat2, int rows, int cols)
{
	int a, b;
	int **storage3;
	storage3 = CreateNewMatrix(rows, cols);

	for ( a= 0; a < rows; a++)////Iterates over rows
	{
		for ( b= 0; b < cols; b++)///Iterates over cols
		{
			storage3[a][b]  = mat1[a][b] - mat2[a][b];//actual subtraction logic
		}
	}

	subtractionAnswer.matrix = storage3;				//populating the multiplyAswer struct
	subtractionAnswer.rows = rows;
	subtractionAnswer.cols = cols;


	//printf("The first matrix is now over-written with the answer\n");
	PrintMat(subtractionAnswer.matrix, rows, cols);
}


////////////
//Addition Function
////////////
int** Addition(int **mat1, int **mat2, int rows, int cols)
{
	int a, b;
	int **storage3;
	storage3 = CreateNewMatrix(rows, cols);

	for ( a= 0; a < rows; a++)////Iterates over rows
	{
		for ( b= 0; b < cols; b++)///Iterates over cols
		{
			storage3[a][b] = mat1[a][b] + mat2[a][b];//actual addition logic
		}
	}

	addiitonAnswer.matrix = storage3;				//populating the multiplyAswer struct
	addiitonAnswer.rows = rows;
	addiitonAnswer.cols = cols;



	//printf("The first matrix is now over-written with the answer\n");
	PrintMat(addiitonAnswer.matrix, rows, cols);
}



//////////////
///Multiplication
/////////////
void Multiplication(int** mat1, int** mat2, int m, int q , int p)
{
	int i, j, k;				//rows of first matrix and col of second matric takena  parameter

	int **storage3;
	storage3 = CreateNewMatrix(p, q);


	int sum;				// the matrix to store the answer is zeroed to prevent inaccurate results
	for (i = 0; i<m; i++)
		for ( j = 0; j<p; j++)
			storage3[i][j] = 0;


	for ( i = 0; i<m; i++){ 		
		for ( j = 0; j<q; j++){ 
			sum = 0;
			for ( k = 0; k<p; k++)
				sum = sum + mat1[i][k] * mat2[k][j];		//actual multiplicaiton logic
			storage3[i][j] = sum;
		}
	}


	multiplyAnswer.matrix = storage3;				//populating the multiplyAswer struct
	multiplyAnswer.rows = p;
	multiplyAnswer.cols = q;

	PrintMat(storage3, p, q);
}



////////////
//Creates a new matrix
//mallocs memory for the matri elements
////////////
int**  CreateNewMatrix(int rows, int cols)
{
	int **matrix;
	matrix = malloc(rows * sizeof(int *));
	if (matrix == NULL)
	{
		printf("ERROR_ cannot allocate memory\n");
	}
	int i;
	for (i = 0; i < rows; i++)
	{
		matrix[i] = malloc(cols * sizeof(int));
		if (matrix[i] == NULL)
		{
			printf("ERROR_ cannot allocate memory\n");		
		}
	}

	return matrix;
}
