// Dragons - A simple text based game
// File contains function implementations for the system as a whole 
// COMP2710 Project 1
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: project1_system.cpp
// Written in Vi text editor
// Version: 4/13/2015, v1
// Sources used: Dr. Qin's PowerPoint on using cin to get string and int values, also 
// 			helpful for error-checking the input 

#include "project1_system.h" 
#include "project1_scoreboard.h"

// Logs in the user, repeats until they enter a non-empty string
void login_process(string& userName)
{
	do
	{
		cout << "Please enter your name: ";
		getline(cin, userName);
	} while (userName.empty());
}

// Initializes character attributes to appropiate values
// Assumes that userName is not empty (since entered from login_process)
void init_character(string userName, player& userPlayer)
{
	userPlayer.name = userName;

	// Generates a random number within the bounds set by gamemaker
	userPlayer.money = rand() % (ATTRIBUTE_UPPER_BOUND - ATTRIBUTE_LOWER_BOUND) + ATTRIBUTE_LOWER_BOUND;
	userPlayer.intel = rand() % (ATTRIBUTE_UPPER_BOUND - ATTRIBUTE_LOWER_BOUND) + ATTRIBUTE_LOWER_BOUND;
	userPlayer.time = rand() % (TIME_UPPER_BOUND - TIME_LOWER_BOUND) + TIME_LOWER_BOUND;

	// Sets initial steps away from the goal to a constant value
	userPlayer.steps = INITIAL_STEPS_FROM_GOAL;

	// Score is calculated FIRST since this attribute will determine the GAME_OVER condition
	calculate_score(userPlayer);
}

// Ensures a nonnegative integer is entered
// @return	nonnegative integer
u_short valid_int_input()
{
	int result = -1;
	
	do
	{
		// in cases where cin fails, notify user and clear buffer
		if (!(cin >> result))
		{
			cout << "\tPlease enter numbers only: ";
			cin.clear();
			cin.ignore(10000,'\n');
			result = -1;
		}
		else if (result < 0)
		{
			cout << "\tPlease enter 0 or positive numbers only: ";
		}
	
	} while (result < 0);

	return result;
}

// Given an action, this function modifies the player accordingly.
// actionType is NOT used, only need attrType and points!
void point_handler(player& userPlayer, action actionToTake)
{
	// Print if user gains or loses something
	if (actionToTake.points >= 0)
	{
		cout << "You GAIN " << actionToTake.points;
	}
	else if (actionToTake.points < 0)
	{
		cout << "You LOSE " << (actionToTake.points * -1);
	}

	// Take action depending on attribute to be modded
	switch (actionToTake.attrType)
	{
		case MONEY:
			cout << " dollars\n";
			
			// Modify player
			userPlayer.money += actionToTake.points;
			break;
		case TIME:
			cout << " units of time\n";

			userPlayer.time += actionToTake.points;
			break;
		case INTEL:
			cout << " IQ points\n";

			userPlayer.intel += actionToTake.points;
			break;
		case STEPS:
			cout << " steps left from the goal\n";

			userPlayer.steps += actionToTake.points;
			break;
	}
}

// Displays the system menu option and asks the user to enter a selection.
// @return user selection (validated first)
u_short display_sys_menu()
{
	u_short userChoice = 0;

	// Repeatedly ask for selection until it is valid
	do
	{
		// Display system menu
		cout << "\n1) Start a New Game of Shelby and Dragons!\n";
		cout << "2) View Top " << MAX_NUM_OF_HIGH_SCORES << " High Scores\n";
		cout << "3) Quit\n\n";
	
		// Obtain user's selection
		cout << "\tPlease choose an option: ";
		userChoice = valid_int_input();

		// Get the zero-index version of the selection
		userChoice--;

		if (userChoice < 0 || userChoice > SYS_MENU_UPPER_CHOICE) 
		{
			cout << "\tThat option does not exist, please try again\n";
		}

		cout << endl;

	} while (userChoice < 0 || userChoice > SYS_MENU_UPPER_CHOICE);
	
	return userChoice;
}
