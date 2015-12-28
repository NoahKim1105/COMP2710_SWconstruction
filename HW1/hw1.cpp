// Program to help a desperate friend lose weight.
// COMP2710 Homework 1
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: hw1.cpp
// Written in Vi text editor, compiled with g++ -o hw1 hw1.cpp
// Version: 1/27/2015, v1
// Sources used: N/A

#include<iostream>
using namespace std;

int main() {

	// Create constant to store fraction of sweetener in soda
	const double PERCENT_SWEET_SODA = 0.001;
	
	// Variables to store user input
	double amntKillMouse;
	int mouseWeight, dieterWeight;
	
	// Variables for calculations
	int numSodasSafeToDrink;
	double sodasKillPerPound;

	// Receive user input
	cout << "What is the amount of artificial sweetener needed to "
	     << "kill a mouse: ";
	cin >> amntKillMouse;
	cout << "What is the weight of the mouse: ";
	cin >> mouseWeight;
	cout << "What is the weight that the dieter wishes to stop at: ";
	cin >> dieterWeight;

	// Calculate how much diet sodas to kill mouse per pound first
	sodasKillPerPound = (amntKillMouse / PERCENT_SWEET_SODA) / mouseWeight;
	numSodasSafeToDrink = sodasKillPerPound * dieterWeight;

	cout << "You can drink " << numSodasSafeToDrink
	     << " diet sodas without dying as a result.\n";

	return 0;	
	
} 
