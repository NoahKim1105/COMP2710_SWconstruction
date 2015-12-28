// Dragons - A simple text based game
// File contains function implementations used for game menu choices
// COMP2710 Project 1
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: project1_menu.cpp
// Written in Vi text editor
// Version: 4/13/2015, v1

#include "project1_menu.h"

// Given an encounter ID, move forward will execute the proper encounter
void move_forward(player& userPlayer, encounter encSelected)
{
	cout << "You move forward and...\n";

	// Print message
	cout << encSelected.message << endl;

	// Switch statement to select the correcet encounter
	switch(encSelected.enctType)
	{
		case NOTHING:
			// Modify player
			point_handler(userPlayer, encSelected.actionArray[0]);
			point_handler(userPlayer, encSelected.actionArray[1]);

			break;
		// Puzzles handled elsewhere (use overloaded function!)
		case PROFESSOR:
			// Call function for professor
			professor_enc(userPlayer, encSelected);

			break;
		case STUDENT:
			// Call function for student
			student_enc(userPlayer, encSelected);

			break;			
		case GRUNT:
			// Call function for grunt work
			grunt_enc(userPlayer, encSelected);

			break;			
		case PAPER:
			// Call function for grade papers
			paper_enc(userPlayer, encSelected);

			break;		
	}	

	cout << endl;
}

// To be executed ONLY if puzzle encounter is expected
void move_forward(player& userPlayer, encounter encSelected, puzzleHead p_head)
{
	cout << "You move forward and...\n";

	// Print message
	cout << encSelected.message << endl;

	// This function only used on PUZZLE encounters
	ask_puzzle(userPlayer, p_head);

	cout << endl;
}

// Displays character information
void view_character(player userPlayer)
{
	cout << "You have:\n" << endl;
	cout << "Money: $" << userPlayer.money << endl;
	cout << "Intelligence: " << userPlayer.intel << endl;
	cout << "Time left: " << userPlayer.time << " turns\n\n";
	cout << "You are " << userPlayer.steps << " steps from the goal.\n";
}

// Reads a paper. Also handles displaying to user what attributes it changed
void read_paper(player& userPlayer)
{
	// Randomly select a paper to read
	u_short paperSelect = rand() % 5;
	
	// Set how much to modify attributes
	u_short modIntelBy = rand() % 5 + 2;
	u_short modTimeBy = 1;
	
	// Modify appropiate attributes
	userPlayer.intel += modIntelBy;
	userPlayer.time -= modTimeBy;

	// Display what happened to the user
	switch (paperSelect)
	{	
		case 0:
			cout << "You read through some technical papers detailing specs for a low orbital ion cannon. ";
			break;
		case 1: 
			cout << "You read through some papers about wormholes, black holes, and a thing called a Stargate. ";
			break;
		case 2: 
			cout << "You read through some papers detailing an alternate world rules by a magical pony (tyrant) princess. Interesting choice there... ";
			break;
		case 3:
		case 4:
			cout << "You read some nonsense claiming that you are being forced to play this game by an AI overlord bent on testing humans forever, that she's codenamed GLaDOS, she says 2 + 2 = 10 (in BASE 4!), and that the cake is a lie. ";
			break;
	}

	cout << "\nYou gain " << modIntelBy << " intelligence, but lose a unit of time.\n";
}

// Searches for change. Also handles displaying to user what attributes it changed
void search_change(player& userPlayer)
{
	// Select what happens to the user randomly
	u_short changeSelect = rand() % 5;

	// Set how much to modify attributes
	u_short modMoneyBy = rand() % 5 + 2;
	u_short modTimeBy = 1;

	// Modify appropiate attributes
	userPlayer.money += modMoneyBy;
	userPlayer.time -= modTimeBy;

	// Display what happened to the user
	switch (changeSelect)
	{
		case 0:
		case 1:
			cout << "You search through the couches of Shelby desperatly for loose change. ";
			break;
		case 2:
		case 3:
			cout << "You resort to begging to use an on-campus resident's TigerCard. It works...at the cost of helping them with their homework after you save the Princess of Engineering. ";
			break; 
		case 4:
			cout << "You open your computer and start mining for BitCoins. However, this is futile as you lack the GPU power neccessary for this and instead receive a kind donation by some ponies. ";
			break;
	}	

	cout << "\nYou gain $" << modMoneyBy << "! But you lose a unit of time.\n";
}

