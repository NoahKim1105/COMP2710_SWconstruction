// Dragons - A simple text-based game
// Contains functions prototypes and data structs for scoreboard 
// COMP2710 Project 1
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: project1_scoreboard.h
// Written in Vi text editor
// Version: 4/13/2015, v1
// Sources used: C programming online tutorial website (to learn header files):
// 			<www.cprogramming.com>
// 		 Stack Overflow forums for info on header files

#ifndef PROJECT1_SCOREBOARD_H
#define PROJECT1_SCOREBOARD_H

#include<fstream>			// for file I/O
#include "project1_system.h"

/************************* CONSTANTS *************************/

// Default scoreboard file name input/output
const char	DEFAULT_SCOREBOARD_FILE[] = "scoreboard.txt";

/********************** DATA STRUCTURES *********************/

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

/******************* FUNCTION PROTOTYPES ********************/

/**
 * Function to display the scores stored in the scoreboard.
 * @param sBoard	head node of scoreboard list
 */
void view_scores(scoreHead sBoard);
/**
 * Function to load scores from a file.
 * NOTE: Assumes scores are sorted in file with HIGHEST first line
 * @param sBoard	head node of scoreboard list
 * @return		0 success
 * 			1 file I/O error
 * 			2 mem allocation error
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
 * @return		0 success
 * 			1 file I/O error
 */
u_short save_scores(scoreHead sBoard);
/**
 * Overloaded of last function, but allows user-provided filename.
 * @param sBoard	head node of scoreboard list
 * @param filename	char array of file's name
 * @return		0 success
 * 			1 file I/O error
 */
u_short save_scores(scoreHead sBoard, const char filename[]);
/**
 * Adds new score to list IF score is high enough to be on.
 * MUST keep list in sorted order!
 * Will also remove a score if adding new one makes list longer than max
 * @param sBoard	head node of scoreboard list
 * @param userScore	user's final score
 * @param userName	user's name to be added
 * @return		0 if added successfully
 * 			1 if not added to list
 * 			2 mem allocation error
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

#endif
