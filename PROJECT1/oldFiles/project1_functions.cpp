// Dragons - A simple text based game
// File contains function implementations used in main application 
// COMP2710 Project 1
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: project1_functions.cpp
// Written in Vi text editor
// Version: 4/11/2015, v1
// Sources used: Dr. Qin's PowerPoint on using cin to get string and int values, also 
// 			helpful for error-checking the input 
// 		 Dr. Qin's presentation of linked list operations

#include<cstdlib>			// for rand()
#include<iostream>			// for console out/in
#include<fstream>			// for file I/O
#include "project1_functions.h"
using namespace std;

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

// Creates a puzzle list using PREDEFINED settings
void create_puzzle_list(puzzleHead& p_head)
{
	// Iterator
	puzzleNodePtr curr;

	// Initialize head node
	p_head.numOfPuzzles = 6;
	p_head.first = new puzzleNode;
	curr = p_head.first;

	// PUZZLE 1
	curr->question = "What does 2 + 2 = ? ... IN BASE 4?\n1. 0\n2. 4\n3. 10\n4. 16\n5. REALLY? MATH? At a time like THIS?!\n";
	curr->answer = 3;
	curr->actionArray[0].actionType = REWARD;
	curr->actionArray[0].attrType = MONEY;
	curr->actionArray[0].points = 10;

	curr->actionArray[1].actionType = PENALTY;
	curr->actionArray[1].attrType = MONEY;
	curr->actionArray[1].points = -10;

	curr->actionArray[2].actionType = REWARD;
	curr->actionArray[2].attrType = TIME;
	curr->actionArray[2].points = -1;

	curr->actionArray[3].actionType = PENALTY;
	curr->actionArray[3].attrType = TIME;
	curr->actionArray[3].points = -2;

	curr->actionArray[4].actionType = REWARD;
	curr->actionArray[4].attrType = STEPS;
	curr->actionArray[4].points = -1;

	curr->actionArray[5].actionType = PENALTY;
	curr->actionArray[5].attrType = STEPS;
	curr->actionArray[5].points = -1;

	curr->numOfActions = 6;
	curr->next = new puzzleNode;
	curr = curr->next;

	// PUZZLE 2
	curr->question = "What do you do when life gives you lemons (according to Aperture Science)?\n1. Make lemonade\n2. Do what Cave Johnson said and make combustible lemons to burn people's houses down\n3. Go to Food Network and become the next Food Network Star...that really likes lemons\n";
	curr->answer = 2;
	curr->actionArray[0].actionType = REWARD;
	curr->actionArray[0].attrType = INTEL;
	curr->actionArray[0].points = 5;

	curr->actionArray[1].actionType = PENALTY;
	curr->actionArray[1].attrType = MONEY;
	curr->actionArray[1].points = -5;

	curr->actionArray[2].actionType = REWARD;
	curr->actionArray[2].attrType = TIME;
	curr->actionArray[2].points = -1;

	curr->actionArray[3].actionType = PENALTY;
	curr->actionArray[3].attrType = TIME;
	curr->actionArray[3].points = -1;

	curr->actionArray[4].actionType = REWARD;
	curr->actionArray[4].attrType = STEPS;
	curr->actionArray[4].points = -1;

	curr->actionArray[5].actionType = PENALTY;
	curr->actionArray[5].attrType = STEPS;
	curr->actionArray[5].points = 0;

	curr->numOfActions = 6;
	curr->next = new puzzleNode;
	curr = curr->next;	

	// PUZZLE 3
	curr->question = "Get this question right and WIN A TIME DILATION DEVICE! A popular protocol for communication between many digital electronics and microcontrollers in embedded systems is?\n1. PDI\n2. JTAG\n3. I2C\n4. IDC\n5. IDK\n";
	curr->answer = 3;
	curr->actionArray[0].actionType = REWARD;
	curr->actionArray[0].attrType = TIME;
	curr->actionArray[0].points = 5;

	curr->actionArray[1].actionType = PENALTY;
	curr->actionArray[1].attrType = TIME;
	curr->actionArray[1].points = -5;

	curr->actionArray[2].actionType = REWARD;
	curr->actionArray[2].attrType = STEPS;
	curr->actionArray[2].points = -1;

	curr->actionArray[3].actionType = PENALTY;
	curr->actionArray[3].attrType = STEPS;
	curr->actionArray[3].points = -1;

	curr->numOfActions = 4;
	curr->next = new puzzleNode;
	curr = curr->next;

	// PUZZLE 4
	curr->question = "WIN BIG BUCKS! The many islands of the State of Hawai'i include Hawai'i (Da Big Island), Oahu, Kauai, Lanai, and what other island?\n1. Maui\n2. Guam\n3. Puerto Rico\n4. Honolulu\n5. Da United States is one island yeah?";
	curr->answer = 1;
	curr->actionArray[0].actionType = REWARD;
	curr->actionArray[0].attrType = MONEY;
	curr->actionArray[0].points = 10;

	curr->actionArray[1].actionType = PENALTY;
	curr->actionArray[1].attrType = INTEL;
	curr->actionArray[1].points = -10;

	curr->actionArray[2].actionType = REWARD;
	curr->actionArray[2].attrType = TIME;
	curr->actionArray[2].points = -1;

	curr->actionArray[3].actionType = PENALTY;
	curr->actionArray[3].attrType = TIME;
	curr->actionArray[3].points = -1;

	curr->actionArray[4].actionType = REWARD;
	curr->actionArray[4].attrType = STEPS;
	curr->actionArray[4].points = -1;

	curr->actionArray[5].actionType = PENALTY;
	curr->actionArray[5].attrType = STEPS;
	curr->actionArray[5].points = -1;

	curr->numOfActions = 6;
	curr->next = new puzzleNode;
	curr = curr->next;
	
	// PUZZLE 5
	curr->question = "Take a LEAP forward if you win this one... Who is the most evilest, rage-inducing, OVERALL BADDEST, League of Legends champion ever?\n1. Sona\n2. The cute and cuddly Teemo\n3. URF the manatee\n4. Nocturne\n5. Really? LoL? Who plays that...\n ";
	curr->answer = 2;
	curr->actionArray[0].actionType = REWARD;
	curr->actionArray[0].attrType = TIME;
	curr->actionArray[0].points = -1;

	curr->actionArray[1].actionType = PENALTY;
	curr->actionArray[1].attrType = TIME;
	curr->actionArray[1].points = -1;

	curr->actionArray[2].actionType = REWARD;
	curr->actionArray[2].attrType = STEPS;
	curr->actionArray[2].points = -3;

	curr->actionArray[3].actionType = PENALTY;
	curr->actionArray[3].attrType = STEPS;
	curr->actionArray[3].points = 0;

	curr->numOfActions = 4;
	curr->next = new puzzleNode;
	curr = curr->next;
	
	// PUZZLE 6
	curr->question = "The Holy Overlord Urf the Manatee appears and decides to be nice to you, but first you answer his question: What does his name truly mean?\n1. Unruly Rascals Federation\n2. Unsubmerged Reptile of Fire\n3. Ultra Rapid Fire\n4. Used RAM for Free\n";
	curr->answer = 3;
	curr->actionArray[0].actionType = REWARD;
	curr->actionArray[0].attrType = MONEY;
	curr->actionArray[0].points = 5;

	curr->actionArray[1].actionType = PENALTY;
	curr->actionArray[1].attrType = MONEY;
	curr->actionArray[1].points = -5;

	curr->actionArray[2].actionType = REWARD;
	curr->actionArray[2].attrType = INTEL;
	curr->actionArray[2].points = 5;

	curr->actionArray[3].actionType = PENALTY;
	curr->actionArray[3].attrType = INTEL;
	curr->actionArray[3].points = -5;

	curr->actionArray[4].actionType = REWARD;
	curr->actionArray[4].attrType = TIME;
	curr->actionArray[4].points = -1;

	curr->actionArray[5].actionType = PENALTY;
	curr->actionArray[5].attrType = TIME;
	curr->actionArray[5].points = -1;

	curr->actionArray[6].actionType = REWARD;
	curr->actionArray[6].attrType = STEPS;
	curr->actionArray[6].points = -1;

	curr->actionArray[7].actionType = PENALTY;
	curr->actionArray[7].attrType = STEPS;
	curr->actionArray[7].points = -1;

	curr->numOfActions = 8;
	
	// END OF LIST
	curr->next = NULL;	
}

