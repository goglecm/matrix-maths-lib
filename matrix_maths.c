#define KBLU  "\x1B[34m"		//Blue color
#define KNRM  "\x1B[0m"			//Black color
#define KRED  "\x1B[31m"		//Red color
#define INPUT_LENGTH 256		//Input maximum length
#define PI 3.14159265358979323846

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef long signed int largeInt;

typedef struct {
	largeInt col, row;
	double *mat;
} *matrix2D, matrix2DStruct;

typedef struct {
	double x, y, z;
} *point3D, point3DStruct;

typedef struct {
	double x, y;
} *point2D, point2DStruct;

typedef struct {
	point3D point;
	largeInt size;
} *object3D, object3DStruct;

typedef struct {
	point2D point;
	largeInt size;
} *object2D, object2DStruct;

//Print functions
char printErr(char errorCode, char attempts);
char print2DM(matrix2D m);
char print3DPoint(point3D p);
char print2DPoint(point2D p);
char print3DObject(object3D m);
char print2DObject(object2D m);

//Reading functions
char read2DM(matrix2D m);
char read2DMSize(matrix2D m);
char read2DMElem(matrix2D m);
char read3DPoint(point3D p);
char read2DPoint(point2D p);
char read3DObject(object3D m);
char read2DObject(object2D m);
largeInt getInt();
double getDouble();

//Conversion functions
double toDouble(char *s);
largeInt toInt(char *s);

//Calculations
char permutate(char *a);
double det2DM(matrix2D m);
matrix2D adjoint2DM(matrix2D m);
matrix2D invert2DM(matrix2D m);
matrix2D mlt2DM(matrix2D m1, matrix2D m2);
matrix2D add2DM(matrix2D m1, matrix2D m2);
matrix2D sub2DM(matrix2D m1, matrix2D m2);
object3D rotate3DS(object3D p, char axis, double angle);
object2D rotate2DS(object2D p, double angle);

//Memory allocation functions
matrix2D init2DM(largeInt rows, largeInt cols);
point3D init3DP(double x, double y, double z);
point2D init2DP(double x, double y);
object3D init3DObj(largeInt n);
object2D init2DObj(largeInt n);

//Memory deallocation functions
char free2DP(point2D p);
char free3DP(point3D p);
char free2DObj(object2D m);
char free3DObj(object3D m);
char free2DM(matrix2D m);

//Rendering functions
void renderMenu();

