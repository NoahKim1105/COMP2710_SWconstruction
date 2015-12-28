// Program to determine statistical probability of duelist living
// And which strategy is the most beneficial for worst duelist
// COMP2710 Homework 3
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: hw3.cpp
// Written in Vi text editor, compiled with g++ -o hw3 hw3.cpp
// Version: 2/13/2015, v1
// Sources used: Dr. Qin's source for rand.cpp and pressanykey.cpp

#include<stdio.h>
#include<termios.h>
#include<unistd.h>
#include<ctype.h>
#include<assert.h>
#include<cstdlib>
#include<iostream>
using namespace std;

// Declare functions
bool at_least_two_alive(bool Aaron_alive, bool Bob_alive, bool Charlie_alive);
/* Input: Aaron_alive indicates whether Aaron is alive
 *	  Bob_ alive indicates whether Bob is alive
 *	  Charlie_alive indicates wheter Charlie is alive
 * Return: true if at least two are alive
 * 	   otherwise return false
 */

void Aaron_shoots1(bool& Bob_alive, bool& Charlie_alive);
/* Strategy 1: Use call by reference
 * Input: Bob_alive indicates whether Bob is alive
 * 	  Charlie_alive indicates whether Charlie is alive
 * Return: Change Bob_alive to false is Bob is killed
 * 	   Change Charlie_alive to false is Charlie is killed
 */

void Bob_shoots(bool& Aaron_alive, bool& Charlie_alive);
/* Call by reference
 * Input: Aaron_alive indicates whether Aaron is alive
 * 	  Charlie_alive indicates whether Charlie is alive
 * Return: Change Aaron_alive to false is Aaron is killed
 * 	   Change Charlie_alive to false is Charlie is killed
 */

void Charlie_shoots(bool& Aaron_alive, bool& Bob_alive);
/* Call by reference
 * Input: Aaron_alive indicates whether Aaron is alive
 * 	  Bob_alive indicates whether Bob is alive
 * Return: Change Aaron_alive to false is Aaron is killed
 * 	   Change Bob_alive to false is Bob is killed
 */

void Aaron_shoots2(bool& Bob_alive, bool& Charlie_alive);
/* Strategy 2: Use call by reference
 * Input: Bob_alive indicates whether Bob is alive
 * 	  Charlie_alive indicates whether Charlie is alive
 * Return: Change Bob_alive to false is Bob is killed
 * 	   Change Charlie_alive to false is Charlie is killed
 */

// Declare unit tests for the 5 functions above
void test_at_least_two_alive(void);
void test_Aaron_shoots1(void);
void test_Bob_shoots(void);
void test_Charlie_shoots(void);
void test_Aaron_shoots2(void);

// Functions needed for press_any_key implementation
int mygetch(void);
void press_any_key(void);

// Constants to define shootrates
const int AARON_SHOOTRATE = 33;
const int BOB_SHOOTRATE = 50;
const int CHARLIE_SHOOTRATE = 100;

