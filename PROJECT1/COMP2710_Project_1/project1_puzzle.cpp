// Dragons - A simple text based game
// File contains function implementations for puzzles 
// COMP2710 Project 1
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: project1_puzzle.cpp
// Written in Vi text editor
// Version: 4/13/2015, v1
// Sources used: Dr. Qin's presentation of linked list operations

#include "project1_puzzle.h"

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
}
