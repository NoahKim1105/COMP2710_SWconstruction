// Dragons - A simple text based game 
// File contains the test drivers with its own main executable
// COMP2710 Project 1
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: project1_test.cpp
// Written in Vi text editor
// Version: 4/13/2015, v1

#include "project1_test.h"

int main()
{
	// Initialize random number generator
	srand(time(NULL));

	// Unit testing cases
	test_login_process();
	test_init_character();
	test_create_puzzle_list();
	test_init_encounters();
	test_view_scores();
	test_load_scores();
	test_save_scores();
	test_add_new_score();
	test_delete_score_tail();
	test_calculate_score();
	test_valid_int_input();
	test_view_character();
	test_read_paper();
	test_search_change();
	test_move_forward();
	test_generate_encounter_ID();
	test_ask_puzzle();
	test_display_sys_menu();
	test_display_game_menu();

	return 0;
}

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
	assert(player1.score == player1.money * player1.time * player1.intel);				// equal to whatever is set in character data

	cout << "\tCase 2.1 Passed...\n";
}

void test_create_puzzle_list()
{
	// Initialize test fixtures
	puzzleHead puzzle1;	
	puzzleNodePtr currentNode;

	string question1 = "What does 2 + 2 = ? ... IN BASE 4?\n1. 0\n2. 4\n3. 10\n4. 16\n5. REALLY? MATH? At a time like THIS?!\n";
	u_short answer1 = 3;
	string question2 = "What do you do when life gives you lemons (according to Aperture Science)?\n1. Make lemonade\n2. Do what Cave Johnson said and make combustible lemons to burn people's houses down\n3. Go to Food Network and become the next Food Network Star...that really likes lemons\n";
	u_short answer2 = 2;
	string question3 = "Get this question right and WIN A TIME DILATION DEVICE! A popular protocol for communication between many digital electronics and microcontrollers in embedded systems is?\n1. PDI\n2. JTAG\n3. I2C\n4. IDC\n5. IDK\n";
	u_short answer3 = 3;
	string question4 = "WIN BIG BUCKS! The many islands of the State of Hawai'i include Hawai'i (Da Big Island), Oahu, Kauai, Lanai, and what other island?\n1. Maui\n2. Guam\n3. Puerto Rico\n4. Honolulu\n5. Da United States is one island yeah?";
	u_short answer4 = 1;
	string question5 = "Take a LEAP forward if you win this one... Who is the most evilest, rage-inducing, OVERALL BADDEST, League of Legends champion ever?\n1. Sona\n2. The cute and cuddly Teemo\n3. URF the manatee\n4. Nocturne\n5. Really? LoL? Who plays that...\n ";
	u_short answer5 = 2;
	string question6 = "The Holy Overlord Urf the Manatee appears and decides to be nice to you, but first you answer his question: What does his name truly mean?\n1. Unruly Rascals Federation\n2. Unsubmerged Reptile of Fire\n3. Ultra Rapid Fire\n4. Used RAM for Free\n";
	u_short answer6 = 3;
	
	action nullAction = {REWARD, MONEY, 0};	// a "NULL" action, just for filler in 2D array

	u_short numOfActions1 = 6;
	u_short numOfActions2 = 6;
	u_short numOfActions3 = 4;
	u_short numOfActions4 = 6;
	u_short numOfActions5 = 4;
	u_short numOfActions6 = 8;

	// Create arrays to allow iteration over all elements cleaner to perform tests
	string questionArray[] = {question1, question2, question3, question4, question5, question6};
	u_short answerArray[] = {answer1, answer2, answer3, answer4, answer5, answer6};
	// Individual action arrays for each event. Unfortunately, couldn't make it any cleaner...
	action actionArrays[6][8] = {{{REWARD, MONEY, 10}, {PENALTY, MONEY, -10}, {REWARD, TIME, -1}, {PENALTY, TIME, -2}, {REWARD, STEPS, -1}, {PENALTY, STEPS, -1},
	/** PUZZLE1 */			nullAction, nullAction},
	/** PUZZLE2 */		     {{REWARD, INTEL, 5}, {PENALTY, MONEY, -5}, {REWARD, TIME, -1}, {PENALTY, TIME, -1}, {REWARD, STEPS, -1}, {PENALTY, STEPS, 0},
					nullAction, nullAction},
	/** PUZZLE3 */		     {{REWARD, TIME, 5}, {PENALTY, TIME, -5}, {REWARD, STEPS, -1}, {PENALTY, STEPS, -1}, nullAction, nullAction, nullAction, nullAction},
	/** PUZZLE4 */		     {{REWARD, MONEY, 10}, {PENALTY, INTEL, -10}, {REWARD, TIME, -1}, {PENALTY, TIME, -1}, {REWARD, STEPS, -1}, {PENALTY, STEPS, -1},
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
	
	string message1 = "OH MY GOSH, NOTHING HAPPENS...\n";
	string message2 = "It's puzzle time!\n";
	string message3 = "You see a tall shadowy figure approach you...\n";
	string message4 = "You see a short figure approach you...\n";
	string message5 = "A small elfish figure hops towards you with something in his hand...\n";
	string message6 = "A flying box of papers approaches your position!\n";

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
	action actionArrays[6][3] = {{{REWARD, STEPS, -1}, {PENALTY, TIME, -1}, nullAction},		// NOTHING
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

void test_load_scores()
{
	// Initialize test fixtures
	char filename1[] = "scoreboardTESTread.txt";
	char filenameDNE[] = "IreallyHopeYoudonthaveThisfileforREALS.txt";
	scoreHead sBoard;	
	scoreHead sBoardDNE;

	cout << "\nUnit Test 6: u_short load_scores(scoreHead& sBoard, const char filename[])\n";

	// Case 6.1: load scores from a file that doesn't exist
	cout << "\tCase 6.1: Attempt to load scores from a file that doesn't exist\n";
	int errorCode = load_scores(sBoardDNE, filenameDNE);

	assert(errorCode != 0);

	cout << "\tCase 6.1 Passed...\n";

	// Case 6.2: load scores from a real file
	cout << "\tCase 6.2: Attempt to load scores from a real file scoreboardTESTread.txt\n";
	errorCode = load_scores(sBoard, filename1);

	assert(errorCode == 0);
	assert(sBoard.numScores == 2);
	assert(sBoard.first->name == "GLaDOS");
	assert(sBoard.first->score == 9001);
	assert(sBoard.first->next->name == "Chell");
	assert(sBoard.first->next->score == 102);
	assert(sBoard.first->next->next == NULL);

	cout << "\tCase 6.2 Passed...\n";
}

void test_save_scores()
{
	// Initialize test fixtures
	char filename1[] = "scoreboardTESTwrite.txt";
	scoreHead sBoard = {3, new scoreNode};
	sBoard.first->name = "GLaDOS";
	sBoard.first->score = 9001;
	sBoard.first->next = new scoreNode;
	sBoard.first->next->name = "Chell";
	sBoard.first->next->score = 10;
	sBoard.first->next->next = new scoreNode; 
	sBoard.first->next->next->name = "Mark";
	sBoard.first->next->next->score = 5;
	sBoard.first->next->next->next = NULL;

	cout << "\nUnit Test 7: u_short save_scores(scoreHead sBoard, const char filename[])\n";

	// Case 7.1: write scores to file
	cout << "\tCase 7.1: Save scores to a file called scoreboardTESTwrite.txt\n";
	int errorCode = save_scores(sBoard, filename1);

	assert(errorCode == 0);
	
	cout << "\tCase 7.1 Passed...\n";
}

void test_add_new_score()
{
	// Initialize test fixtures
	int userScore1 = 5;
	int userScore2 = 3;
	int userScore3 = 9002;
	int userScore4 = 5000;
	int userScore5 = 0;
	u_short errorCode;

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

	cout << "\nUnit Test 8: u_short add_new_score(scoreHead& sBoard, int userScore, string userName)\n";

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

	assert(errorCode == 1);

	cout << "\tCase 8.5 Passed...\n";
	
	// Case 8.6: Attempt to add a new score to the END of the list, when list is at MAX
	// First, add 5 more scores to fill up the list (at this point, normal functionality of add_new_score
	// already tested)
	add_new_score(sBoard, 500, "TEST");
	add_new_score(sBoard, 540, "TEST1");
	add_new_score(sBoard, 324, "TEST2");
	add_new_score(sBoard, 132, "TEST3");
	add_new_score(sBoard, 1008, "TEST4");

	cout << "\tCase 8.6: Attempt to add score to end of list when list is full\n";
	errorCode = add_new_score(sBoard, 1, "NOOB");

	assert(errorCode == 1);
	assert(sBoard.numScores == 10);

	// Get current node to the end of the list
	while (currentNode->next != NULL)
	{
		currentNode = currentNode->next;
	}
	
	assert(currentNode->name == name1);
	assert(currentNode->score == userScore2);
	assert(currentNode->next == NULL);
	
	cout << "\tCase 8.6 Passed...\n";

	// Case 8.7: Add new score in middle of a full list
	cout << "\tCase 8.7: Add new score in the middle of a full list\n";
	errorCode = add_new_score(sBoard, 530, "NOOBish");

	assert(errorCode == 0);
	assert(sBoard.numScores == 10);

	currentNode = sBoard.first->next->next->next->next->next;

	assert(currentNode->name == "NOOBish");
	assert(currentNode->score == 530);
	assert(currentNode->next->name == "TEST");

	cout << "\tCase 8.7 Passed...\n";
}

void test_delete_score_tail()
{
	// Initialize test fixtures
	u_short errorCode;	

	scoreHead emptySboard = {0, NULL};
	scoreHead sBoard = {2, new scoreNode};
	sBoard.first->name = "GLaDOS";
	sBoard.first->score = 9001;
	sBoard.first->next = new scoreNode;
	sBoard.first->next->name = "Chell";
	sBoard.first->next->score = 10;
	sBoard.first->next->next = NULL; 
	
	cout << "\nUnit Test 9: u_short delete_score_tail(scoreHead& sBoard)\n";

	// Case 9.1: Delete the end of a list with items in it
	cout << "\tCase 9.1: Delete tail of list with elements in it\n";
	errorCode = delete_score_tail(sBoard);

	assert(errorCode == 0);
	assert(sBoard.numScores == 1);
	assert(sBoard.first->name == "GLaDOS");
	assert(sBoard.first->score == 9001);
	assert(sBoard.first->next == NULL);

	cout << "\tCase 9.1 Passed...\n";

	// Case 9.2: Delete the node in a list with only 1 node
	cout << "\tCase 9.2: Delete the only node left in a list (Single-element list)\n";
	errorCode = delete_score_tail(sBoard);

	assert(errorCode == 0);
	assert(sBoard.numScores == 0);
	assert(sBoard.first == NULL);
	
	cout << "\tCase 9.2 Passed...\n";

	// Case 9.3: Attempt to delete an empty list
	cout << "\tCase 9.3: Attempt to delete an empty list\n";
	errorCode = delete_score_tail(emptySboard);

	assert(errorCode == 1);
	assert(emptySboard.numScores == 0);
	assert(emptySboard.first == NULL);

	cout << "\tCase 9.3 Passed...\n";
}

void test_calculate_score()
{
	// Initialize test fixtures
	player player1 = {"Don't need a name", 10, 2, 6, 0, 0}; 
	player player2 = {"HOW DID YOU?", 10, -1, 4, 0, 0};

	cout << "\nUnit Test 10: void calculate_score(player& userPlayer)\n";

	// Case 10.1: Calculate normal scores
	cout << "\tCase 10.1: Calculate normal score\n";
	calculate_score(player1);

	assert(player1.score == 120);

	cout << "\tCase 10.1 Passed...\n";

	// Case 10.2: Calculate negative score (and fix it to 0)
	cout << "\tCase 10.2: Calculate negative score (and fix it to 0, no negatives please)\n";
	calculate_score(player2);

	assert(player2.score == 0);

	cout << "\tCase 10.2 Passed...\n";
}

void test_valid_int_input()
{
	// Initialize test fixtures
	int validatedInput;

	cout << "\nUnit Test 11: u_short valid_int_input(void)\n";
	
	// Case 11.1: Spits out whatever was entered
	cout << "\tCase 11.1: Enter anything and program will print what you entered (as interpreted by the game)\n";
	validatedInput = valid_int_input();

	cout << "\tYou entered: " << validatedInput << endl;
	cout << "\tCase 11.1 Passed...\n";
}

void test_view_character()
{
	// Initialize test fixtures
	player player1 = {"Caroline", 1, 5, 10, 3, 50};

	cout << "\nUnit Test 12: void view_character(player userPlayer)\n";

	// Case 12.1: Displays a character information <preset>
	cout << "\tCase 12.1: Displays a typical player info set\n";
	view_character(player1);
	cout << "\tCase 12.1 Passed...\n";
}

void test_read_paper()
{
	// Initialize test fixtures
	player player1 = {"Caroline", 1, 5, 10, 3, 0};
	int oldIntel = player1.intel;
	int oldTime = player1.time;
	
	cout << "\nUnit Test 13: void read_paper(player& userPlayer)\n";
	
	// Case 13.1: player chose to read a paper, attributes modifed
	cout << "\tCase 13.1: Player reads a paper, attributes updated\n";
	read_paper(player1);

	assert(oldIntel < player1.intel);
	assert(oldTime > player1.time);

	cout << "\tCase 13.1 Passed...\n";
}

void test_search_change()
{
	// Initialize test fixtures
	player player1 = {"Caroline", 1, 5, 10, 5, 0};
	int oldMoney = player1.money;
	int oldTime = player1.time;
	
	cout << "\nUnit Test 14: void search_change(player& userPlayer)\n";

	// Case 14.1: player chose to search for change, attributes modified
	cout << "\tCase 14.1: Player looks for change, attributes updated\n";
	search_change(player1);

	assert(oldMoney < player1.money);
	assert(oldTime > player1.time);

	cout << "\tCase 14.1 Passed...\n";
}

// Test move_forward AS WELL AS all of the encounter functions attached to moving forward
// (EXCEPT for puzzles, that is tested by its own function)
void test_move_forward()
{
	// Initialize test fixtures
	// Set player to high initial values to prevent NEGATIVES from occuring
	player player1 = {"Caroline", 100, 100, 100, 100, 0};
	int oldSteps = player1.steps;
	int oldMoney = player1.money;
	int oldTime = player1.time;
	int oldIntel = player1.intel;

	encounterPtr encArray;
	init_encounters(encArray);

	puzzleHead puzzleList;
	create_puzzle_list(puzzleList);

	cout << "\nUnit Test 15: void move_forward(player& userPlayer, encounterPtr encArray, puzzleHead p_head)\n";

	// Case 15.1: Test NOTHING happens encounter
	cout << "\tCase 15.1: Nothing happens encounter, moves forward 1\n";
	move_forward(player1, encArray[NOTHING]);

	assert(player1.money == oldMoney);
	assert(player1.time == oldTime - 1);
	assert(player1.intel == oldIntel);
	assert(player1.steps = oldSteps - 1);

	cout << "\tCase 15.1 Passed...\n";

	// Set the 'old' stats to what was just modified
	oldTime = player1.time;
	oldSteps = player1.steps;

	// Case 15.2: Test PUZZLE encounter

	cout << "\tCase 15.2: Puzzle encounter, a puzzle should appear. Answer correctly or wrong, does not matter\n";
	move_forward(player1, encArray[PUZZLE], puzzleList);

	// ANY of the stats could've changed, assert that if any stat changed, proram worked
	assert(player1.money != oldMoney || player1.time != oldTime || player1.intel != oldIntel || player1.steps != oldSteps);

	cout << "\tCase 15.2 Passed...\n";

	// Set the old stats to what was just modified
	oldMoney = player1.money;
	oldTime = player1.time;
	oldIntel = player1.intel;
	oldSteps = player1.steps;

	// Case 15.3: Test PROFESSOR encounter
	
	cout << "\tCase 15.3: Professor encounter, a professor will appear and modifiy stats randomly\n";
	move_forward(player1, encArray[PROFESSOR]);

	assert(player1.money == oldMoney);
	assert(player1.time < oldTime);
	assert(player1.intel >= oldIntel);
	assert(player1.steps == oldSteps - 1);

	cout << "\tCase 15.3 Passed...\n";

	// Set the old stats to what was just modified
	oldTime = player1.time;
	oldIntel = player1.intel;
	oldSteps = player1.steps;

	// Case 15.4: Test STUDENT encounter
	
	cout << "\tCase 15.4: Grad student encounter, only time will be lost\n";
	move_forward(player1, encArray[STUDENT]);

	assert(player1.money == oldMoney);
	assert(player1.time < oldTime);
	assert(player1.intel == oldIntel);
	assert(player1.steps == oldSteps - 1);

	cout << "\tCase 15.4 Passed...\n";

	// Set the old stats to what was just modified
	oldTime = player1.time;
	oldSteps = player1.steps;

	// Case 15.5: Test GRUNT encounter
	
	cout << "\tCase 15.5: Grunt work encounter, loses intel and time\n";
	move_forward(player1, encArray[GRUNT]);

	assert(player1.money == oldMoney);
	assert(player1.time < oldTime);
	assert(player1.intel < oldIntel);
	assert(player1.steps == oldSteps - 1);

	cout << "\tCase 15.5 Passed...\n";

	// Set the old stats to what was just modified
	oldTime = player1.time;
	oldIntel = player1.intel;
	oldSteps = player1.steps;

	//Case 15.6: Test PAPER encounter
	
	cout << "\tCase 15.6: Grade papers encounter, gain money but lose time\n";
	move_forward(player1, encArray[PAPER]);
	
	assert(player1.money > oldMoney);
	assert(player1.time < oldTime);
	assert(player1.intel == oldIntel);
	assert(player1.steps == oldSteps - 1);

	cout << "\tCase 15.6 Passed...\n";
}

void test_generate_encounter_ID()
{
	// Initialize test fixtures
	int encID;

	cout << "\nUnit Test 16: u_short generate_encounter_ID(void)\n";

	// Case 16.1: Generate an encounter ID within the correct range
	cout << "\tCase 16.1: Generate valid encounter ID. TEST REPEATS TEN TIMES. Each ID is printed\n";

	for (int i = 0; i < 10; i++)
	{
		encID = generate_encounter_ID();
		cout << "ID Generated: " << encID << endl;
		assert(encID >= NUM_OF_ENCOUNTERS - NUM_OF_ENCOUNTERS && encID <= NUM_OF_ENCOUNTERS - 1); // range for encounter IDs
	}
	
	cout << "\tCase 16.1 Passed...\n";
}

void test_ask_puzzle()
{
	// Initialize test fixtures
	player player1 = {"Caroline", 100, 100, 100, 100, 0};
	int oldSteps = player1.steps;
	int oldMoney = player1.money;
	int oldTime = player1.time;
	int oldIntel = player1.intel;

	puzzleHead puzzleList;
	create_puzzle_list(puzzleList);
	
	cout << "\nUnit Test 17: void ask_puzzle(player& userPlayer, puzzleHead p_head)\n";
	
	// Case 17.1: Ask various puzzles and ensure they all modify player attributes
	cout << "\tCase 17.1: Ask various puzzles they should modify player attributes. TEST REPEATS THREE TIMES\n";

	for (int i = 0; i < 3; i++)
	{
		ask_puzzle(player1, puzzleList);
		assert(oldSteps != player1.steps || oldMoney != player1.money || oldTime != player1.time || oldIntel != player1.intel);

		// Update values with newly modified values
		oldSteps = player1.steps;
		oldMoney = player1.money;
		oldTime = player1.time;
		oldIntel = player1.intel;	
		
		cout << endl;
	}

	cout << "\tCase 17.1 Passed...\n";
}

void test_display_sys_menu()
{
	// Initialize test fixtures
	u_short userChoice;

	cout << "\nUnit Test 18: u_short display_sys_menu(void)\n";

	// Case 18.1: Just display menu
	cout << "\tCase 18.1: Display system menu and get user's VALID choice, will repeat until choice is valid\n";
	userChoice = display_sys_menu();

	assert(userChoice >= 0 && userChoice <= 2);
	
	cout << "\tCase 18.1 Passed...\n";
}

void test_display_game_menu()
{
	// Initialize test fixtures
	u_short userChoice;

	cout << "\nUnit Test 19: u_short display_game_menu(void)\n";

	// Case 19.1: Display menu
	cout << "\tCase 19.1: Display game menu and get user's VALID choice, will repeat until choice is valid\n";
	userChoice = display_game_menu();

	assert((userChoice >= 0 && userChoice <= 4) || userChoice == EASTER_EGG_TRIGGER - 1);

	cout << "\tCase 19.1 Passed...\n";
}