int main() {
	// Declare maximum amount of simulations to run
	const int MAX_SIMULATION_NUM = 10000;

	// Declare variables
	bool Aaron_alive, Bob_alive, Charlie_alive;
	int Aaron_wins = 0, Bob_wins = 0, Charlie_wins = 0; // Statistics tracking	
	double Aaron_prob1, Bob_prob, Charlie_prob, Aaron_prob2;

	// Initialize random number generator with seed
	srand(time(NULL));

	cout << "*** Welcome to Mark Gallagher's Duel Simulator ***\n";

	/** Begin unit testing on essential functions **/
	test_at_least_two_alive();
	test_Aaron_shoots1();	
	test_Bob_shoots();	
	test_Charlie_shoots();
	test_Aaron_shoots2();

	/** Begin simulations **/
	// Simulation for strategy 1:
	cout << "Ready to test strategy 1 (run " << MAX_SIMULATION_NUM << " times):\n";
	press_any_key();
	
	for (int i = 0; i < MAX_SIMULATION_NUM; i++) {
		Aaron_alive = Bob_alive = Charlie_alive = true; // Initialize a game
		while (at_least_two_alive(Aaron_alive, Bob_alive, Charlie_alive)) {
			if (Aaron_alive) {
				Aaron_shoots1(Bob_alive, Charlie_alive);
				cout << endl;
			}
			if (Bob_alive) {
				Bob_shoots(Aaron_alive, Charlie_alive); 
				cout << endl;
			}
			if (Charlie_alive) {
				Charlie_shoots(Aaron_alive, Bob_alive);
				cout << endl;
			}
		}	
		// Game ends once while-loop ends
		// Use assert macro to ensure winner properly chosen
		if (Aaron_alive) {
			assert(!Bob_alive && !Charlie_alive);
			Aaron_wins++;
		}
		if (Bob_alive) {
			assert(!Aaron_alive && !Charlie_alive);
			Bob_wins++;
		}
		if (Charlie_alive) {
			assert(!Aaron_alive && !Bob_alive);
			Charlie_wins++;
		}
	}

	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	Aaron_prob1 = (static_cast<double>(Aaron_wins)/MAX_SIMULATION_NUM) * 100.0;
	Bob_prob = (static_cast<double>(Bob_wins)/MAX_SIMULATION_NUM) * 100.0;
	Charlie_prob = (static_cast<double>(Charlie_wins)/MAX_SIMULATION_NUM) * 100.0;

	cout << "Aaron won " << Aaron_wins << "/" << MAX_SIMULATION_NUM << " duels or "
		<< Aaron_prob1 << "%\n";
	cout << "Bob won " << Bob_wins << "/" << MAX_SIMULATION_NUM << " duels or "
		<< Bob_prob << "%\n";
	cout << "Charlie won " << Charlie_wins << "/" << MAX_SIMULATION_NUM << " duels or "
		<< Charlie_prob << "%\n";

	// Simulations for strategy 2:
	cout << "\nReady to test strategy 2 (run " << MAX_SIMULATION_NUM << " times):\n";
	press_any_key();

	// Reset statistic variables
	Aaron_wins = Bob_wins = Charlie_wins = 0;

	for (int i = 0; i < MAX_SIMULATION_NUM; i++) {
		Aaron_alive = Bob_alive = Charlie_alive = true; // Initialize a game
		while (at_least_two_alive(Aaron_alive, Bob_alive, Charlie_alive)) {
			if (Aaron_alive) {
				Aaron_shoots2(Bob_alive, Charlie_alive);
				cout << endl;
			}
			if (Bob_alive) {
				Bob_shoots(Aaron_alive, Charlie_alive); 
				cout << endl;
			}
			if (Charlie_alive) {
				Charlie_shoots(Aaron_alive, Bob_alive);
				cout << endl;
			}
		}	
		// Game ends once while-loop ends
		// Use assert macro to ensure winner properly chosen
		if (Aaron_alive) {
			assert(!Bob_alive && !Charlie_alive);
			Aaron_wins++;
		}
		if (Bob_alive) {
			assert(!Aaron_alive && !Charlie_alive);
			Bob_wins++;
		}
		if (Charlie_alive) {
			assert(!Aaron_alive && !Bob_alive);
			Charlie_wins++;
		}
	}

	Aaron_prob2 = (static_cast<double>(Aaron_wins)/MAX_SIMULATION_NUM) * 100.0;
	Bob_prob = (static_cast<double>(Bob_wins)/MAX_SIMULATION_NUM) * 100.0;
	Charlie_prob = (static_cast<double>(Charlie_wins)/MAX_SIMULATION_NUM) * 100.0;

	cout << "Aaron won " << Aaron_wins << "/" << MAX_SIMULATION_NUM << " duels or "
		<< Aaron_prob2 << "%\n";
	cout << "Bob won " << Bob_wins << "/" << MAX_SIMULATION_NUM << " duels or "
		<< Bob_prob << "%\n";
	cout << "Charlie won " << Charlie_wins << "/" << MAX_SIMULATION_NUM << " duels or "
		<< Charlie_prob << "%\n";
	
	cout << "\nStrategy " << (Aaron_prob1 < Aaron_prob2 ? "2" : "1") << " is better than "
	     << "strategy " << (Aaron_prob1 < Aaron_prob2? "1" : "2") << ".\n";
	
	return 0;
}

// Tests if at least two people are still alive. If not, returns false
bool at_least_two_alive(bool Aaron_alive, bool Bob_alive, bool Charlie_alive) {
	return (Aaron_alive && Bob_alive) || (Bob_alive && Charlie_alive) || 
	       (Aaron_alive && Charlie_alive);
}

// Run procedure for Aaron shooting using strategy 1
void Aaron_shoots1(bool& Bob_alive, bool& Charlie_alive) {
	int shootPoint = rand() % 100;
	// If Charlie is alive, take a shot at him
	if (Charlie_alive) {
		if (shootPoint < AARON_SHOOTRATE) {
			cout << "Charlie is dead.";
			Charlie_alive = false;
		}
		else {
			cout << "Aaron misses.";
		}
	}
	// Bob is alive
	else {
		if (Bob_alive) {
			if (shootPoint < AARON_SHOOTRATE) {
				cout << "Bob is dead.";
				Bob_alive = false;
			}
			else {
				cout << "Aaron misses.";
			}
		}
		else { //If no other branch executes, then two false values were passed in - INVALID ARGS
			cout << "Error Message: Aaron shoots nobody.";
		}
	}
} 