//MAIN
int main() {
	char choice, axis, attempts;
	matrix2D resultM, firstM, secondM;
	object2D first2Dobj, second2Dobj;
	object3D first3Dobj, second3Dobj;
	double angle;
	char inputString[INPUT_LENGTH];
	if ((resultM = init2DM(0, 0)) == '\0') {
		printErr(-1, 0);
		return 1;
	}
	if ((firstM = init2DM(0, 0)) == '\0') {
		printErr(-1, 0);
		return 1;
	}
	if ((secondM = init2DM(0, 0)) == '\0') {
		printErr(-1, 0);
		return 1;
	}
	if ((first2Dobj = init2DObj(0)) == '\0') {
		printErr(-1, 0);
		return 1;
	}
	if ((first3Dobj = init3DObj(0)) == '\0') {
		printErr(-1, 0);
		return 1;
	}
	if ((second2Dobj = init2DObj(0)) == '\0') {
		printErr(-1, 0);
		return 1;
	}
	if ((second3Dobj = init3DObj(0)) == '\0') {
		printErr(-1, 0);
		return 1;
	}
	do {
		renderMenu();
		for (attempts = 0, choice = 0; (choice < 1) || (choice > 10); attempts++) {
			if (attempts > 2) printErr(7, -1);
			if (attempts != 0) printErr(4, 3 - attempts);
			choice = getInt();
		}
		switch (choice) {
			case 1:
				puts("\nSize of first matrix:");
				if (read2DMSize(firstM) != 0) {
					printErr(-1, 0);
					break;
				}
				puts("\nSize of second matrix:");
				if (read2DMSize(secondM) != 0) {
					printErr(-1, 0);
					break;
				}
				if ((firstM->col != secondM->col) || (firstM->row != secondM->row)) {
					printErr(-1, 0);
					break;
				}
				puts("\nElements of first matrix: ");
				if (read2DMElem(firstM) != 0) {
					printErr(-1, 0);
					break;
				}
				puts("\nElements of second matrix");
				if (read2DMElem(secondM) != 0) {
					printErr(-1, 0);
					break;
				}
				if ((free2DM(resultM)) != 0) {
					printErr(-1, 0);
					return 1;
				}
				if ((resultM = add2DM(firstM, secondM)) == '\0') {
					printErr(-1, 0);
					break;
				}
				print2DM(resultM);
				break;
			case 2:
				puts("\nSize of first matrix:");
				if (read2DMSize(firstM) != 0) {
					printErr(-1, 0);
					break;
				}
				puts("\nSize of second matrix:");
				if (read2DMSize(secondM) != 0) {
					printErr(-1, 0);
					break;
				}
				if ((firstM->col != secondM->col) || (firstM->row != secondM->row)) {
					printErr(-1, 0);
					break;
				}
				puts("\nElements of first matrix: ");
				if (read2DMElem(firstM) != 0) {
					printErr(-1, 0);
					break;
				}
				puts("\nElements of second matrix");
				if (read2DMElem(secondM) != 0) {
					printErr(-1, 0);
					break;
				}
				if ((free2DM(resultM)) != 0) {
					printErr(-1, 0);
					return 1;
				}
				if ((resultM = sub2DM(firstM, secondM)) != '\0')
				print2DM(resultM);
				break;
			case 3:
				puts("\nSize of first matrix:");
				if (read2DMSize(firstM) != 0) {
					printErr(-1, 0);
					break;
				}
				puts("\nSize of second matrix:");
				if (read2DMSize(secondM) != 0) {
					printErr(-1, 0);
					break;
				}
				if (firstM->col != secondM->row) {
					printErr(-1, 0);
					break;
				}
				puts("\nElements of first matrix: ");
				if (read2DMElem(firstM) != 0) {
					printErr(-1, 0);
					break;
				}
				puts("\nElements of second matrix");
				if (read2DMElem(secondM) != 0) {
					printErr(-1, 0);
					break;
				}
				if ((free2DM(resultM)) != 0) {
					printErr(-1, 0);
					return 1;
				}
				if ((resultM = mlt2DM(firstM, secondM)) != '\0') print2DM(resultM);
				break;
			case 4:
				puts("\nPlease input desired character set:");
				scanf("%s", inputString);
				permutate(inputString);
				break;
			case 5:
				puts("\nSize of matrix: ");
				if (read2DMSize(firstM) != 0) break;
				if (firstM->col != firstM->row) {
					printErr(-1, 0);
					break;
				}
				if (read2DMElem(firstM) != 0) break;
				if ((free2DM(resultM)) != 0) {
					printErr(-1, 0);
					return 1;
				}
				if ((resultM = adjoint2DM(firstM)) != '\0')
				print2DM(resultM);
				break;
			case 6:
				if (read2DM(firstM) == 0) printf("\n\nDeterminant of this matrix is  %.3f \n\n", det2DM(firstM));
				break;
			case 7:
				puts("\nSize of matrix: ");
				if (read2DMSize(firstM) != 0) break;
				if (firstM->col != firstM->row) {
					printErr(-1, 0);
					break;
				}
				if (read2DMElem(firstM) != 0) break;
				if ((free2DM(resultM)) != 0) {
					printErr(-1, 0);
					return 1;
				}
				if ((resultM = invert2DM(firstM)) != '\0')
				print2DM(resultM);
				break;
			case 8:
				printf("\nPlease input angle in degrees: ");
				angle = getDouble();
				if (read2DObject(first2Dobj) != 0) {
					printErr(111, 0);
					break;
				}
				if ((free2DObj(second2Dobj)) != 0) {
					printErr(-1, 0);
					return 1;
				}
				if ((second2Dobj = rotate2DS(first2Dobj, angle)) == '\0') {
					printErr(111, 0);
					break;
				} else
				print2DObject(second2Dobj);
				break;
			case 9:
				printf("\nPlease input angle in degrees: ");
				angle = getDouble();
				printf("\nSelect the axis around which the rotation should be performed (X = 0, Y = 1 and Z = 2): ");
				for (attempts = 0, axis = -1; (axis < 0) || (axis > 2); attempts++) {
					if (attempts > 2) printErr(7, -1);
					if (attempts != 0) printErr(4, 3 - attempts);
					axis = getInt();
				}
				if (read3DObject(first3Dobj) != 0) {
					printErr(111, 0);
					break;
				}
				if ((free3DObj(second3Dobj)) != 0) {
					printErr(-1, 0);
					return 1;
				}
				if ((second3Dobj = rotate3DS(first3Dobj, axis, angle)) != '\0')
				print3DObject(second3Dobj);
				break;
			case 10:
				printErr(10, -1);
		}
		puts("Press any letter or digit and [Enter] to continue...");
		scanf("%s");
	} while (1);
	if ((free2DObj(second2Dobj)) != 0) {
		printErr(-1, 0);
		return 1;
	}
	if ((free2DObj(first2Dobj)) != 0) {
		printErr(-1, 0);
		return 1;
	}
	if ((free3DObj(second3Dobj)) != 0) {
		printErr(-1, 0);
		return 1;
	}
	if ((free3DObj(first3Dobj)) != 0) {
		printErr(-1, 0);
		return 1;
	}
	if ((free2DM(secondM)) != 0) {
		printErr(-1, 0);
		return 1;
	}
	if ((free2DM(firstM)) != 0) {
		printErr(-1, 0);
		return 1;
	}
	if ((free2DM(resultM)) != 0) {
		printErr(-1, 0);
		return 1;
	}
	return 0;
}

/*
Eliberates memory for a 2D point.
Returns 0 on success.
Returns 1 on failure.
*/
char free2DP(point2D p) {
	if (p == '\0') {
		printErr(-1, 0);
		return 1;
	}
	free(p);
	return 0;
}

/*
Eliberates memory for a 3D point.
Returns 0 on success.
Returns 1 on failure.
*/
char free3DP(point3D p) {
	if (p == '\0') {
		printErr(-1, 0);
		return 1;
	}
	free(p);
	return 0;
}

