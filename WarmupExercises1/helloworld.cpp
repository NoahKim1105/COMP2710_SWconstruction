// Login menu for bank program
// Created by: Mark Gallagher Jr
// Test for using Vim and UNIX dev environment
// TechKnow Systems [TKS]

#include <iostream>
using namespace std;

int main()
{
	int userOption;

	cout << "================================================================\n"
	     << "|	Welcome to the Auburn Branch of the Tiger Bank!		|\n"
	     << "================================================================\n";

	cout << "\n1. Login\n2. Quit\n\n";
	cin >> userOption;

	if (userOption == 1) {
		
		cout << "================================================================\n"
	    	     << "|	Teller Terminal System - Choose Login Privleges		|\n"
	    	     << "================================================================\n";
		
		cout << "\n1. System Administration\n2. Branch Staff\n3. Quit\n\n";

		cin >> userOption;

		if (userOption == 1) {

			cout << "================================================================\n"
		    	     << "|	Teller Terminal System - System Administration		|\n"
	    		     << "================================================================\n";
		
			cout << "\n1. Client and Account Management\n"
			     << "2. Add a branch staff\n3. Delete a branch staff\n"
			     << "4. Display branch staffs\n5. Change password\n6. Exit\n\n";

			cin >> userOption;
			
			cout << "You entered: " << userOption << endl;
			cout << "Software incomplete, terminating...\n";
			return 0;
		}
		else if (userOption == 2) {
			
			cout << "================================================================\n"
		    	     << "|	Teller Terminal System - Branch Staff   		|\n"
	    		     << "================================================================\n";
		
			cout << "\n1. Client and Account Management\n"
			     << "2. Change password\n3. Exit\n\n";

			cin >> userOption;

			cout << "You entered: " << userOption << endl;
			cout << "Software incomplete, terminating...\n";
			return 0;
		}
		else {
			
			cout << "You entered: " << userOption << endl;
			cout << "Software incomplete, terminating...\n";
			return 0;
		}

		
	}
	else {
		return 0;
	}

	return 0;
}	