// Performs the EASTER EGG EVENT!!! WARNING: will terminate program if executed!!!
void easter_egg_event(player& userPlayer)
{
	// HUGE RAISE! :D
	u_int modMoneyBy = 999999999;
	int dummyVar; // not even used 
	
	cout << "You key in the secret number into a keypad on the wall. It opens a hidden door, revealing a shiny object\n"; 
	cout << "You pick up the shiny object (cause why not? It's shiny) and as soon as you do so, you hear a high-pitched voice say in awe";
	cout << " \"Ooooooooo SHIIINYYYY!\". You're concerned because the little trinket begins to glow brightly. It says you get a TON OF MONEY!\n";
	cout << "\"How much money do you want?\" the object asks: ";
	
	// "read" in what the user enters....
	cin >> dummyVar;

	cout << "\nVery well, you get, a TON OF MONEY!\n";
	cout << "And then...the object shakes violently. You don't know what happening and drop the object out of your panic. The object shatters and lets out a magical smoke.";
	cout << " The smoke rises and forms a portal! Before you even have time to realize this, you're grabbed by magical ponies emerging from the portal!!";
	cout << " You try to get away but you can't seem to break free! Their combined strength and magical powers are too strong!!! They drag you through the portal!";

	cout << "\nYou are now forced to live the rest of your new-pony life in this odd magical fairy-tale land of ponies, pegasi, and unicorns under the rule of a ";
	cout << "tyrant princess named, Celestia. It's sad, but hey, you got tons of money right? Money you can't even use in this world that uses a currency called ";
	cout << "\'bits\'.\n";
	
	cout << "Meanwhile, the Princess of Engineering, Princess Shelby, grew tired of waiting for her hero and uses her epic engineering skills to break free herself";
	cout << " and seek her true love from another college.....oh the horror when you find out (through a form of torture given to you by Celestia) that your love,";
	cout << " Princess Shelby, has decided to seek her mate in.....COSAM\n";

	cout << endl;

	userPlayer.time = 0;
	userPlayer.money += modMoneyBy;
	userPlayer.intel = 0;
	userPlayer.steps = 0;

	view_character(userPlayer);

	cout << "Why is steps from goal 0? Isn't it obvious, you've reached your goal of becoming a magical pony!...\n";
	cout << "GAME_OVER\n";

	exit(0);
}

// Displays the game menu and asks the user to enter a selection.
// @return user selection (validated first)
u_short display_game_menu()
{
	u_short userChoice = 0;

	// Repeatedly ask for selection until it is valid
	do
	{
		// Display game menu
		cout << "\n1) Move forward (could be risky...)\n";
		cout << "2) Read technical papers (boost intelligence, takes time, could be fun)\n";
		cout << "3) Search for loose change (boost money, takes time, maybe find a sword in a chest...)\n";
		cout << "4) View character stats\n";
		cout << "5) Quit this game and return to Main Menu (why would you ever do that?)\n\n";

		// Obtain user's selection
		cout << "\tPlease choose an action: ";
		userChoice = valid_int_input();

		// Get the zero-index version of the action
		userChoice--;

		// Use XOR to determine if easter egg trigger entered
		if (userChoice < 0 || ((userChoice > GME_MENU_UPPER_CHOICE) != (userChoice + 1 == EASTER_EGG_TRIGGER)))
		{
			cout << "\tThat option does not exist, please try again\n";
		}

		cout << endl;

	} while (userChoice < 0 || ((userChoice > GME_MENU_UPPER_CHOICE) != (userChoice + 1 == EASTER_EGG_TRIGGER)));

	return userChoice;
}
