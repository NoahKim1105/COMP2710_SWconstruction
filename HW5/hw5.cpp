// Trivia quiz program - asks user questions and awards points
// for right answers. 
// COMP2710 Homework 5
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: hw5.cpp
// Written in Vi text editor, compiled with g++ -o hw5 hw5.cpp
// Version: 3/7/2015, v1
// Sources used: Dr. Qin's source for linked list and multiple versions
// 		 C++ Reference for using getline(cin, var) to obtain strings
// 		 	with spaces in them
// 		 C++ forum to use cin.get() to prevent capture of '\n' char
// 		 	in reading ints from cin

#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <string>
using namespace std;

// Comment this line to enable production version of code!
#define UNIT_TESTING

// Define TriviaNode structures
struct TriviaNode
{
	string question;
	string answer;
	int pointValue;
	TriviaNode *next;
};
struct TriviaHead
{
	int totalQuestions;
	int userPointsEarned; // Store how many points user earned
	TriviaNode *head;
};

// Create typedef for TriviaNode pointers
typedef TriviaNode* TriviaNodePtr;

/*** Function prototypes ***/
/**
 * Initializes the linked list "Trivia" to have three pre-defined 
 * trivia questions.
 */
void hardCodedTriviaList(TriviaHead& Trivia);
/**
 * Adds a new question to the linked list by adding another
 * TriviaNode to the END of the list
 */
void addNewQuestion(TriviaHead& Trivia, string newQuestion, string newAnswer, int newPointValue);
/**
 * Asks the user a number of questions from the list and awards points if user
 * is correct, else, shows correct answer and awards no points.
 * Returns 0 if user was successful at providing an answer
 */
int askUserQuestion(TriviaHead& Trivia, int numOfQuestions);

#ifdef UNIT_TESTING
	void test_hardCodedTriviaList(void);
	void test_addNewQuestion(void);
	void test_askUserQuestion(void);
#endif

int main()
{
// Insert Unit Testing code here
#ifdef UNIT_TESTING
	cout << "*** This is a debugging version ***\n";
	test_hardCodedTriviaList();
	test_addNewQuestion();
	test_askUserQuestion();
	cout << "\n*** End of the debugging version ***\n";

// Insert Production code here	
#else
	// Declare variables
	TriviaHead Trivia; // Trivia linked list for this game
	string userCont = "Yes";   // Determines if user wishes to continue entering questions or not
	string userQuestion, userAnswer; // For custom questions
	int userPointValue;

	// Set up Trivia list to default values
	hardCodedTriviaList(Trivia);

	cout << "*** Welcome to Mark Gallagher's Trivia Quiz Game! ***\n";
	cout << "\nThis program allows you to enter your own questions before the game starts. Please do so now:\n\n";

	while(userCont == "Yes" || userCont == "yes" ||  userCont == "Y" || userCont == "y")
	{
		cout << "Enter a question: ";
		getline(cin, userQuestion);
		cout << "Enter an answer: ";
		getline(cin, userAnswer);
		cout << "Enter award points: ";
		cin >> userPointValue;
		cin.get();	// Required to prevent '\n' being read for next iteration
	
		// Create new node with these values
		addNewQuestion(Trivia, userQuestion, userAnswer, userPointValue);
	
		// Ask if user wants to enter more questions	
		cout << "Continue? (Yes/No): ";
		getline(cin, userCont);
	}

	cout << endl;	

	// Ask the user all of the questions
	askUserQuestion(Trivia, Trivia.totalQuestions);

	// End of game reached
	cout << "Congrats! You won " << Trivia.userPointsEarned << " total points!\n\n";
	cout << "*** Thank you for playing the trivia quiz game. Goodbye! ***\n";	
#endif
	return 0;
}

/**
 * Function initializes the Trivia linked list to contain
 * three pre-set Trivia questions and answers.
 * Postcondition: Trivia list contains 3 pre-defined questions
 * @param Trivia	Trivia linked list
 */
void hardCodedTriviaList(TriviaHead& Trivia)
{
	// Iterator
	TriviaNodePtr currentNode;

	// Set up 'head' node details
	Trivia.head = new TriviaNode;
	currentNode = Trivia.head;
	Trivia.totalQuestions = 3;
	Trivia.userPointsEarned = 0;

	// Question 1
	currentNode->question = "How long was the shortest war on record? (Hint: how many minutes?)";
	currentNode->answer = "38";
	currentNode->pointValue = 100;
	currentNode->next = new TriviaNode;
	currentNode = currentNode->next;

	// Question 2
	currentNode->question = "What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany?)";
	currentNode->answer = "Bank of Italy";
	currentNode->pointValue = 50;
	currentNode->next = new TriviaNode;
	currentNode = currentNode->next;

	// Question 3
	currentNode->question = "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports?)";
	currentNode->answer = "Wii Sports";
	currentNode->pointValue = 20;
	currentNode->next = NULL;
}