// Initializes encounters to the preset specs. The input array should NOT have been allocated yet (new)
// All point values are considered uninitialized since most of the values are to be randomized
void init_encounters(encounterPtr& encArray)
{
	// Initialize dynamic array
	encArray = new encounter[NUM_OF_ENCOUNTERS];

	// Initialize encounter elements 
	// NOTHING encounter
	encArray[0].enctType = NOTHING;
	encArray[0].message = "OH MY GOSH, NOTHING HAPPENS...\n";
	encArray[0].actionArray[0].actionType = REWARD;
	encArray[0].actionArray[0].attrType = STEPS;
	encArray[0].actionArray[0].points = -1;

	encArray[0].actionArray[1].actionType = PENALTY;
	encArray[0].actionArray[1].attrType = TIME;
	encArray[0].actionArray[1].points = -1;

	encArray[0].numOfActions = 2;

	// PUZZLE encounter
	// Info here is NOT handled through encounter functions but by puzzle functions. As such, values here are DONT CARES
	encArray[1].enctType = PUZZLE;
	encArray[1].message = "It's puzzle time!\n";
	encArray[1].actionArray[0].actionType = REWARD;
	encArray[1].actionArray[0].attrType = TIME;
	encArray[1].actionArray[0].points = 0;

	encArray[1].numOfActions = 1;

	// PROFESSOR encounter
	encArray[2].enctType = PROFESSOR;
	encArray[2].message = "You see a tall shadowy figure approach you...\n";
	encArray[2].actionArray[0].actionType = REWARD;
	encArray[2].actionArray[0].attrType = INTEL;
	encArray[2].actionArray[0].points = 1;

	encArray[2].actionArray[1].actionType = PENALTY;
	encArray[2].actionArray[1].attrType = TIME;
	encArray[2].actionArray[1].points = -1;

	encArray[2].actionArray[2].actionType = REWARD;
	encArray[2].actionArray[2].attrType = STEPS;
	encArray[2].actionArray[2].points = -1;

	encArray[2].numOfActions = 3;

	// STUDENT encounter
	encArray[3].enctType = STUDENT;
	encArray[3].message = "You see a short figure approach you...\n";
	encArray[3].actionArray[0].actionType = PENALTY;
	encArray[3].actionArray[0].attrType = TIME;
	encArray[3].actionArray[0].points = -1;

	encArray[3].actionArray[1].actionType = REWARD;
	encArray[3].actionArray[1].attrType = STEPS;
	encArray[3].actionArray[1].points = -1;

	encArray[3].numOfActions = 2;
	
	// GRUNT encounter
	encArray[4].enctType = GRUNT;
	encArray[4].message = "A small elfish figure hops towards you with something in his hand...\n";
	encArray[4].actionArray[0].actionType = PENALTY;
	encArray[4].actionArray[0].attrType = INTEL;
	encArray[4].actionArray[0].points = -1;

	encArray[4].actionArray[1].actionType = PENALTY;
	encArray[4].actionArray[1].attrType = TIME;
	encArray[4].actionArray[1].points = -1;

	encArray[4].actionArray[2].actionType = REWARD;
	encArray[4].actionArray[2].attrType = STEPS;
	encArray[4].actionArray[2].points = -1;

	encArray[4].numOfActions = 3;
	 
	// PAPER encounter
	encArray[5].enctType = PAPER;
	encArray[5].message = "A flying box of papers approaches your position!\n";
	encArray[5].actionArray[0].actionType = REWARD;
	encArray[5].actionArray[0].attrType = MONEY;
	encArray[5].actionArray[0].points = 1;

	encArray[5].actionArray[1].actionType = PENALTY;
	encArray[5].actionArray[1].attrType = TIME;
	encArray[5].actionArray[1].points = -1;

	encArray[5].actionArray[2].actionType = REWARD;
	encArray[5].actionArray[2].attrType = STEPS;
	encArray[5].actionArray[2].points = -1;

	encArray[5].numOfActions = 3;
}

