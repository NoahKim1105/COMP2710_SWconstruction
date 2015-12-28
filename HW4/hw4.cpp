// Program to take in two input files with a sorted list of ints
// and sort them into one merged list and output the merged list
// to a file. 
// COMP2710 Homework 4
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: hw4.cpp
// Written in Vi text editor, compiled with g++ -o hw4 hw4.cpp
// Version: 2/19/2015, v1
// Sources used: Dr. Qin's source for pressanykey.cpp

#include <iostream>
#include <fstream>
#include <assert.h>
#include <cstdlib>
// Include statements needed for press_any_key
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
using namespace std;
 
// Function to read in data from a file
// Input: (1) Array storing data retrieved from file (inStream)
// 	  (2) Input file stream object
// Output: Size of array
int readFile(int inputArray[], ifstream& inStream);

// Function to sort the two input arrays into one array
// Input: (1 and 3) Input arrays containing data
// 	  (2 and 4) Input arrays sizes
// 	  (5) Array to hold sorted values
// Output: Size of output array
int sort(int inputArray1[], int inputArray1_size, int inputArray2[],
		int inputArray2_size, int outputArray[]);

// Function to write output data into a file
// Input: (1) Output array
// 	  (2) Output array size
void writeFile(int outputArray[], int outputArray_size);

// Define unit test functions for functions declared above
void test_readFile(void);
void test_sort(void);
void test_writeFile(void);
 
// Functions to implement press_any_key
int mygetch(void);
void press_any_key(void);

// Define constant for max size of input arrays
const int MAX_SIZE = 100;

int main() {
	// Declare variables
	ifstream inStream; // Object to hold input stream
	char filename1[MAX_SIZE], filename2[MAX_SIZE]; // Char array for filenames
	int inputArray1[MAX_SIZE], inputArray2[MAX_SIZE], outputArray[2 * MAX_SIZE];
	int inputArray1_size, inputArray2_size, outputArray_size;

	// Start printing user interface
	cout << "*** Unit Test Cases ***\n";
	
	// Run unit tests for all three functions
	test_readFile();
	test_sort();
	test_writeFile();

	// Begin actual sorting program
	cout << "*** Welcome to Mark Gallagher's sorting program ***\n";
	cout << "Enter the first input file name: ";
	cin >> filename1;
	
	inStream.open(filename1);
	if (inStream.fail()) {
		cout << "File open failed. Terminating.\n";
		exit(1);
	}

	inputArray1_size = readFile(inputArray1, inStream);
	
	cout << "The list of " << inputArray1_size << " numbers in file " << filename1 << " is:\n";
	// Print numbers in first array
	for (int i = 0; i < inputArray1_size; i++) {
		cout << inputArray1[i] << endl;
	}

	// Obtain second file
	cout << "\nEnter the second input file name: ";
	cin >> filename2;

	inStream.open(filename2);
	if (inStream.fail()) {
		cout << "File open failed. Terminating.\n";
		exit(1);
	}	
	
	inputArray2_size = readFile(inputArray2, inStream);

	cout << "The list of " << inputArray2_size << " numbers in file " << filename2 << " is:\n";
	for (int i = 0; i < inputArray2_size; i++) {
		cout << inputArray2[i] << endl;
	}

	// Sort the two arrays
	outputArray_size = sort(inputArray1, inputArray1_size, inputArray2, inputArray2_size, outputArray);

	// Print results
	cout << "\nThe sorted list of " << outputArray_size << " numbers is: ";
	for (int i = 0; i < outputArray_size; i++) {
		cout << outputArray[i] << " ";
	}
	cout << endl;
	
	// Write results to an output file
	writeFile(outputArray, outputArray_size);

	cout << "*** Goodbye ***\n";

	return 0;
}

int readFile(int inputArray[], ifstream& inStream) {
	int next;
	int i = 0;
	while (inStream >> next) {
		inputArray[i] = next;
		i++;
	}

	inStream.close(); // Close file stream when done
	
	return i;
}

int sort(int inputArray1[], int inputArray1_size, int inputArray2[],
		int inputArray2_size, int outputArray[]) {
	// Declare indices to keep track of location within arrays
	int index1 = 0;
	int index2 = 0;
	int index3 = 0;

	// Begin processing both arrays for "normal" cases (indices not at end of arrays)
	while (index1 < inputArray1_size && index2 < inputArray2_size) {
		if (inputArray1[index1] < inputArray2[index2]) {
			outputArray[index3] = inputArray1[index1];
			index1++;
			index3++;
		}
		else {
			outputArray[index3] = inputArray2[index2];
			index2++;
			index3++;
		}
	}
	
	// Case where reached end of array 1, copy rest of array 2 into output
	if (index1 == inputArray1_size) {
		for (int i = index2; i < inputArray2_size; i++) {
			outputArray[index3] = inputArray2[i];
			index3++; // do not need to increment index2, now represented by i
		}
	}
	// Case where reached end of array 2
	else {
		for (int i = index1; i < inputArray1_size; i++) {
			outputArray[index3] = inputArray1[i];
			index3++;
		}
	}
		
	// Assertion - just to be sure sizing is correct
	assert(index3 == inputArray1_size + inputArray2_size);

	return index3;
}

