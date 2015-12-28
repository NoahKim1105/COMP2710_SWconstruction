// Dragons - A simple text based game
// File contains function implementations for scoreboard 
// COMP2710 Project 1
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: project1_scoreboard.cpp
// Written in Vi text editor
// Version: 4/13/2015, v1
// Sources used: Dr. Qin's presentation of linked list operations

#include "project1_scoreboard.h"

// Displays socreboard to the user
void view_scores(scoreHead sBoard)
{
	// Initialize an iterator
	scoreNodePtr curr = sBoard.first;

	cout << "The top " << sBoard.numScores << " high scores are:\n";

	for (u_short i = 0; i < sBoard.numScores; i++) 
	{
		cout << (i + 1) << ". " << curr->name << ": " << curr->score << endl;
		curr = curr->next;

		// SAFETY
		if (curr == NULL) break;
	}

	// Termination line
	cout << "-No More Scores to Show-\n";
}

// Loads scores from the default file. Same as calling custom filename function with this filename
u_short load_scores(scoreHead& sBoard)
{
	return load_scores(sBoard, DEFAULT_SCOREBOARD_FILE);
}

// Loads scores from file. Will return non-zero if error occurs:
// @return	0 success
// 		1 file I/O error
// 		2 memory allocation error
u_short load_scores(scoreHead& sBoard, const char filename[])
{
	string tempName;
	int tempScore;
	scoreNodePtr curr, newNode;
	
	// Initialize input stream
	ifstream inStream;

	// Open file, return 1 if I/O error occurs
	inStream.open(filename);
	if (inStream.fail())
	{
		return 1;
	}

	inStream >> sBoard.numScores; // store number of scores (first line in file)

	newNode = new scoreNode;
	if (newNode == NULL) return 2;

	// Initialize first node in list
	if (inStream >> tempName && inStream >> tempScore)
	{
		newNode->name = tempName;
		newNode->score = tempScore;
		newNode->next = NULL;
		sBoard.first = newNode;
	}
	else
	{
		// List is EMPTY
		return 0;
	}

	curr = sBoard.first;

	// Continues until end of file reached
	while (inStream >> tempName)
	{
		// Check just to make sure end not reached...
		if (inStream >> tempScore)
		{
			newNode = new scoreNode;
			if (newNode == NULL) return 2;
	
			newNode->name = tempName;
			newNode->score = tempScore;
			newNode->next = NULL;
			curr->next = newNode;
			curr = curr->next;
		}
	}
	
	inStream.close();

	return 0;
}

// Saves scores to the default file
u_short save_scores(scoreHead sBoard)
{
	return save_scores(sBoard, DEFAULT_SCOREBOARD_FILE);
}

// Saves scores to a specified filename
// @return 	0 success
// 		1 file I/O error
u_short save_scores(scoreHead sBoard, const char filename[])
{
	// List iterator
	scoreNodePtr curr = sBoard.first;

	// Outstream
	ofstream outStream;

	outStream.open(filename);
	if (outStream.fail())
	{
		return 1;
	}

	// Write how many scores in board
	outStream << sBoard.numScores << endl;

	while (curr != NULL)
	{
		outStream << curr->name << endl << curr->score << endl;
		curr = curr->next;
	}

	outStream.close();

	return 0;
}

// Add a new score to the high score list IF it should be added
// @return	0 successfully added
// 		1 not added (probably due to 0 score OR not high enough)
// 		2 mem allocation erorr
u_short add_new_score(scoreHead& sBoard, int userScore, string userName)
{
	// Create iterators and new node ptr
	scoreNodePtr curr, pre, new_node;

	if (userScore <= 0)
	{
		// User score not able to be added, 0 or negative
		return 1;
	}

	// Initialize new node to be added
	new_node = new scoreNode;
	if (new_node == NULL) return 2;	// mem allocation error

	new_node->name = userName;
	new_node->score = userScore;
	new_node->next = NULL;

	// List is empty
	if (sBoard.first == NULL) 
	{
		sBoard.first = new_node;
	}
	// Else, add new node to appropiate position
	else
	{
		pre = NULL;
		curr = sBoard.first;
		
		while (curr != NULL && curr->score > userScore)
		{
			pre = curr;
			curr = curr->next;
		}
		
		// Curr holds position where new node should go, pre holds one before
		// If pre is null, insert at head of list
		if (pre == NULL)
		{
			new_node->next = sBoard.first;
			sBoard.first = new_node;
		}
		// Else, in middle of list
		else
		{
			new_node->next = curr;
			pre->next = new_node;
		}
	}

	sBoard.numScores++;

	// Check if limit of high scores exceeded because of this
	if (sBoard.numScores > MAX_NUM_OF_HIGH_SCORES)
	{
		// Delete the last node of the list
		delete_score_tail(sBoard);
		// If curr is NULL, then the new score was added to END of list, which was just deleted
		// by the last function. THEREFORE, the user's score was NOT added.
		if (curr == NULL) return 1;
	}

	return 0;
}

// Deletes the tail node in a scoreboard.
// @return	0 successful delete
// 		1 unsuccessful delete
u_short delete_score_tail(scoreHead& sBoard)
{
	// Initialize iterator
	scoreNodePtr curr, pre;
	
	// List is empty? Don't delete
	if (sBoard.first == NULL)
	{
		return 1;
	}

	// If list only has one node...
	if (sBoard.first->next == NULL)
	{
		delete sBoard.first;
		sBoard.first = NULL;
		sBoard.numScores--;
		return 0;
	}
	
	// List has more than one node
	pre = sBoard.first;
	curr = sBoard.first->next;
	// Iterate through list until end node is reached
	while (curr->next != NULL)
	{
		pre = curr;
		curr = curr->next;
	}

	pre->next = NULL;
	delete curr;
	sBoard.numScores--;

	return 0;	
}

// Calculate the player's score and stores it in the structure.
// If result is negative, will store 0 instead
// Also returns the calculated score
// @return user's calculated score
u_int calculate_score(player& userPlayer)
{
	// Variables
	int calculatedScore;
	
	// Score is all three attributes multiplied together
	calculatedScore = userPlayer.money * userPlayer.intel * userPlayer.time;

	// If score is negative, set it to 0
	if (calculatedScore < 0)
	{
		calculatedScore = 0;
	}

	userPlayer.score = calculatedScore;
	
	return userPlayer.score;
}