// Run procedure for Bob shooting
void Bob_shoots(bool& Aaron_alive, bool& Charlie_alive) {
	int shootPoint = rand() % 100;
	// If Charlie is alive, take a shot at him
	if (Charlie_alive) {
		if (shootPoint < BOB_SHOOTRATE) {
			cout << "Charlie is dead.";
			Charlie_alive = false;
		}
		else {
			cout << "Bob misses.";
		}
	}
	// Aaron is alive
	else {
		if (Aaron_alive) {
			if (shootPoint < BOB_SHOOTRATE) {
				cout << "Aaron is dead.";
				Aaron_alive = false;
			}
			else {
				cout << "Bob misses.";
			}
		}
		else { //If no other branch executes, then two false values were passed in - INVALID ARGS
			cout << "Error Message: Bob shoots nobody.";
		}
	}
}

// Run procedure for Charlie shooting
void Charlie_shoots(bool& Aaron_alive, bool& Bob_alive) {
	// Whoever Charlie shoots at will die (100% kill rate)
	// Note: branch implemented to utilize the constants for Charlie's shootrate
	// since his shootrate may be changed to not be 100%
	
	int shootPoint = rand() % 100;
	// If Bob is alive, take a shot at him
	if (Bob_alive) {
		if (shootPoint < CHARLIE_SHOOTRATE) {
			cout << "Bob is dead.";
			Bob_alive = false;
		}
		else {
			cout << "Charlie misses.";
		}
	}
	// Aaron is alive
	else {
		if (Aaron_alive) {
			if (shootPoint < CHARLIE_SHOOTRATE) {
				cout << "Aaron is dead.";
				Aaron_alive = false;
			}
			else {
				cout << "Charlie misses.";
			}
		}
		else { //If no other branch executes, then two false values were passed in - INVALID ARGS
			cout << "Error Message: Charlie shoots nobody.";
		}
	}
}

// Run procedure for Aaron shooting using strategy 2 
void Aaron_shoots2(bool& Bob_alive, bool& Charlie_alive) {
	// If both Bob and Charlie are still alive, this is Aaron's first shot
	// Therefore, in strategy 2, he should not shoot at anyone
	if (Bob_alive && Charlie_alive) {
		cout << "Both Bob and Charlie are alive.";
		return;
	}

	// Since everything else is same as in strat 1, call that function
	Aaron_shoots1(Bob_alive, Charlie_alive);
} 

// Unit Test for at_least_two_alive function
// Uses assert macro
void test_at_least_two_alive(void) {
	cout << "Unit Testing 1: Function - at_least_two_alive()\n";
	
	cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
	assert(true == at_least_two_alive(true, true, true));
	cout << "\tCase passed...\n";

	cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
	assert(true == at_least_two_alive(false, true, true));
	cout << "\tCase passed...\n"; 

	cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
	assert(true == at_least_two_alive(true, false, true));
	cout << "\tCase passed...\n";
	
	cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
	assert(true == at_least_two_alive(true, true, false));
	cout << "\tCase passed...\n";

	cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
	assert(false == at_least_two_alive(false, false, true));
	cout << "\tCase passed...\n";

	cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
	assert(false == at_least_two_alive(false, true, false));
	cout << "\tCase passed...\n";

	cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
	assert(false == at_least_two_alive(true, false, false));
	cout << "\tCase passed...\n";

	cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
	assert(false == at_least_two_alive(false, false, false));
	cout << "\tCase passed...\n";
	
	press_any_key();
}

// Unit Test for Aaron_shoots1 function
void test_Aaron_shoots1(void) {
	// Initialize test fixtures
	bool Bob_alive = true, Charlie_alive = true;

	// Begin testing on 4 cases
	cout << "Unit Testing 2: Function - Aaron_shoots1(Bob_alive, Charlie_alive)\n";

	// Case 1
	cout << "\tCase 1: Bob alive, Charlie alive\n\t\tAaron is shooting at Charlie\n\t\t";
	Aaron_shoots1(Bob_alive, Charlie_alive);

	// Case 2
	Bob_alive = false;
	Charlie_alive = true;
	cout << "\n\tCase 2: Bob dead, Charlie alive\n\t\tAaron is shooting at Charlie\n\t\t";
	Aaron_shoots1(Bob_alive, Charlie_alive);

	// Case 3
	Bob_alive = true;
	Charlie_alive = false;
	cout << "\n\tCase 3: Bob alive, Charlie dead\n\t\tAaron is shooting at Bob\n\t\t";
	Aaron_shoots1(Bob_alive, Charlie_alive);

	// Case 4
	Bob_alive = false;
	Charlie_alive = false;
	cout << "\n\tCase 4: Bob dead, Charlie dead\n\t\tAaron shouldn't shoot at anyone\n\t\t";
	Aaron_shoots1(Bob_alive, Charlie_alive);
	
	cout << endl;
	press_any_key();
}