/**
 * Adds a new question to the END of the linked list "Trivia"
 * Precondition: Trivia.head = NULL for new lists
 * Postcondition: Adds a new question with specified parameters to end
 * 		  of list
 * @param Trivia	Trivia linked list to be modified
 * @param question	Question to be asked
 * @param answer 	Answer to the question
 * @param pointValue	Value of question being asked if user answers correctly
 */
void addNewQuestion(TriviaHead& Trivia, string newQuestion, string newAnswer, int newPointValue)
{
	// Iterator
	TriviaNodePtr endNode = Trivia.head;
	
	// Search for the end of the list
	while (endNode != NULL && endNode->next != NULL)
	{
		endNode = endNode->next;
	}

	// Once at end of list, add new node
	TriviaNodePtr newNode = new TriviaNode;

	// Check to ensure new operation successful
	if (newNode == NULL)
	{
		cout << "Error: Insufficient Memory";
		exit(1);
	}
	newNode->question = newQuestion;
	newNode->answer = newAnswer;
	newNode->pointValue = newPointValue;
	newNode->next = NULL;

	// Update endNode's next to point to new node
	if (endNode == NULL)
	{
		// Case if brand new list is passed in
		Trivia.head = newNode;
	}
	else
	{
		endNode->next = newNode;
	}

	// Increment head node metadata
	Trivia.totalQuestions++;
}

/**
 * Function asks user questions as specified by the numOfQuestions
 * If numOfQuestions exceeds total questions available as specified
 * by the head metadata, the function prints a warning and doesn't
 * ask a question. If the user gets the answer correct, the function
 * updates the user's score and returns 0
 * @param Trivia		List of trivia questions
 * @param numOfQuestions	Integer representing how many questions to ask 
 */
int askUserQuestion(TriviaHead& Trivia, int numOfQuestions)
{
	// Declare variables
	string userAnswer;	
	TriviaNodePtr currentNode; // Iterator
	Trivia.userPointsEarned = 0;

	// Parameter checking
	if (numOfQuestions > Trivia.totalQuestions)
	{
		cout << "Warning - There are only " << Trivia.totalQuestions << " trivia questions in this list.\n";
		return 1;
	}
	if (numOfQuestions < 1)
	{
		cout << "Warning - The number of questions to be asked must be equal to or greater than 1.\n";
		return 1; 
	}

	// Should point to first node/question
	currentNode = Trivia.head;

	for (int i = 0; i < numOfQuestions && currentNode != NULL; i++)
	{
		// Ask user the question
		cout << "Question: " << currentNode->question << endl;
		cout << "Answer: ";
		getline(cin, userAnswer);
		if (userAnswer == currentNode->answer)
		{
			cout << "Your answer is correct. You receive " << currentNode->pointValue << " points.\n";
			Trivia.userPointsEarned += currentNode->pointValue;
		}
		else
		{
			cout << "Your answer is wrong. The correct answer is " << currentNode->answer << endl;
		}
	
		cout << "Your total points: " << Trivia.userPointsEarned << endl << endl;

		currentNode = currentNode->next;
	}
	
	return 0;
}

#ifdef UNIT_TESTING
/**
 * Function tests to see if the hard-coded trivia questions
 * are properly initialized.
 */
void test_hardCodedTriviaList()
{
	// Initialize test fixtures
	TriviaHead Trivia;
	
	cout << "\nFunction to test: void hardCodedTriviaList(TriviaHead& Trivia)\n";
	cout << "\tUnit Test Case 1: Check if initialization of 3 trivia questions works properly\n";
	hardCodedTriviaList(Trivia);
	assert(Trivia.totalQuestions == 3);
	// assertions for first question
	assert(Trivia.head->question == "How long was the shortest war on record? (Hint: how many minutes?)");
	assert(Trivia.head->answer == "38");
	assert(Trivia.head->pointValue == 100);
	// assertions for second question
	assert(Trivia.head->next->question == "What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany?)");
	assert(Trivia.head->next->answer == "Bank of Italy");
	assert(Trivia.head->next->pointValue == 50);
	// assertions for third question
	assert(Trivia.head->next->next->question == "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports?)");
	assert(Trivia.head->next->next->answer == "Wii Sports");
	assert(Trivia.head->next->next->pointValue == 20);
	assert(Trivia.head->next->next->next == NULL);

	cout << "\tCase 1 passed...\n";
}