// Displays socreboard to the user
void view_scores(scoreHead sBoard)
{
	// Initialize an iterator
	scoreNodePtr curr = sBoard.first;

	cout << "The top " << sBoard.numScores << " high scores are:\n";

	for (u_short i = 0; i < sBoard.numScores; i++) 
	{
		cout << (i + 1) << ". " << curr->name << ": " << curr->score << endl;
		curr = curr->next;

		// SAFETY
		if (curr == NULL) break;
	}

	// Termination line
	cout << "-No More Scores to Show-\n";
}

// Loads scores from the default file. Same as calling custom filename function with this filename
u_short load_scores(scoreHead& sBoard)
{
	return load_scores(sBoard, DEFAULT_SCOREBOARD_FILE);
}

// Loads scores from file. Will return non-zero if error occurs:
// @return	0 success
// 		1 file I/O error
// 		2 memory allocation error
u_short load_scores(scoreHead& sBoard, const char filename[])
{
	string tempName;
	int tempScore;
	scoreNodePtr curr, newNode;
	
	// Initialize input stream
	ifstream inStream;

	// Open file, return 1 if I/O error occurs
	inStream.open(filename);
	if (inStream.fail())
	{
		return 1;
	}

	inStream >> sBoard.numScores; // store number of scores (first line in file)

	newNode = new scoreNode;
	if (newNode == NULL) return 2;

	// Initialize first node in list
	if (inStream >> tempName && inStream >> tempScore)
	{
		newNode->name = tempName;
		newNode->score = tempScore;
		newNode->next = NULL;
		sBoard.first = newNode;
	}
	else
	{
		// List is EMPTY
		return 0;
	}

	curr = sBoard.first;

	// Continues until end of file reached
	while (inStream >> tempName)
	{
		// Check just to make sure end not reached...
		if (inStream >> tempScore)
		{
			newNode = new scoreNode;
			if (newNode == NULL) return 2;
	
			newNode->name = tempName;
			newNode->score = tempScore;
			newNode->next = NULL;
			curr->next = newNode;
			curr = curr->next;
		}
	}
	
	inStream.close();

	return 0;
}

