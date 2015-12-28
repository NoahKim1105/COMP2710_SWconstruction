// Dragons - A simple text-based game
// Contains functions prototypes and data structs for puzzles
// COMP2710 Project 1
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: project1_puzzle.h
// Written in Vi text editor
// Version: 4/13/2015, v1
// Sources used: C programming online tutorial website (to learn header files):
// 			<www.cprogramming.com>
// 		 Stack Overflow forums for info on header files

#ifndef PROJECT1_PUZZLE_H
#define PROJECT1_PUZZLE_H

#include "project1_system.h"

/************************** CONSTANTS **************************/
const u_short	NUM_OF_PUZZLES = 6;

/*********************** DATA STRUCTURES ***********************/

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

/******************** FUNCTION PROTOTYPES *********************/
/**
 * Initializes puzzle list to preset values
 * @param p_head	Points to puzzle list's head node
 */
void create_puzzle_list(puzzleHead& p_head);
/**
 * Asks the user a puzzle question. Depending on answer, will modify attributes accordingly.
 * @param userPlayer	user's character
 * @param p_head	points to head of puzzle list
 */
void ask_puzzle(player& userPlayer, puzzleHead p_head);

#endif