// Unit Test for Bob_shoots function
void test_Bob_shoots(void) {
	// Initialize test fixtures
	bool Aaron_alive = true, Charlie_alive = true;

	// Begin testing on 4 cases
	cout << "Unit Testing 3: Function - Bob_shoots(Aaron_alive, Charlie_alive)\n";

	// Case 1
	cout << "\tCase 1: Aaron alive, Charlie alive\n\t\tBob is shooting at Charlie\n\t\t";
	Bob_shoots(Aaron_alive, Charlie_alive);

	// Case 2
	Aaron_alive = false;
	Charlie_alive = true;
	cout << "\n\tCase 2: Aaron dead, Charlie alive\n\t\tBob is shooting at Charlie\n\t\t";
	Bob_shoots(Aaron_alive, Charlie_alive);

	// Case 3
	Aaron_alive = true;
	Charlie_alive = false;
	cout << "\n\tCase 3: Aaron alive, Charlie dead\n\t\tBob is shooting at Aaron\n\t\t";
	Bob_shoots(Aaron_alive, Charlie_alive);

	// Case 4
	Aaron_alive = false;
	Charlie_alive = false;
	cout << "\n\tCase 4: Aaron dead, Charlie dead\n\t\tBob shouldn't shoot at anyone\n\t\t";
	Bob_shoots(Aaron_alive, Charlie_alive);
	
	cout << endl;
	press_any_key();
}

// Unit Test for Charlie_shoots function
void test_Charlie_shoots(void) {
	// Initialize test fixtures
	bool Aaron_alive = true, Bob_alive = true;

	// Begin testing on 4 cases
	cout << "Unit Testing 4: Function - Charlie_shoots(Aaron_alive, Bob_alive)\n";

	// Case 1
	cout << "\tCase 1: Aaron alive, Bob alive\n\t\tCharlie is shooting at Bob\n\t\t";
	Charlie_shoots(Aaron_alive, Bob_alive);

	// Case 2
	Aaron_alive = false;
	Bob_alive = true;
	cout << "\n\tCase 2: Aaron dead, Bob alive\n\t\tCharlie is shooting at Bob\n\t\t";
	Charlie_shoots(Aaron_alive, Bob_alive);

	// Case 3
	Aaron_alive = true;
	Bob_alive = false;
	cout << "\n\tCase 3: Aaron alive, Bob dead\n\t\tCharlie is shooting at Aaron\n\t\t";
	Charlie_shoots(Aaron_alive, Bob_alive);

	// Case 4
	Aaron_alive = false;
	Bob_alive = false;
	cout << "\n\tCase 4: Aaron dead, Bob dead\n\t\tCharlie shouldn't shoot at anyone\n\t\t";
	Charlie_shoots(Aaron_alive, Bob_alive);
	
	cout << endl;
	press_any_key();
}

// Unit Test for Aaron_shoots2 function
void test_Aaron_shoots2(void) {
	// Initialize test fixtures
	bool Bob_alive = true, Charlie_alive = true;

	// Begin testing on 4 cases
	cout << "Unit Testing 5: Function - Aaron_shoots2(Bob_alive, Charlie_alive)\n";

	// Case 1
	cout << "\tCase 1: Bob alive, Charlie alive\n\t\tAaron intentionally misses his first shot\n\t\t";
	Aaron_shoots2(Bob_alive, Charlie_alive);

	// Case 2
	Bob_alive = false;
	Charlie_alive = true;
	cout << "\n\tCase 2: Bob dead, Charlie alive\n\t\tAaron is shooting at Charlie\n\t\t";
	Aaron_shoots2(Bob_alive, Charlie_alive);

	// Case 3
	Bob_alive = true;
	Charlie_alive = false;
	cout << "\n\tCase 3: Bob alive, Charlie dead\n\t\tAaron is shooting at Bob\n\t\t";
	Aaron_shoots2(Bob_alive, Charlie_alive);

	// Case 4
	Bob_alive = false;
	Charlie_alive = false;
	cout << "\n\tCase 4: Bob dead, Charlie dead\n\t\tAaron shouldn't shoot at anyone\n\t\t";
	Aaron_shoots2(Bob_alive, Charlie_alive);
	
	cout << endl;
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
