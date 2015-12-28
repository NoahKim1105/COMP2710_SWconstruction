// Dragons - A simple text based game 
// COMP2710 Project 1 - Phase 2 Design
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: project1-design.cpp
// Written in Vi text editor, compiled with g++ -o project1-design project1-design.cpp
// Version: 4/3/2015, v1
// Sources used: Dr. Qin's source for dragons_datastructures_new_design.cpp
// 		 Dr. Qin's PowerPoint on using cin to get string and int values, also 
// 			helpful for error-checking the input 
// 		 Stack Overflow forum for finding length of string object

#include<cstdlib>
#include<iostream>
#include<stdio.h>
#include<assert.h>
#include<string>
using namespace std;

// Comment this line out to enable production version of code!
#define UNIT_TESTING

typedef unsigned short u_short;

/********************* SECTION 1: DATA STRUCTURES ************************/

// Score board structures, one for nodes and one for head
struct scoreNode {
	string name;	// Holds name of user with high score
	int score;	// Holds the score
	scoreNode *next;
};

// Convenience typedef
typedef scoreNode* scoreNodePtr;

struct scoreHead {
	u_short numScores;	// Holds how many scores in list
	scoreNodePtr first;	// First score in board
};

// Player data structure
struct player {
	string name;	// Player's name as entered by user
	int money;	// Various player attributes
	int time;
	int intel;
	int steps;	// Steps from goal
	int score; 	// Stores player's calculated score
};

// Data structures relevent to puzzles
const int MAX_NUM_ACTION = 8;	 // Max actions can be taken (2 for each attribute, a penalty and a reward)

// Enumerated types describing different attributes to be affected
enum attribute_t {MONEY, TIME, INTEL, STEPS};
enum action_t {PENALTY, REWARD};

struct action {
	action_t actionType; 	// Penalize or Reward attribute
	attribute_t attrType;	// Which attribute is modified
	short points;		// By how much attribute modified (CAN BE NEGATIVE)
};

struct puzzleNode {
	// Particular puzzle's information
	string question;
	string answer;
	
	// Action to take:
	// Array allows for multiple attribute modifications, up to all 4 attributes penalized or rewarded.
	// Array needs to be initialized with all possibilities when puzzle node created.
	// DESIGN TAKEN FROM DR. QIN's SAMPLE CODE
	action actionArray[MAX_NUM_ACTION];	// Stores all possible actions by this puzzle question
	u_short numOfActions;			// How many actions in array currently
	puzzleNode *next;
};

typedef puzzleNode* puzzleNodePtr;

struct puzzleHead {
	u_short numOfPuzzles;	// Number of puzzles in list
	puzzleNodePtr first;
};

// Data structures related to encounters
enum encounter_t {NOTHING, PUZZLE, PROFESSOR, STUDENT, GRUNT, PAPER};

// Design structure similarly to puzzle data structures
// HOWEVER: List not needed!
// IMPLEMENTATION: Utilize a dynamic (or static) array of encounter type!
struct encounter {
	encounter_t enctType;
	string message;	

	// Action to take:
	action actionArray[MAX_NUM_ACTION];
	u_short numOfActions;
};

// Typedef to set type of dynamic array
typedef encounter* encounterPtr;

// Enumerated types for System Menu and for Game Menu options
enum system_menu_t {VIEW_SCORES, START_GAME, QUIT_PGM};
enum game_menu_t {MOVE, READ, SEARCH, VIEW_CHARACTER, QUIT_GAME};

/********************* SECTION 2: FUNCTION PROTOTYPES ********************/

// Functions for initialization
/**
 * Runs login process. Asks user to enter name and saves it.
 * @param userName	String to store desired name
 */
void login_process(string& userName);
/**
 * Initializes character with provided name and randomly selects attribute values (except steps from goal preset).
 * @param userName	String that stores player's desired name
 * @param userPlayer	Character structure to store newly created player
 */
void init_character(string userName, player& userPlayer);
/**
 * Initializes puzzle list to preset values
 * @param p_head	Points to puzzle list's head node
 */
void create_puzzle_list(puzzleHead& p_head);
/**
 * Initializes puzzles list according to data in a file
 * @param p_head	Points to puzzle list's head node
 * @param filename	Input file name
 * @return 		Error code, not zero if error occurs
 */
