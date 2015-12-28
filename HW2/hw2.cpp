// Program to calculate how long to pay off a loan and how much it'll cost
// COMP2710 Homework 2
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: hw2.cpp
// Written in Vi text editor, compiled with g++ -o hw2 hw2.cpp
// Version: 2/6/2015, v1
// Sources used: N/A

#include <iostream>
using namespace std;

int main() {

	// Declare variables
	double balance, monthlyInterestRate, monthlyPayment, loanAmount,
		monthlyInterest, principal, totalInterest = 0.0;
	int monthsToPayOff = 0;
	char userContinue;
	
	do {
		cout << "Loan Amount: ";
		cin >> loanAmount;
		balance = loanAmount / 1.0; // Initialize balance to the loan amount
		cout << "Interest Rate (% per year): ";
		cin >> monthlyInterestRate;
		monthlyInterestRate /= 100.0;
		monthlyInterestRate /= 12.0;
		cout << "Monthly Payments: ";
		cin >> monthlyPayment;
		
		// Check to see if debt is payable with monthly payment entered
		if (loanAmount * monthlyInterestRate > monthlyPayment) {
			cout << "\nYour debt will never be paid with the numbers entered.\n"
				<< "Please enter a higher monthly payment or a lower"
				<< " interest rate next time.\n";
			cout << "Would you like to try again? (y/n) ";
			cin >> userContinue;
			cout << endl;
			if (userContinue == 'n' || userContinue == 'N') {
				cout << "Very well, terminating program...\n";
				return 0;
			}
		}
		else {
			userContinue = 'n';
		}
	
	} while (userContinue == 'y' || userContinue == 'Y');

	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	// Draw table and print first line of data	
	cout << "**************************************************************************\n"
	     << "*			Amortization Table				 *\n"
	     << "**************************************************************************\n";
	cout << "Month\tBalance \t\tPayment\tRate\tInterest\tPrincipal\n"
	     << "0\t$" << balance << "\t\tN/A\tN/A\tN/A       \tN/A\n";
		
	// Start iteration loop to run calculations
	while (balance > 0) {
		monthlyInterest = balance * monthlyInterestRate;
		totalInterest += monthlyInterest;
		if (monthlyInterest + balance > monthlyPayment) {
			principal = monthlyPayment - monthlyInterest;
			balance -= principal;
		}
		else {
			principal = balance;
			monthlyPayment = principal + monthlyInterest;
			balance = 0.0;
		}	

		cout << ++monthsToPayOff << "\t$" << balance << "   \t\t$"
		     << monthlyPayment << "\t" << monthlyInterestRate * 100  << "\t$"
		     << monthlyInterest << "    \t$" << principal << endl;
	}

	// Print final results
	cout << "**************************************************************************\n\n";
	cout << "It takes " << monthsToPayOff << " months to pay off the loan.\n"
	     << "Total interest paid is: $" << totalInterest << endl; 
	
	return 0;	
}