char free3DObj(object3D m) {
	largeInt i;
	if (m == '\0') {
		printErr(-1, 0);
		return 1;
	}
	for (i = 0; i < m->size; i++) {
		if (free3DP(m->point + i) != 0) {
			printErr(-1, 0);
			return 1;
		}
	}
	free(m);
	return 0;
}

char free2DObj(object2D m) {
	largeInt i;
	if (m == '\0') {
		printErr(-1, 0);
		return 1;
	}
	for (i = 0; i < m->size; i++) {
		if (free2DP(m->point + i) != 0) {
			printErr(-1, 0);
			return 1;
		}
	}
	free(m);
	return 0;
}

char free2DM(matrix2D m) {
	if (m == '\0') {
		printErr(-1, 0);
		return 1;
	}
	free(m->mat);
	free(m);
	return 0;
}

/*
Initialises a 2D point with the given parameters.
On success it returns a pointer to a valid 2D point.
On failure it returns null.
*/
point2D init2DP(double x, double y) {
	point2D p;
	if ((p = ((point2D)calloc(1, sizeof(point2DStruct)))) == '\0') {
		printErr(15, 0);
		return '\0';
	}
	p->x = x;
	p->y = y;
	return p;
}

/*
Initialises a 3D point with given parameters.
On success it returns a pointer to a valid 3D point.
On failure it returns null.
*/
point3D init3DP(double x, double y, double z) {
	point3D p;
	if ((p = ((point3D)calloc(1, sizeof(point3DStruct)))) == '\0') {
		printErr(15, 0);
		return '\0';
	}
	p->x = x;
	p->y = y;
	p->z = z;
	return p;
}

/*
Initialises a 2D matrix by allocating necessary memory and initialising the fields to valid memory locations.
On success it returns the pointer to a valid 2D matrix.
On failure it returns null.
*/
matrix2D init2DM(largeInt rows, largeInt cols) {
	matrix2D m;
	if ((m = ((matrix2D)calloc(1, sizeof(matrix2DStruct)))) == '\0') {
		printErr(6, 0);
		return '\0';
	}
	if ((m->mat = (double*)(calloc(rows * cols, sizeof(double)))) == '\0') {
		printErr(6, 0);
		return '\0';
	}
	m->col = cols;
	m->row = rows;
	return m;
}

/*
Initialises a 3D object with the number of points specified in the parameters.
On success it returns a pointer to a valid 3D object address.
On failure it returns null.
*/
object3D init3DObj(largeInt n) {
	object3D p;
	largeInt i;
	if ((p = (object3D)malloc(sizeof(object3DStruct))) == '\0') {
		printErr(100, 0);
		return '\0';
	}
	if ((p->point = (point3D)calloc(n, sizeof(point2DStruct))) == '\0') {
		printErr(100, 0);
		return '\0';
	}
	p->size = n;
	return p;
}

/*
Initialises a 2D object with the number of points specified in the parameters.
On success it returns a pointer to a valid 2D object address.
On failure it returns null.
*/
object2D init2DObj(largeInt n) {
	object2D p;
	void *point;
	largeInt i;
	if ((p = ((object2D)malloc(sizeof(object2DStruct)))) == '\0') {
		printErr(101, 0);
		return '\0';
	}
	if ((p->point = (point2D)calloc(n, sizeof(point2DStruct))) == '\0') {
		printErr(100, 0);
		return '\0';
	}
	p->size = n;
	return p;
}

/*
Displays the menu.
*/
void renderMenu() {
	puts(KBLU);
	puts("=====================================");
	puts("|            MENU                   |");
	puts("|  1. Add two matrices              |");
	puts("|  2. Subtract two matrices         |");
	puts("|  3. Multiply two matrices         |");
	puts("|  4. Character set permutations    |");
	puts("|  5. Matrix Adjoint                |");
	puts("|  6. Matrix determinant            |");
	puts("|  7. Matrix inverse                |");
	puts("|  8. 2 Dim matrix rotation         |");
	puts("|  9. 3 Dim matrix rotation         |");
	puts("| 10. Exit program                  |");
	puts("=====================================");
	puts(KNRM);
	printf("Please select one of these options: ");
}

/*
Reads the size and points of a 3D structure.
Returns 0 on success.
Returns 1 on failure.
*/
char read3DObject(object3D m) {
	char attempts = 0;
	largeInt i, size;
	printf("\nPlease input the number of 3D points: ");
	for (size = 0; size <= 0; attempts++) {
		if (attempts > 2) printErr(7, -1);
		if (attempts != 0) printErr(5, 3 - attempts);
		size = getInt();
	}
	if ((free3DObj(m)) != 0) {
		printErr(-1, 0);
		return 1;
	}
	if ((m = init3DObj(size)) == '\0') {
		printErr(6, 0);
		return 1;
	}
	putchar('\n');
	for (i = 0; i < size; i++) {
		printf("\nPoint # %d:", i + 1);
		if (read3DPoint(m->point + i) != 0) {
			printErr(103, 0);
			return 1;
		}
	}
	return 0;
}

