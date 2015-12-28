// Dragons - A simple text-based game
// Contains functions prototypes and data structs for the game menu 
// COMP2710 Project 1
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: project1_menu.h
// Written in Vi text editor
// Version: 4/13/2015, v1
// Sources used: C programming online tutorial website (to learn header files):
// 			<www.cprogramming.com>
// 		 Stack Overflow forums for info on header files

#ifndef PROJECT1_MENU_H
#define PROJECT1_MENU_H

#include "project1_system.h"
#include "project1_encounters.h"	// encounters and puzzle in Move forward
#include "project1_puzzle.h"

/***************************** CONSTANTS ***************************/
// Upper choice for menu (zero-indexed)
const u_short	GME_MENU_UPPER_CHOICE = 4;

/*************************** DATA STRUCTURES ***********************/
enum game_menu_t {MOVE, READ, SEARCH, VIEW_CHARACTER, QUIT_GAME};

/************************ FUNCTION PROTOTYPES **********************/
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
 * Displays the game menu
 * @return user's zero-indexed selection (VALIDATED FIRST)
 */
u_short display_game_menu(void);

#endif
