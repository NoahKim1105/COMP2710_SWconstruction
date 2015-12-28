// Header file contains all data structure definitions,
// enumerated types, and function prototypes. 
// COMP2710 Project 1
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: project1_functions.h
// Written in Vi text editor
// Version: 4/11/2015, v1
// Sources used: Dr. Qin's source for dragons_datastructures_new_design.cpp
// 		 C programming online tutorial website (to learn header files):
// 			<www.cprogramming.com>
// 		 Stack Overflow forums for info on header files

#ifndef PROJECT1_FUNCTIONS_H
#define PROJECT1_FUNCTIONS_H

#include<string>

// Trying to not bring in EVERYTHING from using namespace std, instead only what is needed
// Read on forum that typically header files shouldn't use "using namespace std", but only what is needed
using std::string;

typedef unsigned short u_short;
typedef unsigned int u_int;

/**************************** GLOBAL CONSTANTS *******************************/
// Define constants to make code more maintainable

// Bounds for initial attributes
const u_short	ATTRIBUTE_LOWER_BOUND = 20;
const u_short	ATTRIBUTE_UPPER_BOUND = 35;
const u_short	TIME_LOWER_BOUND = 30;
const u_short	TIME_UPPER_BOUND = 40;
const u_short	INITIAL_STEPS_FROM_GOAL = 20;

// Specify amount of puzzles and encounters for presets
const u_short	NUM_OF_PUZZLES = 6;
const u_short	NUM_OF_ENCOUNTERS = 6;

// Bounds for points encounters can take away or add (random within bounds)
const short 	ENCOUNTER_POINT_LOWER_BOUND = -5;
const u_short	ENCOUNTER_POINT_UPPER_BOUND = 5;

// Scoreboard contains max amount of scores
const u_short	MAX_NUM_OF_HIGH_SCORES = 10;

// Default scoreboard file name input/output
const char	DEFAULT_SCOREBOARD_FILE[] = "scoreboard.txt";

// Specifiy maximums for data sctructures below
const u_short	MAX_NUM_ACTION = 8;

// Upper limits for menu options (ZERO-BASED indexing)
const u_short	SYS_MENU_UPPER_CHOICE = 2;
const u_short	GME_MENU_UPPER_CHOICE = 4;

// Easter egg event trigger: this is the number the USER has to enter to activate it
const int	EASTER_EGG_TRIGGER = 555;

/***************************** DATA STRUCTURES *******************************/

// Score board structures, one for nodes and one for head
struct scoreNode {
	string name;	// Holds name of user with high score
	u_int score;	// Holds the score
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
	u_int score; 	// Stores player's calculated score
};

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
	u_short answer;
	
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


/*************************** FUNCTION PROTOTYPES *****************************/

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
u_short load_scores(scoreHead& sBoard);
/**
 * Overloaded of last function, but allows user-provided filename.
 * @param sBoard	head node of scoreboard list
 * @param filename	char array of file's name
 * @return 		0 success
 * 			1 file I/O error
 * 			2 mem allocation error
 */
u_short load_scores(scoreHead& sBoard, const char filename[]);
/**
 * Function to save scoreboard to a file.
 * @param sBoard	head node of scoreboard list
 * @return		error code, not zero if error occurs
 */
u_short save_scores(scoreHead sBoard);
/**
 * Overloaded of last function, but allows user-provided filename.
 * @param sBoard	head node of scoreboard list
 * @param filename	char array of file's name
 * @return		error code, not zero if error occurs
 */
u_short save_scores(scoreHead sBoard, const char filename[]);
/**
 * Adds new score to list IF score is high enough to be on.
 * MUST keep list in sorted order!
 * Will also remove a score if adding new one makes list longer than max
 * @param sBoard	head node of scoreboard list
 * @param userScore	user's final score
 * @param userName	user's name to be added
 * @return		0 if added successfully, 1 if not
 */
u_short add_new_score(scoreHead& sBoard, int userScore, string userName);
/**
 * Deletes the tail of the scoreboard list. Used when list exceeds allowable high scores
 * @param sBoard	head node of scoreboard list
 * @return error code	0 success
 * 			1 failed (probably an empty list)
 */
u_short delete_score_tail(scoreHead& sBoard);
/**
 * Calculates player's score and stores it in player's structure and returns it
 * @param userPlayer	user's character at end of game
 * @return the user's calculated score
 */
u_int calculate_score(player& userPlayer);

// Function for handling user input
/**
 * Asks user for numeric input and ensures only a valid number is returned (nonnegative)
 * @return		User entered integer
 */
u_short valid_int_input(void);

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
 * Moves forward one. Encounter generated must be passed to function 
 * Handles encounters (but NOT puzzles) itself. If is puzzle, calls that function. 
 * @param userPlayer	user's character
 * @param encSelected	the encounter selected from the encArray[encID]
 * @param p_head	root of puzzle linked list, needed if encounter is puzzle
 */
void move_forward(player& userPlayer, encounter encSelected);
void move_forward(player& userPlayer, encounter encSelected, puzzleHead p_head);
/**
 * Generates a random (valid) encounter ID.
 * @return integer within range for a valid encounter ID.
 */
u_short generate_encounter_ID(void);
/**
 * Handles the PROFESSOR encounter
 * @param userPlayer	user's character
 * @param profEnc	encounter corresponding to professor attributes
 */
void professor_enc(player& userPlayer, encounter profEnc);
/**
 * Handles the STUDENT encounter
 * @param userPlayer	user's character
 * @param studEnc	encounter corresponding to student attributes
 */
void student_enc(player& userPlayer, encounter studEnc);
/**
 * Handles the GRUNT encounter
 * @param userPlayer	user's character
 * @param gruntEnc	encounter corresponding to grunt work attributes
 */
void grunt_enc(player& userPlayer, encounter gruntEnc);
/**
 * Handls the PAPER encounter
 * @param userPlayer	user's character
 * @param papEnc	encounter corresponding to grade paper attributes
 */
void paper_enc(player& userPlayer, encounter papEnc);

// Functions to handle puzzles
/**
 * Asks the user a puzzle question. Depending on answer, will modify attributes accordingly.
 * @param userPlayer	user's character
 * @param p_head	points to head of puzzle list
 */
void ask_puzzle(player& userPlayer, puzzleHead p_head);

// Functions to display menus and return user selection to main
/**
 * Displays the system menu
 * @return user's zero-indexed selection (VALIDATED FIRST)
 */
u_short display_sys_menu(void);
/**
 * Displays the game menu
 * @return user's zero-indexed selection (VALIDATED FIRST)
 */
u_short display_game_menu(void);

// Point handler
/**
 * Given an action data struct, modifies the player appropiately
 * ALSO: Displays info to user as edits are made
 * @param userPlayer	user's character
 * @param actionTake	the action data to take towards player
 */
void point_handler(player& userPlayer, action actionToTake);

#ifdef UNIT_TESTING
// Unit Testing Prototypes
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
void test_delete_score_tail(void);
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

#endif