/*
Reads the size and points of a 2D structure.
Returns 0 on success.
Returns 1 on failure.
*/
char read2DObject(object2D m) {
	char attempts = 0;
	largeInt i, size;
	if (m == '\0') {
		printErr(104, 0);
		return 1;
	}
	printf("\nPlease input the number of 2D points: ");
	for (size = 0; size <= 0; attempts++) {
		if (attempts > 2) printErr(7, -1);
		if (attempts != 0) printErr(5, 3 - attempts);
		size = getInt();
	}
	if ((free2DObj(m)) != 0) {
		printErr(-1, 0);
		return 1;
	}
	if ((m = init2DObj(size)) == '\0') {
		printErr(6, 0);
		return 1;
	}
	putchar('\n');
	for (i = 0; i < size; i++) {
		printf("\nInput point # %d: ", i + 1);
		if (read2DPoint(m->point + i) != 0) {
			printErr(105, 0);
			return 1;
		}
	}
	return 0;
}

/*
Prints the coordinates of a 3D point.
Returns 0 on success.
Returns 1 on failure.
*/
char print3DPoint(point3D p) {
	if (p == '\0') {
		printErr(106, 0);
		return 1;
	}
	printf("\nThe 3D point X, Y and Z coordintates are: %.3f, %.3f and %.3f\n", p->x, p->y, p->z);
	return 0;
}

/*
Prints the coordinates of a 2D point.
Returns 0 on success.
Returns 1 on failure.
*/
char print2DPoint(point2D p) {
	if (p == '\0') {
		printErr(107, 0);
		return 1;
	}
	printf("The 2D point X and Y coordintates are: %.3f and %.3f\n", p->x, p->y);
	return 0;
}

/*
Prints the coordinates the 2D points of a 2D structure.
Returns 0 on success.
Returns 1 on failure.
*/
char print2DObject(object2D p) {
	largeInt i;
	if (p == '\0') {
		printErr(104, 0);
		return 1;
	}
	printf("\nA 2D structure of %d points:\n\n", p->size);
	for (i = 0; i < p->size; i++) {
		if ((p->point + i) == '\0') {
			printErr(102, 0);
			return 1;
		}
		if (print2DPoint(p->point + i) != 0) {
			printErr(108, 0);
			return 1;
		}
	}
	putchar('\n');
	return 0;
}

/*
Prints the coordinates the 3D points of a 3D structure.
Returns 0 on success.
Returns 1 on failure.
*/
char print3DObject(object3D p) {
	largeInt i;
	if (p == '\0') {
		printErr(102, 0);
		return 1;
	}
	printf("\nA 3D structure of %d points:\n\n", p->size);
	for (i = 0; i < p->size; i++) {
		if (p->point == '\0') {
			printErr(106, 0);
			return 1;
		}
		if (print3DPoint(p->point + i) != 0) {
			printErr(109, 0);
			return 1;
		}
	}
	putchar('\n');
	return 0;
}
/*
Reads the coordinates of a 3D point.
Returns zero on success.
Returns 1 on failure.
*/
char read3DPoint(point3D p) {
	if (p == '\0') {
		printErr(106, 0);
		return 1;
	}
	printf("\nInput point X-coordinate: ");
	p->x = getDouble();
	printf("\nInput point Y-coordinate: ");
	p->y = getDouble();
	printf("\nInput point Z-coordinate: ");
	p->z = getDouble();
	putchar('\n');
	return 0;
}

/*
Reads the coordinates of a 2D point.
Returns zero on success.
Returns 1 on failure.
*/
char read2DPoint(point2D p) {
	if (p == '\0') {
		printErr(107, 0);
		return 1;
	}
	printf("\nInput point X-coordinate: ");
	p->x = getDouble();
	printf("\nInput point Y-coordinate: ");
	p->y = getDouble();
	putchar('\n');
	return 0;
}

/*
Displays the elements of a 2D matrix.
Returns 0 on success.
Returns 1 on failure.
*/
char print2DM(matrix2D m) {
	largeInt i, j;
	if (m == '\0') {
		printErr(8, 0);
		return 1;
	}
	if ((m->col != 0) || (m->row == 0))
		if (m->mat == '\0') {
			printErr(8, 0);
			return 1;
		}
	printf("\nA %d by %d matrix:", m->row, m->col);
	putchar('\n');
	for (i = 0; i < m->row; i++) {
		for (j = 0; j < m->col; j++)
			printf("\t%7.3f\t", *(m->mat + (i * m->row) + j));
		puts("\n\n");
	}
	return 0;
}

/*
Reads all fields of a 2D matrix.
Returns 0 on success.
Returns 1 on failure.
*/
char read2DM(matrix2D m) {
	char attempts = 0;
	largeInt i, j;
	if (m == '\0') {
		printErr(16, 0);
		return 1;
	}
	if (read2DMSize(m) != 0) {
		printErr(110, 0);
		return 1;
	}
	if (read2DMElem(m) != 0) {
		printErr(111, 0);
		return 1;
	}
	return 0;
}

/*
Reads all the elements of a 2D matrix.
Returns zero on success.
Returns 1 on failure.
*/
char read2DMElem(matrix2D m) {
	largeInt i, j, cols, rows;
	if (m == '\0') {
		printErr(16, 0);
		return 1;
	}
	cols = m->col;
	rows = m->row;
	if ((free2DM(m)) != 0) {
		printErr(-1, 0);
		return 1;
	}
	if ((m = init2DM(rows, cols)) == '\0') {
		printErr(-1, 0);
		return 1;
	}
	for (i = 0; i < m->row; i++)
		for (j = 0; j < m->col; j++) {
			printf("\nInput M[%d][%d]: ", i, j);
			*(m->mat + (i * m->row) + j) = getDouble();
		}
	return 0;
}

