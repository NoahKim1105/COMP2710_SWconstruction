// Dragons - A simple text based game
// File contains function implementations used for encounter handling
// COMP2710 Project 1
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: project1_encounters.cpp
// Written in Vi text editor
// Version: 4/13/2015, v1
// Sources used: Dr. Qin's PowerPoint on using cin to get string and int values, also 
// 			helpful for error-checking the input 
// 		 Dr. Qin's presentation of linked list operations

#include "project1_encounters.h"

// Initializes encounters to the preset specs. The input array should NOT have been allocated yet (new)
// All point values are considered uninitialized since most of the values are to be randomized
void init_encounters(encounterPtr& encArray)
{
	// Initialize dynamic array
	encArray = new encounter[NUM_OF_ENCOUNTERS];

	// Initialize encounter elements 
	// NOTHING encounter
	encArray[0].enctType = NOTHING;
	encArray[0].message = "OH MY GOSH, NOTHING HAPPENS...\n";
	encArray[0].actionArray[0].actionType = REWARD;
	encArray[0].actionArray[0].attrType = STEPS;
	encArray[0].actionArray[0].points = -1;

	encArray[0].actionArray[1].actionType = PENALTY;
	encArray[0].actionArray[1].attrType = TIME;
	encArray[0].actionArray[1].points = -1;

	encArray[0].numOfActions = 2;

	// PUZZLE encounter
	// Info here is NOT handled through encounter functions but by puzzle functions. As such, values here are DONT CARES
	encArray[1].enctType = PUZZLE;
	encArray[1].message = "It's puzzle time!\n";
	encArray[1].actionArray[0].actionType = REWARD;
	encArray[1].actionArray[0].attrType = TIME;
	encArray[1].actionArray[0].points = 0;

	encArray[1].numOfActions = 1;

	// PROFESSOR encounter
	encArray[2].enctType = PROFESSOR;
	encArray[2].message = "You see a tall shadowy figure approach you...\n";
	encArray[2].actionArray[0].actionType = REWARD;
	encArray[2].actionArray[0].attrType = INTEL;
	encArray[2].actionArray[0].points = 1;

	encArray[2].actionArray[1].actionType = PENALTY;
	encArray[2].actionArray[1].attrType = TIME;
	encArray[2].actionArray[1].points = -1;

	encArray[2].actionArray[2].actionType = REWARD;
	encArray[2].actionArray[2].attrType = STEPS;
	encArray[2].actionArray[2].points = -1;

	encArray[2].numOfActions = 3;

	// STUDENT encounter
	encArray[3].enctType = STUDENT;
	encArray[3].message = "You see a short figure approach you...\n";
	encArray[3].actionArray[0].actionType = PENALTY;
	encArray[3].actionArray[0].attrType = TIME;
	encArray[3].actionArray[0].points = -1;

	encArray[3].actionArray[1].actionType = REWARD;
	encArray[3].actionArray[1].attrType = STEPS;
	encArray[3].actionArray[1].points = -1;

	encArray[3].numOfActions = 2;
	
	// GRUNT encounter
	encArray[4].enctType = GRUNT;
	encArray[4].message = "A small elfish figure hops towards you with something in his hand...\n";
	encArray[4].actionArray[0].actionType = PENALTY;
	encArray[4].actionArray[0].attrType = INTEL;
	encArray[4].actionArray[0].points = -1;

	encArray[4].actionArray[1].actionType = PENALTY;
	encArray[4].actionArray[1].attrType = TIME;
	encArray[4].actionArray[1].points = -1;

	encArray[4].actionArray[2].actionType = REWARD;
	encArray[4].actionArray[2].attrType = STEPS;
	encArray[4].actionArray[2].points = -1;

	encArray[4].numOfActions = 3;
	 
	// PAPER encounter
	encArray[5].enctType = PAPER;
	encArray[5].message = "A flying box of papers approaches your position!\n";
	encArray[5].actionArray[0].actionType = REWARD;
	encArray[5].actionArray[0].attrType = MONEY;
	encArray[5].actionArray[0].points = 1;

	encArray[5].actionArray[1].actionType = PENALTY;
	encArray[5].actionArray[1].attrType = TIME;
	encArray[5].actionArray[1].points = -1;

	encArray[5].actionArray[2].actionType = REWARD;
	encArray[5].actionArray[2].attrType = STEPS;
	encArray[5].actionArray[2].points = -1;

	encArray[5].numOfActions = 3;
}