int create_puzzle_list(puzzleHead& p_head, const char filename[]);
/**
 * Initializes encounter array to preset values
 * @param encArray	Pointer to first element in array
 */
void init_encounters(encounterPtr& encArray);

// Functions for scoreboard operations
/**
 * Function to display the scores stored in the scoreboard.
 * @param sBoard	head node of scoreboard list
 */
void view_scores(scoreHead sBoard);
/**
 * Function to load scores from a file.
 * NOTE: Assumes scores are sorted in file with HIGHEST first line
 * @param sBoard	head node of scoreboard list
 * @return		error code, not zero if error occurs
 */
int load_scores(scoreHead& sBoard);
/**
 * Overloaded of last function, but allows user-provided filename.
 * @param sBoard	head node of scoreboard list
 * @param filename	char array of file's name
 * @return 		error code, not zero if error occurs
 */
int load_scores(scoreHead& sBoard, const char filename[]);
/**
 * Function to save scoreboard to a file.
 * @param sBoard	head node of scoreboard list
 * @return		error code, not zero if error occurs
 */
int save_scores(scoreHead sBoard);
/**
 * Overloaded of last function, but allows user-provided filename.
 * @param sBoard	head node of scoreboard list
 * @param filename	char array of file's name
 * @return		error code, not zero if error occurs
 */
int save_scores(scoreHead sBoard, const char filename[]);
/**
 * Adds new score to list IF score is high enough to be on.
 * MUST keep list in sorted order!
 * Will also remove a score if adding new one makes list longer than max
 * @param sBoard	head node of scoreboard list
 * @param userScore	user's final score
 * @param userName	user's name to be added
 * @return		0 if added successfully, 1 if not
 */
int add_new_score(scoreHead& sBoard, int userScore, string userName);
/**
 * Calculates player's score and stores it in player's structure
 * @param userPlayer	user's character at end of game
 */
void calculate_score(player& userPlayer);

// Function for handling user input
/**
 * Asks user for numeric input and ensures only a valid number is returned (nonnegative)
 * @return		User entered integer
 */
int valid_int_input(void);

// Functions to execute user choices
/**
 * Displays the current status of the user's character
 * @param userPlayer	user's character
 */
void view_character(player userPlayer);
/**
 * User selects to read a paper. Randomly affects attributes.
 * Increase intel, decrease time.
 * @param userPlayer	user's character
 */
void read_paper(player& userPlayer);
/** 
 * User selects to search for change. Randomly affects attributes.
 * Increase money, decrease time.
 * @param userPlayer	user's character
 */
void search_change(player& userPlayer);
/**
 * If user activates easter event.
 * Warning: Will terminate program immediately.
 * @param userPlayer	user's character
 */
void easter_egg_event(player& userPlayer);
/**
 * Moves forward one. Also chance of generating an event.
 * Handles encounters (but NOT puzzles) itself. If is puzzle, calls that function. 
 * @param userPlayer	user's character
 * @param encArray	dynamic array of possible encounters
 * @param p_head	root of puzzle linked list, needed if encounter is puzzle
 */
void move_forward(player& userPlayer, encounterPtr encArray, puzzleHead p_head);
/**
 * Generates a random (valid) encounter ID.
 * @return integer within range for a valid encounter ID.
 */
int generate_encounter_ID(void);

// Functions to handle puzzles
/**
 * Asks the user a puzzle question. Depending on answer, will modify attributes accordingly.
 * @param userPlayer	user's character
 * @param p_head	points to head of puzzle list
 */
void ask_puzzle(player& userPlayer, puzzleHead p_head);

// Convenience functions to display menus
/**
 * Displays the system menu
 */
void display_sys_menu(void);
/**
 * Displays the game menu
 */
void display_game_menu(void);

// UNIT TESTING FUNCTIONS
#ifdef UNIT_TESTING
// Should be one test function for each production function:
// Note: easter egg event cannot be tested properly as doing so will terminate program
void test_login_process(void);
void test_init_character(void);
void test_create_puzzle_list(void);
void test_init_encounters(void);
void test_view_scores(void);
void test_load_scores(void);
void test_save_scores(void);
void test_add_new_score(void);
void test_calculate_score(void);
void test_valid_int_input(void);
void test_view_character(void);
void test_read_paper(void);
void test_search_change(void);
void test_move_forward(void);
void test_generate_encounter_ID(void);
void test_ask_puzzle(void);
void test_display_sys_menu(void);
void test_display_game_menu(void);
#endif