void writeFile(int outputArray[], int outputArray_size) {
	// Declare output stream
	ofstream outStream;
	char filename[MAX_SIZE]; // Char array to store filename

	// Since no ofstream object is passed in, need to prompt for output filename
	cout << "Enter the output file name: ";
	cin >> filename;

	outStream.open(filename); // Will overwrite any existing file!
	if (outStream.fail()) {
		cout << "Output file opening failed. Terminating.\n";
		exit(1);
	}
	
	for (int i = 0; i < outputArray_size; i++) {
		outStream << outputArray[i] << endl;
	}	
	
	// Close output stream
	outStream.close();
	
	cout << "*** Please check the new file - " << filename << " ***\n";
}

void test_readFile() {
	// Declare test fixtures
	ifstream inStream;
	int inputArray[MAX_SIZE];
	int inputArray_size;

	cout << "Unit Test Case 1: Function - int readFile(int inputArray[], ifstream& inStream)\n";
	
	// Test Case 1.1
	cout << "\tCase 1.1: Open input1.txt and store values from that file.\n";
	inStream.open("input1.txt"); // Create first input stream
	if (inStream.fail()) {
		cout << "\tFailed opening \"input1.txt\"\n\tCase 1.1 failed. Terminating.\n";
		exit(1);
	}
	
	inputArray_size = readFile(inputArray, inStream);
	// Run assertions
	assert(inputArray[0] == 4);
	assert(inputArray[1] == 13);
	assert(inputArray[2] == 14);
	assert(inputArray[3] == 17);
	assert(inputArray[4] == 23);
	assert(inputArray[5] == 89);
	assert(inputArray_size == 6);
	
	// Test has passed if program reaches this point
	cout << "\tCase 1.1 passed.\n";

	// Repeat the above for test case 1.2 and so on
	cout << "\tCase 1.2: Open input2.txt and store values from that file.\n";
	// Clear the input array to be used again
	for (int i = 0; i < inputArray_size; i++) {
		inputArray[i] = 0; 
	}

	inStream.open("input2.txt");
	if (inStream.fail()) {
		cout << "\tFailed opening \"input2.txt\"\n\tCase 1.2 failed. Terminating.\n";
		exit(1);
	}
	
	inputArray_size = readFile(inputArray, inStream);
	// Run assertions
	assert(inputArray[0] == 3);
	assert(inputArray[1] == 7);
	assert(inputArray[2] == 9);
	assert(inputArray[3] == 14);
	assert(inputArray[4] == 15);
	assert(inputArray_size == 5);

	cout << "\tCase 1.2 passed.\n";

	// Test Case 1.3
	cout << "\tCase 1.3: Attempt to open a file that does not exist\n";
	inStream.open("input3.txt");
	if (!inStream.fail()) {
		cout << "\tProgram opened \"input3.txt\", please make sure this file does not exist.\n\tTerminating.\n";
		exit(1);
	}
	inStream.close();
	cout << "\tCase 1.3 passed.\n";

	press_any_key();
}