// Generates an encounter ID within the correct range of IDs
// @return random encounter ID according to game spec
u_short generate_encounter_ID()
{
	u_short encID;

	int randomNum = rand() % 100;

	// Depending on random num, select appropiate encID
	if (randomNum < 25) encID = NOTHING;
	else if (randomNum < 55) encID = PUZZLE;
	else if (randomNum < 65) encID = PROFESSOR;
	else if (randomNum < 75) encID = STUDENT;
	else if (randomNum < 90) encID = GRUNT;
	else encID = PAPER;

	return encID;
}

// Displays a professor encounter and modifies player
void professor_enc(player& userPlayer, encounter profEnc)
{
	// Determine how much to modify attributes by
	u_short modIntelBy = rand() % ENCOUNTER_POINT_UPPER_BOUND;
	short modTimeBy = -1 * ((rand() % ENCOUNTER_POINT_UPPER_BOUND) + 1);
	
	// Modify encounter so that it modifies the correct amount of points
	profEnc.actionArray[0].points = modIntelBy;
	profEnc.actionArray[1].points = modTimeBy;

	// Display some fun messages depending on modification
	if (modIntelBy == 0)
	{
		cout << "You run into a humanities professor...he's not very helpful\n";
	}
	else if (modIntelBy < ENCOUNTER_POINT_UPPER_BOUND - 1)
	{
		cout << "You find a helpful professor who provides you insight into your current situation\n";
	}
	else
	{
		cout << "You find a very insightful and ingenious professor! He gives you the secret to infinite wealth. He leans in and whispers: ";
		cout << EASTER_EGG_TRIGGER << endl;
	}

	cout << endl;

	if (modTimeBy == -1)
	{
		cout << "The professor just runs around you, saving you the time of talking\n";
	}
	else if (modTimeBy > ENCOUNTER_POINT_LOWER_BOUND + 1)
	{
		cout << "The professor takes up quite a bit of time...\n";
	}
	else
	{
		cout << "The professor takes up A TON OF TIME, but he drops a note that reads: the secret is " << EASTER_EGG_TRIGGER << endl;
	}

	// Modify attributes accordingly
	for (int i = 0; i < profEnc.numOfActions; i++)
	{
		point_handler(userPlayer, profEnc.actionArray[i]);
	}
}

// Runs a grad student encounter
void student_enc(player& userPlayer, encounter studEnc)
{
	// Determine how much to modify attributes by
	short modTimeBy = -1 * ((rand() % ENCOUNTER_POINT_UPPER_BOUND) + 1);

	// Modify encounter accordingly
	studEnc.actionArray[0].points = modTimeBy;

	// Display some fun messages
	if (modTimeBy == -1)
	{
		cout << "You run into your fellow...ARCH NEMESIS! He says his usual speech about how he'll do better than you and blah blah, you ignored him halfway though so you saved time, good for you\n";
	}
	else if (modTimeBy > ENCOUNTER_POINT_LOWER_BOUND + 1)
	{
		cout << "You run into your primary arch nemesis!!! He says his usual speech about how not only will he do better than you, but he will also rule the world, the galaxy, and then the universe. Once he started talking about space you got really interested though so instead of moving onward with your quest, you listen to your nemesis. A slow clap for you, hero\n";
	}
	else
	{
		cout << "It's your friend! He's pretty cool to talk to, so instead of focusing on your mission to save Princess Shelby, you talk with your friend about things like ponies, video games, space, life, oh look at the time you lost...good job, hero\n";
	}

	// Modify attributes accordingly
	for (int i = 0; i < studEnc.numOfActions; i++)
	{
		point_handler(userPlayer, studEnc.actionArray[i]);
	}
}

