// Dragons - A simple text-based game
// Contains functions prototypes for test drivers
// COMP2710 Project 1
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: project1_test.h
// Written in Vi text editor
// Version: 4/13/2015, v1
// Sources used: C programming online tutorial website (to learn header files):
// 			<www.cprogramming.com>
// 		 Stack Overflow forums for info on header files

#ifndef PROJECT1_TEST_H
#define PROJECT1_TEST_H

// Required functions to run full suite of unit tests
#include<assert.h>
#include "project1_menu.h"
#include "project1_scoreboard.h"
#include "project1_puzzle.h"
#include "project1_encounters.h"

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
