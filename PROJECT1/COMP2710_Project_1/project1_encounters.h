// Dragons - A simple text-based game
// Contains functions prototypes and data structs for encounters 
// COMP2710 Project 1
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: project1_encounters.h
// Written in Vi text editor
// Version: 4/13/2015, v1
// Sources used: Dr. Qin's source for dragons_datastructures_new_design.cpp
// 		 C programming online tutorial website (to learn header files):
// 			<www.cprogramming.com>
// 		 Stack Overflow forums for info on header files

#ifndef PROJECT1_ENCOUNTERS_H
#define PROJECT1_ENCOUNTERS_H

#include "project1_system.h"

/*************************** CONSTANTS *************************/
const u_short	NUM_OF_ENCOUNTERS = 6;

// Bounds for points encounters can take away or add (random within bounds)
const short 	ENCOUNTER_POINT_LOWER_BOUND = -5;
const u_short	ENCOUNTER_POINT_UPPER_BOUND = 5;

/********************** DATA STRUCTURES ************************/
enum encounter_t {NOTHING, PUZZLE, PROFESSOR, STUDENT, GRUNT, PAPER};

// Design structure similarly to puzzle data structures
// IMPLEMENTATION: Utilize a dynamic (or static) array of encounter type
struct encounter {
	encounter_t enctType;
	string message;	

	// Action to take:
	action actionArray[MAX_NUM_ACTION];
	u_short numOfActions;
};

// Typedef to set type of dynamic array
typedef encounter* encounterPtr;

/******************** FUNCTION PROTOTYPES ***********************/
/**
 * Initializes encounter array to preset values
 * @param encArray	Pointer to first element in array
 */
void init_encounters(encounterPtr& encArray);
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
 * Handles the PAPER encounter
 * @param userPlayer	user's character
 * @param papEnc	encounter corresponding to grade paper attributes
 */
void paper_enc(player& userPlayer, encounter papEnc);

#endif