// Runs a grunt work encounter
void grunt_enc(player& userPlayer, encounter gruntEnc)
{
	// Determine how much to modify attrbiutes by
	short modIntelBy = -1 * ((rand() % ENCOUNTER_POINT_UPPER_BOUND) + 1);
	short modTimeBy = -1 * ((rand() % ENCOUNTER_POINT_UPPER_BOUND) + 1);

	// Modify encounter accordingly
	gruntEnc.actionArray[0].points = modIntelBy;
	gruntEnc.actionArray[1].points = modTimeBy;

	// Display some fun messages
	if (modIntelBy == -1)
	{
		cout << "Oh no, a grunt, he's giving you work, oh no, it's, it's.....oh, it's just signing an attendence sheet. You can do that, right?\n";
	}
	else if (modIntelBy > ENCOUNTER_POINT_LOWER_BOUND + 1)
	{
		cout << "A grunt! What's he doing?! Oh no, he's giving you work, you must resist, RESIST THE WORK...it didn't work. You're forced to work now, so sad\n";
	}
	else
	{
		cout << "It's a grunt, he gives you a creepy smile and proceeds to throw sheets of paper at you! Each one is something worse and more mediocre of a task than the last! You scream for help, no, no, NO, PLEASE NO MORE, NO MORE WORK!!!, NOOOOOOOOOOOOOOOOOOOOOOOOOOO\n";
	}

	cout << endl;

	if (modTimeBy == -1)
	{
		cout << "You somehow managed to complete the work very quickly, good for you\n";
	}
	else if (modTimeBy > ENCOUNTER_POINT_LOWER_BOUND + 1)
	{
		cout << "Whelp, that took some time to do, but you got it done...sadly, you get no compensation\n";
	}
	else
	{
		cout << "OH MY GOSH THAT GRUNT GAVE YOU SOOOOOO MUCH WORK. You started WHINING half-way through, taking up SOOOOOOO much more time than needed...\n";
	}

	// Modify character
	for (int i = 0; i < gruntEnc.numOfActions; i++)
	{
		point_handler(userPlayer, gruntEnc.actionArray[i]);
	}
}

// Runs a grade papers encounter
void paper_enc(player& userPlayer, encounter papEnc)
{
	// Set how much to modify attributes by
	u_short modMoneyBy = rand() % ENCOUNTER_POINT_UPPER_BOUND + 1;
	short modTimeBy = -1 * ((rand() % ENCOUNTER_POINT_UPPER_BOUND) + 1);

	// Modify encounter accordingly
	papEnc.actionArray[0].points = modMoneyBy;
	papEnc.actionArray[1].points = modTimeBy;

	// Display some fun messages
	if (modMoneyBy == 1)
	{
		cout << "You got papers to grade! But it's all for that 1000-level class...so you don't get paid a lot\n";
	}
	else if (modMoneyBy < ENCOUNTER_POINT_UPPER_BOUND - 1)
	{
		cout << "The wild flying paper box is full of things to grade! You choose to grade, ALL OF EM!! Your pay is decent at least\n";
	}
	else
	{
		cout << "The wild flying paper box ATTACKED! You use graduate student powers! It's super effective!! The box drops with money falling out of it! You find one paper left to grade, the student's answer to number 7 is " << EASTER_EGG_TRIGGER << ". Odd...that correct answer was obviously \"DONUTS\", why put a number there...hm, weird, indeed\n";
	}

	cout << endl;

	if (modTimeBy == -1)
	{
		cout << "Phew, grading went by very quickly. Nice job, you hard worker!\n";
	}
	else if (modTimeBy > ENCOUNTER_POINT_LOWER_BOUND + 1)
	{
		cout << "Finish up, you're burning time!! You get through it, not before wasting time doodling on your student's papers!\n";
	}
	else
	{
		cout << "Wow, really, you took THAT LONG to grade? Those papers must've been really tough...hopefully it'll all be worth it right? Maybe the Princess will have more money than you, then you don't have to grade...\n";
	}

	// Modify player
	for (int i = 0; i < papEnc.numOfActions; i++)
	{
		point_handler(userPlayer, papEnc.actionArray[i]);
	}
}