/*
Reads the size of a 2D matrix.
Returns zero on success.
Returns 1 on failure.
*/
char read2DMSize(matrix2D m) {
	char attempts = 0;
	if (m == '\0') {
		printErr(112, 0);
		return 1;
	}
	printf("\nInput number of rows of the matrix: ");
	for (m->row = 0; m->row <= 0; attempts++) {
		if (attempts > 2) printErr(7, -1);
		if (attempts != 0) printErr(5, 3 - attempts);
		m->row = getInt();
	}
	printf("\nInput number of columns of the matrix: ");
	for (m->col = 0, attempts = 0; m->col <= 0; attempts++) {
		if (attempts > 2) printErr(7, -1);
		if (attempts != 0) printErr(5, 3 - attempts);
		m->col = getInt();
	}
	return 0;
}

/*`
Adds two 2D matrices and stores the result in the third matrix.
Return 0 on success.
Return 1 on failure.
*/
matrix2D add2DM(matrix2D m1, matrix2D m2) {
	largeInt i, j, k;
	matrix2D rm;
	if (m1 == '\0') {
		printErr(112, 0);
		return '\0';
	}
	if (m2 == '\0') {
		printErr(112, 0);
		return '\0';
	}
	if (m1->col != m2->row) {
		printErr(3, 0);
		return '\0';
	}
	if ((rm = init2DM(m1->row, m1->col)) == '\0') {
		printErr(-1, 0);
		return '\0';
	}
	for (i = 0; i < rm->row; i++)
		for (j = 0; j < rm->col; j++)
			*(rm->mat + (i * rm->row) + j) = (*(m1->mat + (i * m1->row) + j)) + *(m2->mat + (i * m2->row) + j);
	return rm;
}

/*
Subtracts two 2D matrices and stores the result in the third matrix.
Return 0 on success.
Return 1 on failure.
*/
matrix2D sub2DM(matrix2D m1, matrix2D m2) {
	largeInt i, j, k;
	matrix2D rm;
	if (m1 == '\0') {
		printErr(112, 0);
		return '\0';
	}
	if (m2 == '\0') {
		printErr(112, 0);
		return '\0';
	}
	if (m1->col != m2->row) {
		printErr(3, 0);
		return '\0';
	}
	if ((rm = init2DM(m1->row, m1->col)) == '\0') {
		printErr(-1, 0);
		return '\0';
	}
	for (i = 0; i < m1->row; i++)
		for (j = 0; j < m1->col; j++)
			*(rm->mat + (i * rm->row) + j) = (*(m1->mat + (i * m1->row) + j)) - (*(m2->mat + (i * m2->row) + j));
	return rm;
}

/*
Multiplies two 2D matrices and returns the result.
Returns the matrix pointer on success.
Returns null on failure.
*/
matrix2D mlt2DM(matrix2D m1, matrix2D m2) {
	largeInt i, j, k;
	matrix2D rm;
	if (m1 == '\0') {
		printErr(112, 0);
		return '\0';
	}
	if (m2 == '\0') {
		printErr(112, 0);
		return '\0';
	}
	if (m1->col != m2->row) {
		printErr(3, 0);
		return '\0';
	}
	if ((rm = init2DM(m1->row, m2->col)) == '\0') {
		printErr(-1, 0);
		return '\0';
	}
	for (i = 0; i < rm->row; i++)
		for (j = 0; j < rm->col; j++) {
			*(rm->mat + (i * rm->row) + j) = 0;
			for (k = 0; k < m1->col; k++)
				*(rm->mat + (i * rm->row) + j) += (*(m1->mat + (i * m1->row) + k)) * (*(m2->mat + (k * m2->row) + j));
		}
	return rm;
}

