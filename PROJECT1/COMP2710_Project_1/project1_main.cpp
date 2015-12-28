// Dragons - A simple text based game 
// This file contains the MAIN applicaion
// COMP2710 Project 1
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: project1_main.cpp
// Written in Vi text editor
// Version: 4/13/2015, v1

#include "project1_main.h"

int main() {

	// Initialize random number generator
	srand(time(NULL));

	// Variables
	string userName, userFileChoice, filename;
	player player1;		// holds the player attributes for user
	scoreHead sBoard; 	// holds scoreboard for game
	puzzleHead puzzleList;	// holds the puzzle list
	encounterPtr encArray;	// holds the encounters list
	u_short userChoice_sysmenu = 0;	// determines user choice in the system menu
	u_short userChoice_gmemenu = 0;	// determines user choice in the game menu

	// Log in the gamer
	login_process(userName);

	// Initialize puzzles and encounters from presets
	create_puzzle_list(puzzleList);
	init_encounters(encArray);
	
	// Ask if user would like to use a different file for the scoreboard
	cout << "\nThe current file to load the scoreboard from is \"" << DEFAULT_SCOREBOARD_FILE << "\". Would you like to use a different file? (y/n): ";
	getline(cin, userFileChoice);
	
	// Load scores in
	if (userFileChoice == "Y" || userFileChoice == "y" || userFileChoice == "Yes" || userFileChoice == "yes")
	{
		cout << "\nPlease enter desired filename: ";
		getline(cin, filename);
		
		// Attempt to load scores from this file
		if (load_scores(sBoard, filename.c_str()) == 1)
		{
			cout << "ERROR: Could not load file... using default scoreboard file\n";
			if (load_scores(sBoard) == 1)
			{
				cout << "ERROR: Default file cannot be loaded, using an empty scoreboard\n";
				sBoard.numScores = 0;
				sBoard.first = NULL;
			}
		}
		else
		{
			cout << "File loaded successfully, proceeding with main program...\n\n";
		}
	}
	else
	{
		if (load_scores(sBoard) == 1)
		{
			cout << "ERROR: Default file cannot be loaded, using an empty scoreboard\n";
			sBoard.numScores = 0;
			sBoard.first = NULL;
		}
		else
		{
			cout << "File loaded successfully, proceeding with main program...\n\n";
		}
	}

	// Welcome the user
	cout << "\n================================================================================\n";
	cout << "|\t\t\t\tWelcome, " << userName << "!\t\t\t\t|\n";
	cout << "================================================================================\n";

	// Begin main program loop
	// Termination condition: User chooses to quit the program entirely (option 3)
	while (userChoice_sysmenu != 2)
	{
		// Get the user's next option
		userChoice_sysmenu = display_sys_menu();

		// Execute the user's choice
		switch (userChoice_sysmenu)
		{
			// Start a new game
			case START_GAME:
				cout << "Now entering Shelby Center, where you, " << userName << ", is on a quest to save the Princess of Engineering, Princess Shelby! Good luck on your quest, young programmer\n";
				
				// Initialize character to initial values
				init_character(userName, player1);
				view_character(player1);
				userChoice_gmemenu = 0;

				// Begin game program loop
				// Termination conditions: Game over conditions or user user chooses to quit this game
				while (userChoice_gmemenu != 4 && calculate_score(player1) > 0 && player1.steps > 0)
				{
					// Get user's next action
					userChoice_gmemenu = display_game_menu();
	
					// Create variable to hold encounter ID in
					u_short encID;

					// Execute the user's choice
					switch (userChoice_gmemenu)
					{
						case MOVE:
							encID = generate_encounter_ID();
							if (encID == PUZZLE)
							{
								move_forward(player1, encArray[encID], puzzleList);
							}
							else
							{
								move_forward(player1, encArray[encID]);
							}
							
							break;
						case READ:
							read_paper(player1);
							
							break;
						case SEARCH:
							search_change(player1);
			
							break;
						case VIEW_CHARACTER:
							view_character(player1);
						
							break;
						case QUIT_GAME:
							cout << "You want to quit?! And leave the Princess of Engineering to fend for herself?!?!? WHY?? YOU MONSTER!!! Fine, but just you let you know, you lost the game, and you get NO CAKE.\n";

							break;
						case EASTER_EGG_TRIGGER - 1:
							easter_egg_event(player1);
					}
				}
				
				// Communicate Game Over and the conditions that resulted in it
				if (userChoice_gmemenu == 4) break;
				if (calculate_score(player1) == 0)
				{
					if (player1.time <= 0)
					{
						cout << "You ran out of time! The Princess wasn't saved!! Her father beat you to her and saved her!!! He and the princess look down upon you in disappointment...\n";
					}
					if (player1.money <= 0)
					{
						cout << "Your TigerCard is EMPTY! You have no more money for Chick-fil-A, Panda Express, or Starbucks! What will you do?! You're forced to leave Shelby to try to phone all your friends and family for extra money. But for now, the princess' fate remains a mystery...\n";
					}
					if (player1.intel <= 0)
					{
						cout << "Just as you finish your last action...POP MIDTERM EXAM! Oh no, you failed the exam because your IQ is below the threshold needed to pass!! You fail the exam and your GPA falls drastically. The University is forced to send the grade police to Shelby to extract you for questioning and intensive retraining of your mind. You tell them of the princess but they don't believe you.\n\nThe next day you hear that the princess is later saved by a strange Italian plumber, who appeared through a green tube to extract the princess...of course, that's the least of your worries now\n";
					}
				}
				// Victory condition
				else if (player1.steps <= 0)
				{
					cout << "YOU DID IT!!!!!!! You, single-handedly, SAVED PRINCESS SHELBY! She is eternally grateful for your bravery and hard work to save her! As a token of her appreciation, she gives you her handkerchief. She then says \"Well, shall we ride off on your trusty steed?\" Oh no, the trusty steed? Where is your trust steed?!\n\nJust when you think all is lost, out of nowhere appears an orange and blue sports car!! You hope Princess Shelby doesn't notice it says \"TIGER TRANSIT\" on the side. Both of you hop in and drive off onto the concourse and into the sunset~\n";

					// Display final stats and score:
					cout << "\nYou saved the princess! Congrats! Here are your final stats:\n";
					view_character(player1);
					cout << "Final Score: " << player1.score << endl;

					// Attempt to add score to list
					if (add_new_score(sBoard, player1.score, player1.name) == 1)
					{
						cout << "\nSorry, but your final score was not high enough to be added to the scoreboard. Better luck next time!\n";
					}
					else
					{
						cout << "\nCongrats! You made it on the scoreboard! View the board on the main menu to see!\n";
						
						// Save scores to the user's specified file (if they spec'd one) OR to the default file
						if (filename.empty())
						{
							if (save_scores(sBoard) == 1)
							{
								cout << "\nERROR: Could not save scores to default file!\n";
							}
							else
							{
								cout << "\nScores saved to default file successfully!\n";
							}
						}
						else
						{
							if (save_scores(sBoard, filename.c_str()) == 1)
							{
								cout << "\nERROR: Could not save to user provided file!\n";
							}
							else
							{
								cout << "\nScores saved to user file \"" << filename << "\" successfully!\n";
							}
						}
					}
				}
				
				break;
			// View the scoreboard
			case VIEW_SCORES:
				view_scores(sBoard);
				break;
			// Quits the program
			case QUIT_PGM:
				cout << "You really want to quit? Very well, have a good day!\n";
				break;
		}
	}

	return 0;
}