/********************* SECTION 3: MAIN/PRODUCTION CODE ********************/
// Constants to make code more maintainable

// Bounds for initial attributes
const int ATTRIBUTE_LOWER_BOUND = 8;
const int ATTRIBUTE_UPPER_BOUND = 25;
const int TIME_LOWER_BOUND = 15;
const int TIME_UPPER_BOUND = 25;
const int INITIAL_STEPS_FROM_GOAL = 20;

// Specify amount of puzzles and encounters for presets
const int NUM_OF_PUZZLES = 6;
const int NUM_OF_ENCOUNTERS = 6;

// Bounds for points encounters can take away or add (random within bounds)
const int ENCOUNTER_POINT_LOWER_BOUND = -20;
const int ENCOUNTER_POINT_UPPER_BOUND = 20;

// Scoreboard contains max amount of scores
const int MAX_NUM_OF_HIGH_SCORES = 10;

// Default scoreboard file name input/output
const char DEFAULT_SCOREBOARD_FILE[] = "scoreboard.txt";

int main()
{
	return 0;
}

// The following are just function stubs and are not fully defined until the next phase of the design

void login_process(string& userName)
{
	return;
}

void init_character(string userName, player& userPlayer)
{
	return;
}

void create_puzzle_list(puzzleHead& p_head)
{
	return;
}

int create_puzzle_list(puzzleHead& p_head, const char filename[])
{
	return 0;
}

void init_encounters(encounterPtr& encArray)
{
	return;
}

void view_scores(scoreHead sBoard)
{
	return;
}

int load_scores(scoreHead& sBoard)
{
	return 0;
}

int load_scores(scoreHead& sBoard, const char filename[])
{
	return 0;
}

int save_scores(scoreHead sBoard)
{
	return 0;
}

int save_scores(scoreHead sBoard, const char filename[])
{
	return 0;
}

int add_new_score(scoreHead& sBoard, int userScore, string userName)
{
	return 0;
}

void calculate_score(player& userPlayer)
{
	return;
}

int valid_int_input()
{
	return 0;
}

void view_character(player userPlayer)
{
	return;
}

void read_paper(player& userPlayer)
{
	return;
}

void search_change(player& userPlayer)
{
	return;
}

void easter_egg_event(player& userPlayer)
{
	return;
}

void move_forward(player& userPlayer, encounterPtr encArray, puzzleHead p_head)
{
	return;
}

int generate_encounter_ID()
{
	return 0;
}

void ask_puzzle(player& userPlayer, puzzleHead p_head)
{
	return;
}

void display_sys_menu()
{
	return;
}

void display_game_menu()
{
	return;
}

/********************* SECTION 4: UNIT TEST CASES CODE ********************/
#ifdef UNIT_TESTING

void test_login_process()
{
	// Initialize test fixtures
	string userName = "";

	cout << "\nUnit Test 1: void login_process(string& userName)\n";
	
	// Case 1.1: Prompt for a name, valid name is entered
	cout << "\tCase 1.1: Enter a valid username when prompted\n";
	login_process(userName);
	
	assert(!userName.empty());	// If not empty, then user entered a value successfully
	cout << "\tCase 1.1 Passed...\n";
}

void test_init_character()
{
	// Initialize test fixtures
	string userName1 = "GLaDOS";
	player player1;
	
	cout << "\nUnit Test 2: void init_character(string userName, player& userPlayer)\n";

	// Case 2.1: Initialize player1 properly
	cout << "\tCase 2.1: Initialize character to legal values with a given username\n";
	init_character(userName1, player1);

	assert(player1.name == userName1);
	assert(player1.money >= ATTRIBUTE_LOWER_BOUND && player1.money <= ATTRIBUTE_UPPER_BOUND);	// valid range for initial values
	assert(player1.time >= TIME_LOWER_BOUND && player1.time <= TIME_UPPER_BOUND);
	assert(player1.intel >= ATTRIBUTE_LOWER_BOUND && player1.intel <= ATTRIBUTE_UPPER_BOUND);
	assert(player1.steps == INITIAL_STEPS_FROM_GOAL);						// whatever initial steps should be (PRESET)
	assert(player1.score == 0);									// score init to 0

	cout << "\tCase 2.1 Passed...\n";
}