/**
 * Function tests to see adding a new trivia question works 
 * properly.
 * Precondition: test_hardCodedTriviaList(Trivia) must have 
 * 		 successfully tested that function
 */
void test_addNewQuestion()
{
	// Initialize test fixtures
	TriviaHead Trivia;
	Trivia.head = NULL; // Required for brand new lists
	Trivia.totalQuestions = 0;
	string newQuestion = "Does a set of all sets contain itself?";
	string newAnswer = "This statement is false";
	int newPointValue = 3;
	int totalQuestionsBeforeAdd = Trivia.totalQuestions;
	TriviaNodePtr secondToLastNode;

	cout << "\nFunction to test: void addNewQuestion(TriviaHead& Trivia, string newQuestion, string newAnswer, int newPointValue)\n";

	// Case 1
	cout << "\tUnit Test Case 1: Check if function adds new question an empty list\n";
	addNewQuestion(Trivia, newQuestion, newAnswer, newPointValue);

	// Run assertions
	secondToLastNode = Trivia.head;
	assert(secondToLastNode->question == newQuestion);
	assert(secondToLastNode->answer == newAnswer);
	assert(secondToLastNode->pointValue == newPointValue);
	assert(Trivia.totalQuestions == totalQuestionsBeforeAdd + 1);

	cout << "\tCase 1 passed...\n";
	
	// Case 2
	cout << "\tUnit Test Case 2: Check if function adds new question in a pre-initialized list\n";
	hardCodedTriviaList(Trivia);
	totalQuestionsBeforeAdd = Trivia.totalQuestions;
	addNewQuestion(Trivia, newQuestion, newAnswer, newPointValue);
	
	// Run assertions
	secondToLastNode = Trivia.head->next->next->next;
	assert(secondToLastNode->question == newQuestion);
	assert(secondToLastNode->answer == newAnswer);
	assert(secondToLastNode->pointValue == newPointValue);
	assert(Trivia.totalQuestions == totalQuestionsBeforeAdd + 1);

	cout << "\tCase 2 passed...\n";
}

/**
 * Functions tests the asking the user a question functions
 * works properly
 * Precondition: The test_hardCodedTriviaList(Trivia) must have
 * 		 shown that function to be operating properly
 */
void test_askUserQuestion()
{
	// Initialize test fixtures
	TriviaHead Trivia;
	int successOrFailed;
	int noQuestions = 0, oneQuestion = 1, allQuestions = 3, moreQuestions = 5;
	
	// Setup Trivia list
	hardCodedTriviaList(Trivia);

	cout << "\nFunction to test: int askUserQuestion(TriviaHead& Trivia, int numOfQuestions)\n";

	// Case 1
	cout << "\tUnit Test Case 1: Ask no questions. The program should give a warning message.\n";
	successOrFailed = askUserQuestion(Trivia, noQuestions);
	
	// Run assertions
	assert(successOrFailed == 1);
	cout << "\tCase 1 passed...\n";
	
	// Case 2.1
	cout << "\n\tUnit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer.\n";
	successOrFailed = askUserQuestion(Trivia, oneQuestion);

	// Run assertions
	assert(successOrFailed == 0);
	assert(Trivia.userPointsEarned == 0);
	cout << "\tCase 2.1 passed...\n";

	// Case 2.2
	cout << "\n\tUnit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer.\n";
	successOrFailed = askUserQuestion(Trivia, oneQuestion);
	
	// Run assertions
	assert(successOrFailed == 0);
	assert(Trivia.userPointsEarned == 100);
	cout << "\tCase 2.2 passed...\n";

	// Case 3
	cout << "\n\tUnit Test Case 3: Ask all of the questions in the linked list. Answers given do not matter.\n";
	successOrFailed = askUserQuestion(Trivia, allQuestions);

	// Run assertions
	assert(successOrFailed == 0);
	// cover all possible scores
	assert(Trivia.userPointsEarned == 0 || Trivia.userPointsEarned == 100 || Trivia.userPointsEarned == 150
		|| Trivia.userPointsEarned == 170 || Trivia.userPointsEarned == 50 || Trivia.userPointsEarned == 20
		|| Trivia.userPointsEarned == 70 || Trivia.userPointsEarned == 120);
	cout << "\tCase 3 passed...\n";

	// Case 4
	cout << "\n\tUnit Test Case 4: Attempt to ask 5 questions in the linked list. Program should give a warning message.\n";
	successOrFailed = askUserQuestion(Trivia, moreQuestions);

	// Run assertions
	assert(successOrFailed == 1);
	cout << "\tCase 4 passed...\n";
}
#endif