/*
Displays an error or a warning message for the error/warning specified by errorCode.
For attempts = -1, exit the program.
Returns 0 on success.
Returns 1 on failure.
*/
char printErr(char errorCode, char attempts) {
	puts(KRED);
	switch (errorCode) {
	case -1:
		fputs("Undefined error.", stderr);
		break;
	case 1:
		fputs("Error 001: Addition cannot be performed. Matrices do not have equal size.", stderr);
		break;
	case 2:
		fputs("Error 002: Subtraction cannot be performed. Matrices do not have equal size.", stderr);
		break;
	case 3:
		fputs("Error 003: Multiplication cannot be performed. Matrices do not have the correct size.", stderr);
		break;
	case 4:
		fprintf(stderr, "Error 004: Illegal input (%d attempts left). Please insert a legal input.", attempts);
		break;
	case 5:
		fprintf(stderr, "Error 005: Illegal array size (%d attempts left). Please insert a legal array size here.", attempts);
		break;
	case 6:
		fputs("Error 006: Unable to allocate memory for the matrix.", stderr);
		break;
	case 7:
		fputs("Error 007: Too many invalid attempts. Good Bye!", stderr);
		break;
	case 8:
		fputs("Error 008: Unable to print. Invalid matrix.", stderr);
		break;
	case 10:
		puts("\nGood Bye!");
		puts(KNRM);
		exit(0);
		break;
	case 11:
		fputs("Error 011: Unable to allocate memory for the character set temporary storage.", stderr);
		break;
	case 12:
		fputs("Error 012: Unable to compute the determinant. Matrix is not square.", stderr);
		break;
	case 13:
		fputs("Error 013: Undefined matrix.", stderr);
		break;
	case 14:
		fputs("Error 014: Inversion cannot be performed. Determinant equals zero.", stderr);
		break;
	case 15:
		fputs("Error 015: Unable to initialise matrix. Undefined matrix.", stderr);
		break;
	case 16:
		fputs("Error 016: Unable to read matrix. Undefined matrix.", stderr);
		break;
	case 100:
		fputs("Error 100: Unable to initialise 3d object.", stderr);
		break;
	case 101:
		fputs("Error 101: Unable to initialise 2d object.", stderr);
		break;
	case 102:
		fputs("Error 102: Undefined 3d object.", stderr);
		break;
	case 103:
		fputs("Error 103: Unable to read 3D point.", stderr);
		break;
	case 104:
		fputs("Error 104: Undefined 2D Object.", stderr);
		break;
	case 105:
		fputs("Error 105: Unable to read 2D point.", stderr);
		break;
	case 106:
		fputs("Error 106: Undefined 3D point.", stderr);
		break;
	case 107:
		fputs("Error 107: Undefined 2D point.", stderr);
		break;
	case 108:
		fputs("Error 108: Unable to print 2D point.", stderr);
		break;
	case 109:
		fputs("Error 109: Unable to print 3D point.", stderr);
		break;
	case 110:
		fputs("Error 110: Unable to read matrix size.", stderr);
		break;
	case 111:
		fputs("Error 111: Unable to read matrix elemnts.", stderr);
		break;
	case 112:
		fputs("Error 112: Undefined matrix.", stderr);
		break;
	case 113:
		fputs("Error 113: Unable to initialise Matrix.", stderr);
		break;
	case 114:
		fputs("Error 114: Unable to compute adjoint.", stderr);
		break;
	case 115:
		fputs("Error 115: Unable to muliply matrix.", stderr);
		break;
	default:
		fputs("Error 000: Invalid error code.", stderr);
		return 1;
	}
	puts(KNRM);
	if (attempts == -1) abort();
	return 0;
}

/*
Reads a valid natural number. If invalid input is entered more than 3 times, the program terminates.
Returns the read number.
*/
largeInt getInt() {
	char in[INPUT_LENGTH], attempts = 0, checker = 1, i = -1;
	for (; ((checker != 0) || ((in[0] == '-') && (in[1] == '\0'))); ++attempts, i = -1) {
		if (attempts > 2) printErr(7, -1);
		if (attempts != 0) printErr(4, 3 - attempts);
		scanf("%s", in);
		for (i += (in[0] == '-'), checker = 0; in[++i] != '\0'; checker += ((in[i] > '9') || (in[i] < '0')));
	}
	return toInt(in);
}

/*
Reads a valid real floating point number. If invalid input is entered more than 3 times, the program terminates.
Returns the read number.
*/
double getDouble() {
	char in[INPUT_LENGTH], i, decPoint, negSign, checker, attempt = 0;
	for (; ; attempt++) {
		if (attempt > 2) printErr(7, -1);
		if (attempt != 0) printErr(4, 3 - attempt);
		scanf("%s", in);
		for (i = 0, decPoint = 0, negSign = 0, checker = 0; in[i] != '\0'; i++)
			if (in[i] == '.') decPoint++;
			else
			if (in[i] == '-') negSign++;
			else
			if ((in[i] > '9') || (in[i] < '0')) checker++;
		//This is the boolean expression to check wether a string of characters is a float or not
		if ((checker == 0) && (decPoint < 2) && (negSign < 2) && ((i && (in[0] == '-') && negSign && (decPoint == 0)) || ((decPoint == 0) && (negSign == 0) && (i > -1)) || (decPoint && negSign && (i > 2) && (in[0] == '-') && (in[1] != '.') && (in[i - 1]) != '.') || (i > 1) && (negSign == 0) && (decPoint == 1) && (in[0] != '.') && (in[i - 1] != '.')))
			return toDouble(in);
	}
}

/*
Converts string to a long int.
Returns the long int.
*/
largeInt toInt(char *s) {
	char i;
	largeInt num = 0;
	for (s += (i = (*s == '-')); *s != '\0'; num = num * 10 + *s - 48, s++);
	return (i ? (-num) : num);
}

/*
Converts string to a double.
Returns the double.
*/
double toDouble(char *s) {
	char j = -1, i, k = 0;
	double numInt = 0, numFlt  = 0;
	s += (i = (*s == '-'));
	while ((s[k] != '.') && (s[k] != '\0')) k++;
	if (s[k] == '\0') return (i ? (-toInt(s)) : (toInt(s)));
	else {
		for (; ++j != k; numInt = numInt * 10 + s[j] - 48);
		for (; s[j] != '\0'; j++);
		for (; --j != k; numFlt = (numFlt + s[j] - 48) / 10);
		return (i ? (-(numInt + numFlt)) : (numInt + numFlt));
	}
}