// Saves scores to the default file
u_short save_scores(scoreHead sBoard)
{
	return save_scores(sBoard, DEFAULT_SCOREBOARD_FILE);
}

// Saves scores to a specified filename
// @return 	0 success
// 		1 file I/O error
u_short save_scores(scoreHead sBoard, const char filename[])
{
	// List iterator
	scoreNodePtr curr = sBoard.first;

	// Outstream
	ofstream outStream;

	outStream.open(filename);
	if (outStream.fail())
	{
		return 1;
	}

	// Write how many scores in board
	outStream << sBoard.numScores << endl;

	while (curr != NULL)
	{
		outStream << curr->name << endl << curr->score << endl;
		curr = curr->next;
	}

	outStream.close();

	return 0;
}

// Add a new score to the high score list IF it should be added
// @return	0 successfully added
// 		1 not added (probably due to 0 score OR not high enough)
// 		2 mem allocation erorr
u_short add_new_score(scoreHead& sBoard, int userScore, string userName)
{
	// Create iterators and new node ptr
	scoreNodePtr curr, pre, new_node;

	if (userScore <= 0)
	{
		// User score not able to be added, 0 or negative
		return 1;
	}

	// Initialize new node to be added
	new_node = new scoreNode;
	if (new_node == NULL) return 2;	// mem allocation error

	new_node->name = userName;
	new_node->score = userScore;
	new_node->next = NULL;

	// List is empty
	if (sBoard.first == NULL) 
	{
		sBoard.first = new_node;
	}
	// Else, add new node to appropiate position
	else
	{
		pre = NULL;
		curr = sBoard.first;
		
		while (curr != NULL && curr->score > userScore)
		{
			pre = curr;
			curr = curr->next;
		}
		
		// Curr holds position where new node should go, pre holds one before
		// If pre is null, insert at head of list
		if (pre == NULL)
		{
			new_node->next = sBoard.first;
			sBoard.first = new_node;
		}
		// Else, in middle of list
		else
		{
			new_node->next = curr;
			pre->next = new_node;
		}
	}

	sBoard.numScores++;

	// Check if limit of high scores exceeded because of this
	if (sBoard.numScores > MAX_NUM_OF_HIGH_SCORES)
	{
		// Delete the last node of the list
		delete_score_tail(sBoard);
		// If curr is NULL, then the new score was added to END of list, which was just deleted
		// by the last function. THEREFORE, the user's score was NOT added.
		if (curr == NULL) return 1;
	}

	return 0;
}