void test_create_puzzle_list()
{
	// Initialize test fixtures
	puzzleHead puzzle1;	
	puzzleNodePtr currentNode;

	string question1 = "Q1";	// @todo: ADD REAL VALUES FOR Q's and A's
	string answer1 = "A1";		// @todo: possibly change amount of puzzles
	string question2 = "Q2";
	string answer2 = "A2";
	string question3 = "Q3";
	string answer3 = "A3";
	string question4 = "Q4";
	string answer4 = "A4";
	string question5 = "Q5";
	string answer5 = "A5";
	string question6 = "Q6";
	string answer6 = "A6";
	
	action nullAction = {REWARD, MONEY, 0};	// a "NULL" action, just for filler in 2D array

	// @todo: ALTER ONCE REAL VALUES PLANNED (FOR PUZZLE ACTIONS AND NUMBER OF ACTIONS)
	u_short numOfActions1 = 6;
	u_short numOfActions2 = 6;
	u_short numOfActions3 = 4;
	u_short numOfActions4 = 6;
	u_short numOfActions5 = 4;
	u_short numOfActions6 = 8;

	// Create arrays to allow iteration over all elements cleaner to perform tests
	string questionArray[] = {question1, question2, question3, question4, question5, question6};
	string answerArray[] = {answer1, answer2, answer3, answer4, answer5, answer6};
	// Individual action arrays for each event. Unfortunately, couldn't make it any cleaner...
	action actionArrays[6][8] = {{{REWARD, MONEY, 10}, {PENALTY, MONEY, -10}, {REWARD, TIME, -1}, {PENALTY, TIME, -2}, {REWARD, STEPS, -1}, {PENALTY, STEPS, -1},
	/** PUZZLE1 */			nullAction, nullAction},
	/** PUZZLE2 */		     {{REWARD, INTEL, 5}, {PENALTY, MONEY, -5}, {REWARD, TIME, -1}, {PENALTY, TIME, -1}, {REWARD, STEPS, -1}, {PENALTY, STEPS, 0},
					nullAction, nullAction},
	/** PUZZLE3 */		     {{REWARD, TIME, 5}, {PENALTY, TIME, -5}, {REWARD, STEPS, 0}, {PENALTY, STEPS, 1}, nullAction, nullAction, nullAction, nullAction},
	/** PUZZLE4 */		     {{REWARD, MONEY, 20}, {PENALTY, INTEL, -15}, {REWARD, TIME, -1}, {PENALTY, TIME, -1}, {REWARD, STEPS, -1}, {PENALTY, STEPS, -1},
					nullAction, nullAction},
	/** PUZZLE5 */		     {{REWARD, TIME, -1}, {PENALTY, TIME, -1}, {REWARD, STEPS, -3}, {PENALTY, STEPS, 0}, nullAction, nullAction, nullAction, nullAction},
	/** PUZZLE6 */		     {{REWARD, MONEY, 5}, {PENALTY, MONEY, -5}, {REWARD, INTEL, 5}, {PENALTY, INTEL, -5}, {REWARD, TIME, -1}, {PENALTY, TIME, -1},
					{REWARD, STEPS, -1}, {PENALTY, STEPS, -1}}};
	u_short numOfActionsArray[] = {numOfActions1, numOfActions2, numOfActions3, numOfActions4, numOfActions5, numOfActions6};

	cout << "\nUnit Test 3: void create_puzzle_list(puzzleHead p_head)\n";

	// Case 3.1: Initialize puzzle list
	cout << "\tCase 3.1: Initialize puzzle list properly\n";
	create_puzzle_list(puzzle1);

	assert(puzzle1.numOfPuzzles == NUM_OF_PUZZLES);
	currentNode = puzzle1.first;

	for (int i = 0; i < NUM_OF_PUZZLES; i++)
	{
		assert(currentNode->question == questionArray[i]);
		assert(currentNode->answer == answerArray[i]);
		assert(currentNode->numOfActions == numOfActionsArray[i]);

		for (int j = 0; j < numOfActionsArray[i]; j++)
		{
			// Check action array properties!
			action currentElement = currentNode->actionArray[j];
			assert(currentElement.actionType == actionArrays[i][j].actionType);
			assert(currentElement.attrType == actionArrays[i][j].attrType);
			assert(currentElement.points == actionArrays[i][j].points);
		}
	
		currentNode = currentNode->next;
	}
	
	assert(currentNode == NULL);	// reached end of list
	cout << "\tCase 3.1 Passed...\n";
}