/*
Prints all possible combinations of the string from the arguments.
Returns 0 on success.
Returns 1 on failure.
*/
char permutate(char *a) {
	int n = 0, *indexer, i = 0, j, swap;
	if (a == '\0') {
		printErr(11, 0);
		return 1;
	}
	while (*(a + n) !='\0') n++;
	if ((indexer = (int *)malloc(sizeof(int) * (n + 1))) == '\0') {
		printErr(11, 0);
		return 1;
	}
	for (; i <= n; *(indexer + i) = i, i++);
	puts("All permutations:");
	for (i = 1; i < n;) {
		printf("%s\n", a);
		*(indexer + i) -= 1;
		if (i % 2) j = *(indexer + i);
		else j = 0;
		swap = *(a + j);
		*(a + j) = *(a + i);
		*(a + i) = swap;
		i = 0;
		while (*(indexer + i) == 0) *(indexer + i) = i++;
	}
	free(indexer);
	printf("%s\n\n", a);
	return 0;
}

/*
Calculates the determinant of a square matrix recursively.
Returns the determinant value on success.
Returns 0 on failure (and sometimes on success).
*/
double det2DM(matrix2D m) {
	largeInt i, j, k, p;
	double tempSum = 0;
	matrix2D nextM;
	/*Check if input matrix is valid*/
	if (m == '\0') {
		printErr(13, 0);
		return 0;
	}
	/*Check if matrix is square*/
	if (m->col != m->row) {
		printErr(12, 0);
		return 0;
	}
	switch (m->col) {
		case 1:
			return *m->mat;
		case 2:
			return (*(m->mat) * *(m->mat + 3) - *(m->mat +1) * *(m->mat + 2));
		default:
			if ((nextM = init2DM(m->row - 1, m->col - 1)) == '\0') {
					printErr(6, 0);
					return 0;
				}
			for (i = 0; i < m->col; i++) {
				//Allocate memory for temp array
				//Create temp array
				for (j = 1, p = 0; j < m->row; j++) {
					for (k = 0; k < m->col; k++)
						if (k != i) {
							*(nextM->mat + p) = *(m->mat + (j * m->row) + k);
							p++;
						}
				}
				//Check if an element in the top row is 0 and builds up the sum of cofactors aka determinant and sub-determinant
				if (*(m->mat + i) != 0) tempSum += *(m->mat + i) * det2DM(nextM) * (((i % 2) == 1) ? (-1) : 1);
			}
			//Eliberate temp storage
			if ((free2DM(nextM)) != 0) {
				printErr(-1, 0);
			return 0;
			}
			return tempSum;
	}
}

/*
Creates the adjoint of a matrix.
On success, it returns a the adjoint matrix.
On failure, it returns null.
*/
matrix2D adjoint2DM(matrix2D m) {
	largeInt i, j, k, p, r, q;
	double swap;
	matrix2D innerM, result;
	//Check is matrix is valid
	if (m == '\0') {
		printErr(13, 0);
		return '\0';
	}
	//Check is matrix is square
	if (m->col != m->row) {
		printErr(12, 0);
		return '\0';
	}
	//Allocate memory for resultant matrix
	if ((result = init2DM(m->row, m->col)) == '\0') {
		printErr(6, 0);
		return '\0';
	}
	//Allocate memory for temp array holding the minors
	if ((innerM = init2DM(m->row - 1, m->col - 1)) == '\0') {
		printErr(6, 0);
		return '\0';
	}
	//Browse each element from matrix using i, r, for rows and cols respectively
	for (i = 0; i < m->row; i++)
		for (r = 0; r < m->col; r++) {
			//Consider each element from the matrix and build its minor in the temp array
			for (j = 0, p = 0; j < m->row; j++)
				for (k = 0; k < m->col; k++)
					if ((j != i) && (k != r)) {
						*(innerM->mat + p) = *(m->mat + (j * m->row) + k);
						p++;
					}
			//Create the resultant matrix of cofactros
			*(result->mat + (result->row * i) + r) = det2DM(innerM) * ((((i + r) % 2) == 1) ? (-1) : (1));
		}
	//Eliberate fully the temp array
	if ((free2DM(innerM)) != 0) {
		printErr(-1, 0);
		return '\0';
	}
	//Transpose resultant array
	for (i = 0; i < result->row; i++)
		for (j = i; j < result->col; j++) {
			swap = *(result->mat + (result->row * i) + j);
			*(result->mat + (result->row * i) + j) = *(result->mat + (result->row * j) + i);
			*(result->mat + (result->row * j) + i) =  swap;
		}
	return result;
}

/*
Determines the inverse of a square matrix.
Returns the resultant matrixon success.
Returns null on failure.
*/
matrix2D invert2DM(matrix2D m) {
	double determinant;
	largeInt i, j;
	matrix2D result;
	//Check if matrix is valid
	if (m == '\0') {
		printErr(13, 0);
		return '\0';
	}
	//Compute and check if determinant is zero
	if ((determinant = det2DM(m)) == 0) {
		printErr(14, 0);
		return '\0';
	}
	//Allocate memory and initialise resultant matrix
	if ((result = init2DM(m->row, m->col)) == '\0') {
		printErr(6, 0);
		return '\0';
	}
	//Get the adjoint and multiply by the determinant
	if ((result = adjoint2DM(m)) == '\0') {
		printErr(114, 0);
		return '\0';
	}
	for (i = 0; i < result->row; i++)
		for (j = 0; j< result->col; j++)
			*(result->mat + (result->row * i) + j) /= determinant;
	return result;
}