// Deletes the tail node in a scoreboard.
// @return	0 successful delete
// 		1 unsuccessful delete
u_short delete_score_tail(scoreHead& sBoard)
{
	// Initialize iterator
	scoreNodePtr curr, pre;
	
	// List is empty? Don't delete
	if (sBoard.first == NULL)
	{
		return 1;
	}

	// If list only has one node...
	if (sBoard.first->next == NULL)
	{
		delete sBoard.first;
		sBoard.first = NULL;
		sBoard.numScores--;
		return 0;
	}
	
	// List has more than one node
	pre = sBoard.first;
	curr = sBoard.first->next;
	// Iterate through list until end node is reached
	while (curr->next != NULL)
	{
		pre = curr;
		curr = curr->next;
	}

	pre->next = NULL;
	delete curr;
	sBoard.numScores--;

	return 0;	
}

// Calculate the player's score and stores it in the structure.
// If result is negative, will store 0 instead
// Also returns the calculated score
// @return user's calculated score
u_int calculate_score(player& userPlayer)
{
	// Variables
	int calculatedScore;
	
	// Score is all three attributes multiplied together
	calculatedScore = userPlayer.money * userPlayer.intel * userPlayer.time;

	// If score is negative, set it to 0
	if (calculatedScore < 0)
	{
		calculatedScore = 0;
	}

	userPlayer.score = calculatedScore;
	
	return userPlayer.score;
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

// Generates an encounter ID within the correct range of IDs
// @return random encounter ID according to game spec
u_short generate_encounter_ID()
{
	u_short encID;

	int randomNum = rand() % 100;

	// Depending on random num, select appropiate encID
	if (randomNum < 25) encID = NOTHING;
	else if (randomNum < 55) encID = PUZZLE;
	else if (randomNum < 65) encID = PROFESSOR;
	else if (randomNum < 75) encID = STUDENT;
	else if (randomNum < 90) encID = GRUNT;
	else encID = PAPER;

	return encID;
}

// Displays a professor encounter and modifies player
void professor_enc(player& userPlayer, encounter profEnc)
{
	// Determine how much to modify attributes by
	u_short modIntelBy = rand() % ENCOUNTER_POINT_UPPER_BOUND;
	short modTimeBy = -1 * ((rand() % ENCOUNTER_POINT_UPPER_BOUND) + 1);
	
	// Modify encounter so that it modifies the correct amount of points
	profEnc.actionArray[0].points = modIntelBy;
	profEnc.actionArray[1].points = modTimeBy;

	// Display some fun messages depending on modification
	if (modIntelBy == 0)
	{
		cout << "You run into a humanities professor...he's not very helpful\n";
	}
	else if (modIntelBy < ENCOUNTER_POINT_UPPER_BOUND - 1)
	{
		cout << "You find a helpful professor who provides you insight into your current situation\n";
	}
	else
	{
		cout << "You find a very insightful and ingenious professor! He gives you the secret to infinite wealth. He leans in and whispers: ";
		cout << EASTER_EGG_TRIGGER << endl;
	}

	cout << endl;

	if (modTimeBy == -1)
	{
		cout << "The professor just runs around you, saving you the time of talking\n";
	}
	else if (modTimeBy > ENCOUNTER_POINT_LOWER_BOUND + 1)
	{
		cout << "The professor takes up quite a bit of time...\n";
	}
	else
	{
		cout << "The professor takes up A TON OF TIME, but he drops a note that reads: the secret is " << EASTER_EGG_TRIGGER << endl;
	}

	// Modify attributes accordingly
	for (int i = 0; i < profEnc.numOfActions; i++)
	{
		point_handler(userPlayer, profEnc.actionArray[i]);
	}
}

// Runs a grad student encounter
void student_enc(player& userPlayer, encounter studEnc)
{
	// Determine how much to modify attributes by
	short modTimeBy = -1 * ((rand() % ENCOUNTER_POINT_UPPER_BOUND) + 1);

	// Modify encounter accordingly
	studEnc.actionArray[0].points = modTimeBy;

	// Display some fun messages
	if (modTimeBy == -1)
	{
		cout << "You run into your fellow...ARCH NEMESIS! He says his usual speech about how he'll do better than you and blah blah, you ignored him halfway though so you saved time, good for you\n";
	}
	else if (modTimeBy > ENCOUNTER_POINT_LOWER_BOUND + 1)
	{
		cout << "You run into your primary arch nemesis!!! He says his usual speech about how not only will he do better than you, but he will also rule the world, the galaxy, and then the universe. Once he started talking about space you got really interested though so instead of moving onward with your quest, you listen to your nemesis. A slow clap for you, hero\n";
	}
	else
	{
		cout << "It's your friend! He's pretty cool to talk to, so instead of focusing on your mission to save Princess Shelby, you talk with your friend about things like ponies, video games, space, life, oh look at the time you lost...good job, hero\n";
	}

	// Modify attributes accordingly
	for (int i = 0; i < studEnc.numOfActions; i++)
	{
		point_handler(userPlayer, studEnc.actionArray[i]);
	}
}

// Runs a grunt work encounter
void grunt_enc(player& userPlayer, encounter gruntEnc)
{
	// Determine how much to modify attrbiutes by
	short modIntelBy = -1 * ((rand() % ENCOUNTER_POINT_UPPER_BOUND) + 1);
	short modTimeBy = -1 * ((rand() % ENCOUNTER_POINT_UPPER_BOUND) + 1);

	// Modify encounter accordingly
	gruntEnc.actionArray[0].points = modIntelBy;
	gruntEnc.actionArray[1].points = modTimeBy;

	// Display some fun messages
	if (modIntelBy == -1)
	{
		cout << "Oh no, a grunt, he's giving you work, oh no, it's, it's.....oh, it's just signing an attendence sheet. You can do that, right?\n";
	}
	else if (modIntelBy > ENCOUNTER_POINT_LOWER_BOUND + 1)
	{
		cout << "A grunt! What's he doing?! Oh no, he's giving you work, you must resist, RESIST THE WORK...it didn't work. You're forced to work now, so sad\n";
	}
	else
	{
		cout << "It's a grunt, he gives you a creepy smile and proceeds to throw sheets of paper at you! Each one is something worse and more mediocre of a task than the last! You scream for help, no, no, NO, PLEASE NO MORE, NO MORE WORK!!!, NOOOOOOOOOOOOOOOOOOOOOOOOOOO\n";
	}

	cout << endl;

	if (modTimeBy == -1)
	{
		cout << "You somehow managed to complete the work very quickly, good for you\n";
	}
	else if (modTimeBy > ENCOUNTER_POINT_LOWER_BOUND + 1)
	{
		cout << "Whelp, that took some time to do, but you got it done...sadly, you get no compensation\n";
	}
	else
	{
		cout << "OH MY GOSH THAT GRUNT GAVE YOU SOOOOOO MUCH WORK. You started WHINING half-way through, taking up SOOOOOOO much more time than needed...\n";
	}

	// Modify character
	for (int i = 0; i < gruntEnc.numOfActions; i++)
	{
		point_handler(userPlayer, gruntEnc.actionArray[i]);
	}
}

// Runs a grade papers encounter
void paper_enc(player& userPlayer, encounter papEnc)
{
	// Set how much to modify attributes by
	u_short modMoneyBy = rand() % ENCOUNTER_POINT_UPPER_BOUND + 1;
	short modTimeBy = -1 * ((rand() % ENCOUNTER_POINT_UPPER_BOUND) + 1);

	// Modify encounter accordingly
	papEnc.actionArray[0].points = modMoneyBy;
	papEnc.actionArray[1].points = modTimeBy;

	// Display some fun messages
	if (modMoneyBy == 1)
	{
		cout << "You got papers to grade! But it's all for that 1000-level class...so you don't get paid a lot\n";
	}
	else if (modMoneyBy < ENCOUNTER_POINT_UPPER_BOUND - 1)
	{
		cout << "The wild flying paper box is full of things to grade! You choose to grade, ALL OF EM!! Your pay is decent at least\n";
	}
	else
	{
		cout << "The wild flying paper box ATTACKED! You use graduate student powers! It's super effective!! The box drops with money falling out of it! You find one paper left to grade, the student's answer to number 7 is " << EASTER_EGG_TRIGGER << ". Odd...that correct answer was obviously \"DONUTS\", why put a number there...hm, weird, indeed\n";
	}

	cout << endl;

	if (modTimeBy == -1)
	{
		cout << "Phew, grading went by very quickly. Nice job, you hard worker!\n";
	}
	else if (modTimeBy > ENCOUNTER_POINT_LOWER_BOUND + 1)
	{
		cout << "Finish up, you're burning time!! You get through it, not before wasting time doodling on your student's papers!\n";
	}
	else
	{
		cout << "Wow, really, you took THAT LONG to grade? Those papers must've been really tough...hopefully it'll all be worth it right? Maybe the Princess will have more money than you, then you don't have to grade...\n";
	}

	// Modify player
	for (int i = 0; i < papEnc.numOfActions; i++)
	{
		point_handler(userPlayer, papEnc.actionArray[i]);
	}
}

// Asks a random puzzle question from the list. Modifies attributes accordingly
void ask_puzzle(player& userPlayer, puzzleHead p_head)
{
	// Variables
	u_short userAnswer;	
	action_t rewardOrPenalty;

	// Select a puzzle within range [0 - numOfPuzzles] randomly
	u_short puzzleSelect = rand() % p_head.numOfPuzzles;

	// Iterator
	puzzleNodePtr curr = p_head.first;

	// Get iterator to the puzzle selected by random generator
	for (int i = 0; i < puzzleSelect && curr != NULL; i++)
	{
		curr = curr->next;
	}
	
	// Display the question for this puzzle:
	cout << curr->question;

	// Get user's answer
	cout << "\nChoose wisely: ";
	userAnswer = valid_int_input();

	// Check is answer is correct, then perform action related to that
	if (userAnswer == curr->answer)
	{
		cout << "*** YOU GOT IT RIGHT! Good Job...are you surprised?\n";
		rewardOrPenalty = REWARD;
	}
	else
	{
		cout << "*** YOU GOT IT WRONG!? HOW?? Oh well, better luck next time eh?\n";
		rewardOrPenalty = PENALTY;
	}
	
	// Modify player
	for (int i = 0; i < curr->numOfActions; i++)
	{
		// Action in action array for puzzle is either REWARD or PENALTY, execute only ones that appliy
		if (curr->actionArray[i].actionType == rewardOrPenalty)
		{
			point_handler(userPlayer, curr->actionArray[i]);
		}
	}

	cout << endl;
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