void test_init_encounters()
{
	// Initialize test fixtures
	encounterPtr encDynArray;	
	
	string message1 = "M1";		// @todo: add appropiate messages
	string message2 = "M2";
	string message3 = "M3";
	string message4 = "M4";
	string message5 = "M5";
	string message6 = "M6";

	action nullAction = {REWARD, MONEY, 0};	// a "NULL" action, just for filler in 2D array

	u_short numOfActions1 = 2;	
	u_short numOfActions2 = 1;
	u_short numOfActions3 = 3;
	u_short numOfActions4 = 2;
	u_short numOfActions5 = 3;
	u_short numOfActions6 = 3;

	// Create arrays to make test code easier to read
	string messageArray[] = {message1, message2, message3, message4, message5, message6};
	encounter_t enctTypesArray[] = {NOTHING, PUZZLE, PROFESSOR, STUDENT, GRUNT, PAPER};
	action actionArrays[6][3] = {{{REWARD, STEPS, -1}, {PENALTY, STEPS, -1}, nullAction},		// NOTHING
				     {{REWARD, TIME, 0}, nullAction, nullAction},			// PUZZLE: determined by puzzle, NOT ENCOUNTER
				     {{REWARD, INTEL, 1}, {PENALTY, TIME, -1}, {REWARD, STEPS, -1}},	// PROFESSOR: point value DONT CARE: RANDOMIZED by function
				     {{PENALTY, TIME, -1}, {REWARD, STEPS, -1}, nullAction},		// STUDENT: point value DONT CARE: RANDOMIZED
				     {{PENALTY, INTEL, -1}, {PENALTY, TIME, -1}, {REWARD, STEPS, -1}},	// GRUNT: point value DONT CARE: RANDOMIZED
				     {{REWARD, MONEY, 1}, {PENALTY, TIME, -1}, {REWARD, STEPS, -1}}}; 	// PAPER: point value DONT CARE: RANDOMIZED
	u_short numOfActionsArray[] = {numOfActions1, numOfActions2, numOfActions3, numOfActions4, numOfActions5, numOfActions6};

	cout << "\nUnit Test 4: void init_encounters(encounterPtr& encArray)\n";

	// Case 4.1: Properly initialize encounters array
	cout << "\tCase 4.1: Properly initialize encounters array\n";
	init_encounters(encDynArray);
	
	for (int i = 0; i < NUM_OF_ENCOUNTERS; i++)
	{
		encounter currentElement = *(encDynArray + i);
		assert(currentElement.message == messageArray[i]);
		assert(currentElement.enctType == enctTypesArray[i]);
		assert(currentElement.numOfActions == numOfActionsArray[i]);

		for (int j = 0; j < numOfActionsArray[i]; j++)
		{
			// Check all properties of action arrays
			action currentAction = currentElement.actionArray[j];
			assert(currentAction.actionType == actionArrays[i][j].actionType);
			assert(currentAction.attrType == actionArrays[i][j].attrType);
			if (i >= 2) 
			{
				// Needed since these values should be RANDOMIZED
				assert(currentAction.points >= ENCOUNTER_POINT_LOWER_BOUND);
				assert(currentAction.points <= ENCOUNTER_POINT_UPPER_BOUND);
				if ((i == 2 || i == 5) && j == 0)	// These values must be POSITIVE
				{
					assert(currentAction.points >= 0);
				}
				else if ((i == 3 || i == 4) && j == 0)	// must be NEGATIVE
				{
					assert(currentAction.points <= 0);
				}
				if (j == 1 || j == 2)	// must also be NEGATIVE
				{
					assert(currentAction.points <= 0);
				}
			}
			else
			{
				assert(currentAction.points == actionArrays[i][j].points);
			}
		}
	}	
	
	cout << "\tCase 4.1 Passed...\n";

	// Cleanup
	delete[] encDynArray;
	encDynArray = NULL;
}

