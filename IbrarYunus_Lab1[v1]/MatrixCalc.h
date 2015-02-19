struct matrices 
{
	int rows;
	int cols;;
	int** matrix;
};


struct matrices MATRIX[300];			//Stores all the matrices as read from the file
struct matrices multiplyAnswer;			//Stores answer to a multiplication
struct matrices addiitonAnswer;
struct matrices subtractionAnswer;

void filer();							//reads from the file and populates the matrices struct array

void PrintMat(int **mat, int rows, int cols);
void Operation_Choose( struct matrices mat1, struct matrices mat2, char choice);
int** Subtraction(int **mat1, int **mat2, int rows, int cols);
int** Addition(int **mat1, int **mat2, int rows, int cols);
void Multiplication(int** mat1, int** mat2, int m, int q , int p);
int**  CreateNewMatrix(int rows, int cols);