/*
Rotates a 3D structure by accepting a 3D point, the angle and the axis (0 = X, 1 = Y, 2 = Z) upon which it should be rotated.
Returns a 3D object on success.
Returns null on failure.
*/
object3D rotate3DS(object3D p, char axis, double angle) {
	matrix2D m, k, result;
	object3D newObj;
	largeInt i = 0, j = 0;
	angle = (angle / 180) * PI;
	if (p == '\0') {
		printErr(112, 0);
		return '\0';
	}
	if ((m = init2DM(p->size, 3)) == '\0') {
		printErr(6, 0);
		return '\0';
	}
	if ((k = init2DM(3, 3)) == '\0') {
		printErr(6, 0);
		return '\0';
	}
	//Build coordinate matrix
	for (; i < p->size; i++, j += 3) {
		*(m->mat + j) = (p->point + i)->x;
		*(m->mat + j + 1) = (p->point + i)->y;
		*(m->mat + j + 2) = (p->point + i)->z;
	}
	//Build transform matrix
	switch (axis) {
		case 0:
			*k->mat = 1;
			*(k->mat + 1) = 0;
			*(k->mat + 2) = 0;
			*(k->mat + 3) = 0;
			*(k->mat + 4) = cos(angle);
			*(k->mat + 5) = -sin(angle);
			*(k->mat + 6) = 0;
			*(k->mat + 7) = sin(angle);
			*(k->mat + 8) = cos(angle);
			break;
		case 1:
			*k->mat = cos(angle);
			*(k->mat + 1) = 0;
			*(k->mat + 2) = sin(angle);
			*(k->mat + 3) = 0;
			*(k->mat + 4) = 1;
			*(k->mat + 5) = 0;
			*(k->mat + 6) = -sin(angle);
			*(k->mat + 7) = 0;
			*(k->mat + 8) = cos(angle);
			break;
		case 2:
			*k->mat = cos(angle);
			*(k->mat + 1) = -sin(angle);
			*(k->mat + 2) = 0;
			*(k->mat + 3) = sin(angle);
			*(k->mat + 4) = cos(angle);
			*(k->mat + 5) = 0;
			*(k->mat + 6) = 0;
			*(k->mat + 7) = 0;
			*(k->mat + 8) = 1;
			break;
		default:
			return '\0';
	}
	if ((result = mlt2DM(m, k)) == '\0') {
		printErr(115, 0);
		return '\0';
	}
	if ((free2DM(m)) != 0) {
		printErr(-1, 0);
		return '\0';
	}
	if ((free2DM(k)) != 0) {
		printErr(-1, 0);
		return '\0';
	}
	if ((newObj = init3DObj(p->size)) == '\0') {
		printErr(100, 0);
		return '\0';
	}
	for (i = 0, j = 0; i < p->size; i++, j += 3) {
		(newObj->point + i)->x = *(result->mat + j);
		(newObj->point + i)->y = *(result->mat + j + 1);
		(newObj->point + i)->z = *(result->mat + j + 2);
	}
	if ((free2DM(result)) != 0) {
		printErr(-1, 0);
		return '\0';
	}
	return newObj;
}

/*
Rotates a 2D structure by accepting a 2D point and the angle.
Returns a 2D matrix on success.
Returns null on failure.
*/
object2D rotate2DS(object2D p, double angle) {
	matrix2D m, k, result;
	object2D newObj;
	largeInt i = 0, j = 0;
	angle = (angle / 180) * PI;
	if (p == '\0') {
		printErr(112, 0);
		return '\0';
	}
	if ((m = init2DM(p->size, 2)) == '\0') {
		printErr(6, 0);
		return '\0';
	}
	if ((k = init2DM(2, 2)) == '\0') {
		printErr(6, 0);
		return '\0';
	}
	//Building the coordinate matrix set
	for (; i < p->size; i++, j += 2) {
		*(m->mat + j) = (p->point + i)->x;
		*(m->mat + j + 1) = (p->point + i)->y;
	}
	//Building tranfsorm matrix
	*k->mat = cos(angle);
	*(k->mat + 1) = -sin(angle);
	*(k->mat + 2) = sin(angle);
	*(k->mat + 3) = cos(angle);
	//Do mutiplication
	if ((result = mlt2DM(m, k)) == '\0') {
		printErr(115, 0);
		return '\0';
	}
	if ((free2DM(m)) != 0) {
		printErr(-1, 0);
		return '\0';
	}
	if ((free2DM(k)) != 0) {
		printErr(-1, 0);
		return '\0';
	}
	if ((newObj = init2DObj(p->size)) == '\0') {
		printErr(100, 0);
		return '\0';
	}
	for (i = 0, j = 0; i < p->size; i++, j += 2) {
		(newObj->point + i)->x = *(result->mat + j);
		(newObj->point + i)->y = *(result->mat + j + 1);
	}
	if ((free2DM(result)) != 0) {
		printErr(-1, 0);
		return '\0';
	}
	return newObj;
}