void test_view_scores()
{
	// Initialize test fixtures
	scoreHead sBoard = {2, new scoreNode};
	sBoard.first->name = "GLaDOS";
	sBoard.first->score = 9001;
	sBoard.first->next = new scoreNode;
	sBoard.first->next->name = "Chell";
	sBoard.first->next->score = 10;
	sBoard.first->next->next = NULL; 

	cout << "\nUnit Test 5: void view_scores(scoreHead sBoard)\n";

	// Case 5.1: Displays 2 scores from list
	cout << "\tCase 5.1: Should display 2 scores from list with termination line\n";
	view_scores(sBoard);

	cout << "\tCase 5.1 Passed...\n";
}

// DO NOT INCLUDE THIS IN FINAL VERSION --- REQUIRES AN EXTRA INPUT FILE
void test_load_scores()
{
	// Initialize test fixtures
	char filename1[] = "scoreboard.txt";
	char filenameDNE[] = "IreallyHopeYoudonthaveThisfileforREALS.txt";
	scoreHead sBoard;	
	scoreHead sBoardDNE;

	cout << "\nUnit Test 6: int load_scores(scoreHead& sBoard, const char filename[])\n";

	// Case 6.1: load scores from a file that doesn't exist
	cout << "\tCase 6.1: Attempt to load scores from a file that doesn't exist\n";
	int errorCode = load_scores(sBoardDNE, filenameDNE);
	
	assert(errorCode != 0);

	cout << "\tCase 6.1 Passed...\n";

	// Case 6.2: load scores from a real file
	cout << "\tCase 6.2: Attempt to load scores from a real file\n";
	errorCode = load_scores(sBoard, filename1);

	assert(errorCode == 0);
	// @todo: ADD ASSERTIONS FOR WHAT SCOREBOARD SHOULD BE ACCORDING TO FILE

	cout << "\tCase 6.2 Passed...\n";
}

void test_save_scores()
{
	// Initialize test fixtures
	char filename1[] = "scoreboard_TEST.txt";
	scoreHead sBoard = {2, new scoreNode};
	sBoard.first->name = "GLaDOS";
	sBoard.first->score = 9001;
	sBoard.first->next = new scoreNode;
	sBoard.first->next->name = "Chell";
	sBoard.first->next->score = 10;
	sBoard.first->next->next = NULL; 

	cout << "\nUnit Test 7: int save_scores(scoreHead sBoard, const char filename[])\n";

	// Case 7.1: write scores to file
	cout << "\tCase 7.1: Save scores to a file called scoreboard_TEST.txt\n";
	int errorCode = save_scores(sBoard, filename1);

	assert(errorCode == 0);
	
	// @todo: Possibly add assertions for checking saved file? 
	
	cout << "\tCase 7.1 Passed...\n";
}

