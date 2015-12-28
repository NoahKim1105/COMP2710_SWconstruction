// Dragons - A simple text-based game
// Contains functions prototypes and data structs for the system 
// COMP2710 Project 1
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: project1_system.h
// Written in Vi text editor
// Version: 4/13/2015, v1
// Sources used: Dr. Qin's source for dragons_datastructures_new_design.cpp
// 		 C programming online tutorial website (to learn header files):
// 			<www.cprogramming.com>
// 		 Stack Overflow forums for info on header files

#ifndef PROJECT1_SYSTEM_H
#define PROJECT1_SYSTEM_H

#include<iostream>		// all other headers need iostream and string
#include<string>
#include<cstdlib>		// also uses rand() a lot

using namespace std;		// ALL functions use std namespace 

typedef unsigned short u_short;
typedef unsigned int u_int;

/**************************** CONSTANTS ************************/

// Bounds for initial attributes
const u_short	ATTRIBUTE_LOWER_BOUND = 20;
const u_short	ATTRIBUTE_UPPER_BOUND = 35;
const u_short	TIME_LOWER_BOUND = 30;
const u_short	TIME_UPPER_BOUND = 40;
const u_short	INITIAL_STEPS_FROM_GOAL = 20;

// Specifiy maximums for data sctructures below ( = 2 * (num of player attributes))
const u_short	MAX_NUM_ACTION = 8;

// Upper limits for menu options (ZERO-BASED indexing)
const u_short	SYS_MENU_UPPER_CHOICE = 2;

// Scoreboard contains max amount of scores
const u_short	MAX_NUM_OF_HIGH_SCORES = 10;

// Easter egg event trigger: this is the number the USER has to enter to activate it
const int	EASTER_EGG_TRIGGER = 555;


/************************* DATA STRUCTURES ********************/

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

enum system_menu_t {START_GAME, VIEW_SCORES, QUIT_PGM};

/********************* FUNCTION PROTOTYPES ********************/
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
 * Displays the system menu
 * @return user's zero-indexed selection (VALIDATED FIRST)
 */
u_short display_sys_menu(void);
/**
 * Asks user for numeric input and ensures only a valid number is returned (nonnegative)
 * @return		User entered integer
 */
u_short valid_int_input(void);
/**
 * Given an action data struct, modifies the player appropiately
 * ALSO: Displays info to user as edits are made
 * @param userPlayer	user's character
 * @param actionTake	the action data to take towards player
 */
void point_handler(player& userPlayer, action actionToTake);

#endif
