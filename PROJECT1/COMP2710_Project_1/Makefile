# Dragons - A simple text based game
# Makefile makes Project 1 program
# COMP2710 Project 1
# Mark Gallagher Jr | mag0038@auburn.edu
# Filename: Makefile
# Written in Vi text editor
# Version: 4/13/2015, v1
# Sources used: Dr. Qin's tutorial on creating makefiles

# Compiler is g++
CC = g++

# -c flag for creating object files
CCFLAGS = -c

# Executable files names 
EXECUTABLE = project1_main
UNIT_TESTS = project1_test

# Stores all of the object files to be compiled for final program
OBJFILES = project1_system.o project1_menu.o project1_encounters.o project1_puzzle.o project1_scoreboard.o

all : ${EXECUTABLE}

${EXECUTABLE} : project1_main.o ${OBJFILES} 
	${CC} project1_main.o ${OBJFILES} -o ${EXECUTABLE} 

# Unit tests, only made when want to run tests. Depends on everything (of course)
${UNIT_TESTS} : project1_test.cpp project1_test.h ${OBJFILES} 
	${CC} ${CCFLAGS} project1_test.cpp
	${CC} project1_test.o ${OBJFILES} -o ${UNIT_TESTS}

# Main function
project1_main.o : ${OBJFILES}
	${CC} ${CCFLAGS} project1_main.cpp

# System file: depends on scoreboard as well for calculate_score(player& userPlayer) function
project1_system.o : project1_system.cpp project1_system.h project1_scoreboard.o
	${CC} ${CCFLAGS} project1_system.cpp

# Menu file: handles all actions possible at game menu, relies on encounter and puzzle
project1_menu.o : project1_menu.cpp project1_menu.h project1_encounters.o project1_puzzle.o project1_system.o
	${CC} ${CCFLAGS} project1_menu.cpp

# Encounters file: handles all encounters to be executed
project1_encounters.o : project1_encounters.cpp project1_encounters.h project1_system.o
	${CC} ${CCFLAGS} project1_encounters.cpp

# Puzzle file: handles puzzle structure and asking puzzle questions
project1_puzzle.o : project1_puzzle.cpp project1_puzzle.h project1_system.o
	${CC} ${CCFLAGS} project1_puzzle.cpp

# Scoreboard file: handles operations on scoreboard, including loading and saving
project1_scoreboard.o : project1_scoreboard.cpp project1_scoreboard.h 
	${CC} ${CCFLAGS} project1_scoreboard.cpp

clean : 
	rm -rf *.o ${EXECUTABLE} ${UNIT_TESTS}