void test_add_new_score()
{
	// Initialize test fixtures
	int userScore1 = 5;
	int userScore2 = 1;
	int userScore3 = 9002;
	int userScore4 = 5000;
	int userScore5 = 0;
	int errorCode;

	string name1 = "Wheatley";	
	string name2 = "SPAAAAACE";
	string name3 = "Cave Johnson";

	scoreHead emptySboard = {0, NULL};
	scoreHead sBoard = {2, new scoreNode};
	sBoard.first->name = "GLaDOS";
	sBoard.first->score = 9001;
	sBoard.first->next = new scoreNode;
	sBoard.first->next->name = "Chell";
	sBoard.first->next->score = 10;
	sBoard.first->next->next = NULL; 
	
	scoreNodePtr currentNode;

	cout << "\nUnit Test 8: int add_new_score(scoreHead& sBoard, int userScore, string userName)\n";

	// Case 8.1: Add new score to an empty scoreboard
	cout << "\tCase 8.1: Add new score to an empty scoreboard\n";
	errorCode = add_new_score(emptySboard, userScore1, name1);

	assert(errorCode == 0);
	assert(emptySboard.numScores == 1);
	assert(emptySboard.first != NULL);
	assert(emptySboard.first->name == name1);
	assert(emptySboard.first->score == userScore1);

	cout << "\tCase 8.1 Passed...\n";	

	// Case 8.2: Add new score to the end of a scoreboard
	cout << "\tCase 8.2: Add new score to the end of a scoreboard\n";
	errorCode = add_new_score(sBoard, userScore2, name1);	

	assert(errorCode == 0);
	assert(sBoard.numScores == 3);

	currentNode = sBoard.first->next->next;

	assert(currentNode->name == name1);
	assert(currentNode->score == userScore2);
	assert(currentNode->next == NULL);

	cout << "\tCase 8.2 Passed...\n";

	// Case 8.3: Add new score to start of a scoreboard
	cout << "\tCase 8.3: Add new score to start of a scoreboard\n";
	errorCode = add_new_score(sBoard, userScore3, name2);

	assert(errorCode == 0);
	assert(sBoard.numScores == 4);

	currentNode = sBoard.first;

	assert(currentNode->name == name2);
	assert(currentNode->score == userScore3);
	assert(currentNode->next->name == "GLaDOS");

	cout << "\tCase 8.3 Passed...\n";

	// Case 8.4: Add new score to middle of a scoreboard
	cout << "\tCase 8.4: Add new score to middle of a scoreboard\n";
	errorCode = add_new_score(sBoard, userScore4, name3);

	assert(errorCode == 0);
	assert(sBoard.numScores == 5);

	currentNode = sBoard.first->next->next;

	assert(currentNode->name == name3);
	assert(currentNode->score == userScore4);
	assert(currentNode->next->name == "Chell");

	cout << "\tCase 8.4 Passed...\n";

	// Case 8.5: Attempt to add an invalid score
	cout << "\tCase 8.5: Attempt to add an invalid score (0)\n";
	errorCode = add_new_score(sBoard, userScore5, name3);

	assert(errorCode != 0);

	cout << "\tCase 8.5 Passed...\n";
}

void test_calculate_score()
{
	// Initialize test fixtures
	player player1 = {"Don't need a name", 10, 2, 6, 0, 0}; 
	player player2 = {"HOW DID YOU?", 10, -1, 4, 0, 0};

	cout << "\nUnit Test 9: void calculate_score(player& userPlayer)\n";

	// Case 9.1: Calculate normal scores
	cout << "\tCase 9.1: Calculate normal score\n";
	calculate_score(player1);

	assert(player1.score == 120);

	cout << "\tCase 9.1 Passed...\n";

	// Case 9.2: Calculate negative score (and fix it to 0)
	cout << "\tCase 9.2: Calculate negative score (and fix it to 0, no negatives please)\n";
	calculate_score(player2);

	assert(player2.score == 0);

	cout << "\tCase 9.2 Passed...\n";
}

void test_valid_int_input()
{
	// Initialize test fixtures
	int validatedInput;

	cout << "\nUnit Test 10: int valid_int_input(void)\n";
	
	// Case 10.1: Spits out whatever was entered
	cout << "\tCase 10.1: Enter anything and program will print what you entered (as interpreted by the game)\n";
	validatedInput = valid_int_input();

	cout << "\tYou entered: " << validatedInput << endl;
	cout << "\tCase 10.1 Passed...\n";
}

void test_view_character()
{
	// Initialize test fixtures
	player player1 = {"Caroline", 1, 5, 10, 3, 50};

	cout << "\nUnit Test 11: void view_character(player userPlayer)\n";

	// Case 11.1: Displays a character information <preset>
	cout << "\tCase 11.1: Displays a typical player info set\n";
	view_character(player1);
	cout << "\tCase 11.1 Passed...\n";
}

void test_read_paper()
{
	// Initialize test fixtures
	player player1 = {"Caroline", 1, 5, 10, 3, 0};
	int oldIntel = player1.intel;
	int oldTime = player1.time;
	
	cout << "\nUnit Test 12: void read_paper(player& userPlayer)\n";
	cout << "\nNOTE: if this function puts a player in GAME_OVER state, that's cause by a handler, NOT this function\n";
	
	// Case 12.1: player chose to read a paper, attributes modifed
	cout << "\tCase 12.1: Player reads a paper, attributes updated\n";
	read_paper(player1);

	assert(oldIntel < player1.intel);
	assert(oldTime > player1.time);

	cout << "\tCase 12.1 Passed...\n";
}

