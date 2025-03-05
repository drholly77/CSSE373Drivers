#include "Wrapper.h"
#include "SRMatrix.h"



int main (int argc, char* argv[]) 
{
	MatrixOfStudents sa; 

	cout << "Student Names" << endl; 
	for (int row = rowLower; row <= rowUpper; row++) { 
		for (int col = columnLower; col <= columnUpper; col++) { 
			cout << sa[row][col].name << endl; 
		} // end for 
	} // end for 
	cout << endl; 

	return 0;
}