void test_sort() {
	// Declare test fixtures
	int inputArray1_size;
	int inputArray2_size;
	int inputArray1_empty_size = 0;
	int inputArray2_empty_size = 0;
	int outputArray_size;
	int inputArray1[MAX_SIZE];
	int inputArray2[MAX_SIZE];
	int inputArray1_empty[0];
	int inputArray2_empty[0];
	int outputArray[2 * MAX_SIZE]; // Output should be able to contain both input arrays	

	cout << "Unit Test Case 2: Function - int sort(int inputArray1[], int inputArray1_size,\n"
	     << "\t\tint inputArray2[], int inputArray2_size, int outputArray[])\n";

	// Test Case 2.1
	cout << "\tCase 2.1: Sort two standard arrays into one output array\n";
	
	// Initialize array elements to values
	inputArray1[0] = 4;
	inputArray1[1] = 13;
	inputArray1[2] = 14;
	inputArray1[3] = 17;
	inputArray1[4] = 23;
	inputArray1[5] = 89;
	inputArray1_size = 6;

	inputArray2[0] = 3;
	inputArray2[1] = 7;
	inputArray2[2] = 9;
	inputArray2[3] = 14;
	inputArray2[4] = 15;
	inputArray2_size = 5;

	outputArray_size = sort(inputArray1, inputArray1_size, inputArray2, inputArray2_size, outputArray);

	// Run assertions
	assert(outputArray[0] == 3);
	assert(outputArray[1] == 4);
	assert(outputArray[2] == 7);
	assert(outputArray[3] == 9);
	assert(outputArray[4] == 13);
	assert(outputArray[5] == 14);
	assert(outputArray[6] == 14);
	assert(outputArray[7] == 15);
	assert(outputArray[8] == 17);
	assert(outputArray[9] == 23);
	assert(outputArray[10] == 89);
	assert(outputArray_size == 11);

	// If program reaches this point, the test case passed
	cout << "\tCase 2.1 passed.\n";

	// Test Case 2.2
	cout << "\tCase 2.2: Sort 1 standard array with an empty array\n";

	// Initialize array elements to values
	inputArray1[0] = 5;
	inputArray1[1] = 10;
	inputArray1[2] = 12;
	inputArray1[3] = 14;
	inputArray1_size = 4;

	outputArray_size = sort(inputArray1, inputArray1_size, inputArray2_empty, inputArray2_empty_size, outputArray);

	// Run assertions
	assert(outputArray[0] == 5);
	assert(outputArray[1] == 10);
	assert(outputArray[2] == 12);
	assert(outputArray[3] == 14);
	assert(outputArray_size == 4);

	cout << "\tCase 2.2 passed.\n";

	// Test Case 2.3
	cout << "\tCase 2.3: Sort 2 empty arrays\n";

	outputArray_size = sort(inputArray1_empty, inputArray1_empty_size, inputArray2_empty, inputArray2_empty_size,
				outputArray);

	// Run assertions
	assert(outputArray_size == 0);

	cout << "\tCase 2.3 passed.\n";

	// Test Case 2.4
	cout << "\tCase 2.4: Sort arrays containing \"large\" int values\n";

	// Initialize array elements
	inputArray1[0] = 1024;
	inputArray1[1] = 2048;
	inputArray1[2] = 9001;
	inputArray1[3] = 1000450;
	inputArray1[4] = 50000000;
	inputArray1[5] = 50000001;
	inputArray1_size = 6;

	inputArray2[0] = 5;
	inputArray2[1] = 5000;
	inputArray2[2] = 500000;
	inputArray2[3] = 90000000;
	inputArray2_size = 4;

	outputArray_size = sort(inputArray1, inputArray1_size, inputArray2, inputArray2_size, outputArray);

	// Run Assertions
	assert(outputArray[0] == 5);
	assert(outputArray[1] == 1024);
	assert(outputArray[2] == 2048);
	assert(outputArray[3] == 5000);
	assert(outputArray[4] == 9001);
	assert(outputArray[5] == 500000);
	assert(outputArray[6] == 1000450);
	assert(outputArray[7] == 50000000);
	assert(outputArray[8] == 50000001);
	assert(outputArray[9] == 90000000);
	assert(outputArray_size == 10);	

	cout << "\tCase 2.4 passed.\n";
	
	press_any_key();
}

void test_writeFile() {
	// Declare test fixtures
	int outputArray_size;
	int outputArray_empty_size = 0;
	int outputArray[2 * MAX_SIZE];
	int outputArray_empty[0];	
	int next;
	int i;
	ifstream inStream;

	cout << "Unit Test Case 3: Function - void writeFile(int outputArray[],\n\t\tint outputArray_size)\n*** Please enter "
	     << "out.txt as the filename\n";

	// Test Case 3.1
	cout << "\tCase 3.1: Write normal output array to a file\n";

	// Initialize array elements
	outputArray[0] = 3;
	outputArray[1] = 4;
	outputArray[2] = 7;
	outputArray[3] = 9;
	outputArray[4] = 13;
	outputArray[5] = 14;
	outputArray[6] = 14;
	outputArray[7] = 15;
	outputArray[8] = 17;
	outputArray[9] = 23;
	outputArray[10] = 89;
	outputArray_size = 11;

	writeFile(outputArray, outputArray_size);
	
	inStream.open("out.txt");
	if (inStream.fail()) {
		cout << "Test failed, output file not \"out.txt\". Terminating\n";
		exit(1);
	}

	i = 0;
	// Run Assertions
	while (inStream >> next) {
		assert(outputArray[i] == next);
		i++;
	}	
	
	inStream.close();
	assert(i == outputArray_size);	
	
	// Test case passed once program reaches this line
	cout << "\tCase 3.1 passed.\n";

	// Test Case 3.2
	cout << "\tCase 3.2: Write an empty output array to a file\n";

	writeFile(outputArray_empty, outputArray_empty_size);

	inStream.open("out.txt");
	if (inStream.fail()) {
		cout << "Test failed, output file not \"out.txt\". Termining\n";
		exit(1);
	}

	i = 0;
	// Run Assertions
	while (inStream >> next) {
		assert(outputArray[i] == next);
		i++;
	}
	
	inStream.close();
	assert(i == outputArray_empty_size);

	cout << "\tCase 3.2 passed.\n";

	press_any_key();
}

/*** BEGIN - Source code for press_any_key implementation ***/
void press_any_key(void) {
	char ch;
	cout << "Press any key to continue...";
	ch = mygetch();
	if (ch == 0 || ch == 224) mygetch();
	cout << endl << endl; // Add extra lines between continuous press_any_key
}

int mygetch(void) {
	int ch;
	struct termios oldt, newt;
	
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	return ch;
}
/*** END - press_any_key implementation source ***/