void test_search_change()
{
	// Initialize test fixtures
	player player1 = {"Caroline", 1, 5, 10, 5, 0};
	int oldMoney = player1.money;
	int oldTime = player1.time;
	
	cout << "\nUnit Test 13: void search_change(player& userPlayer)\n";

	// Case 13.1: player chose to search for change, attributes modified
	cout << "\tCase 13.1: Player looks for change, attributes updated\n";
	search_change(player1);

	assert(oldMoney < player1.money);
	assert(oldTime > player1.time);

	cout << "\tCase 13.1 Passed...\n";
}

void test_move_forward()
{
	// Initialize test fixtures
	player player1 = {"Caroline", 35, 30, 40, 6, 0};
	int oldSteps = player1.steps;
	int oldMoney = player1.money;
	int oldTime = player1.time;
	int oldIntel = player1.intel;

	encounterPtr encDynArray;
	init_encounters(encDynArray);

	puzzleHead puzzleList;
	create_puzzle_list(puzzleList);

	cout << "\nUnit Test 14: void move_forward(player& userPlayer, encounterPtr encArray, puzzleHead p_head)\n";

	// Case 14.1: Moves forward one step
	cout << "\tCase 14.1: Player moves forward one step each time. TEST REPEATS THREE TIMES\n";
	
	for (int i = 0; i < 3; i++)
	{
		move_forward(player1, encDynArray, puzzleList);
		// Since some encounters MAY leave steps the same, ALL attributes must be checked
		// At least one attribute is guranteed to change every time move is called
		assert(oldSteps != player1.steps || oldMoney != player1.money || oldTime != player1.time
				|| oldIntel != player1.intel);
		oldSteps = player1.steps;
		oldMoney = player1.money;
		oldTime = player1.time;
		oldIntel = player1.intel;
	}

	cout << "\tCase 14.1 (Probably) Passed...\n";
}

void test_generate_encounter_ID()
{
	// Initialize test fixtures
	int encID;

	cout << "\nUnit Test 15: int generate_encounter_ID(void)\n";

	// Case 15.1: Generate an encounter ID within the correct range
	cout << "\tCase 15.1: Generate valid encounter ID. TEST REPEATS THREE TIMES\n";

	for (int i = 0; i < 3; i++)
	{
		encID = generate_encounter_ID();
		assert(encID >= NUM_OF_ENCOUNTERS - NUM_OF_ENCOUNTERS && encID <= NUM_OF_ENCOUNTERS - 1); // range for encounter IDs
	}
	
	cout << "\tCase 15.1 Passed...\n";
}

void test_ask_puzzle()
{
	// Initialize test fixtures
	player player1 = {"Caroline", 35, 30, 40, 6, 0};
	int oldSteps = player1.steps;
	int oldMoney = player1.money;
	int oldTime = player1.time;
	int oldIntel = player1.intel;

	puzzleHead puzzleList;
	create_puzzle_list(puzzleList);
	
	cout << "\nUnit Test 16: void ask_puzzle(player& userPlayer, puzzleHead p_head)\n";
	
	// Case 16.1: Ask various puzzles and ensure they all modify player attributes
	cout << "\tCase 16.1: Ask various puzzles they should modify player attributes. TEST REPEATS THREE TIMES\n";

	for (int i = 0; i < 3; i++)
	{
		ask_puzzle(player1, puzzleList);
		assert(oldSteps != player1.steps || oldMoney != player1.money || oldTime != player1.time || oldIntel != player1.intel);

		// Update values with newly modified values
		oldSteps = player1.steps;
		oldMoney = player1.money;
		oldTime = player1.time;
		oldIntel = player1.intel;	
	}

	cout << "\tCase 16.1 Passed...\n";
}

void test_display_sys_menu()
{
	cout << "\nUnit Test 17: void display_sys_menu(void)\n";

	// Case 17.1: Just display menu
	cout << "\tCase 17.1: Display system menu. Tester: inspect to ensure correct menu\n";
	display_sys_menu();
	
	cout << "\tCase 17.1 Passed...\n";
}

void test_display_game_menu()
{
	cout << "\nUnit Test 18: void display_game_menu(void)\n";

	// Case 18.1: Display menu
	cout << "\tCase 18.1: Display game menu. Tester: inspect to ensure correct menu\n";
	display_game_menu();

	cout << "\tCase 18.1 Passed...\n";
}

#endif
