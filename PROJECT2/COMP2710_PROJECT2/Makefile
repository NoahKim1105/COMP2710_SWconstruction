# auDiskTool - A Tool for Monitoring Disk Devices
# Makefile to compile the project
# COMP2710 Project 2
# Mark Gallagher Jr | mag0038@auburn.edu
# Filename: Makefile
# Written in Vi text editor
# Version: 5/1/2015, v1
# Sources used: Dr. Qin's presentation on makefiles
# 		Stackoverflow for info to use C++11 compiler

# Compiler is g++
CC = g++

# -c flag for creating object files
CCFLAGS = -c

# Executable file names
EXECUTABLE = auDiskToolv1

# Stores all of the object files to be compiled for final program
OBJFILES = project2_main.o project2_tool.o project2_configuration.o project2_command_line.o project2_report.o

all : ${EXECUTABLE}

${EXECUTABLE} : ${OBJFILES}
	${CC} ${OBJFILES} -o ${EXECUTABLE}

# Main function
project2_main.o : project2_tool.o
	${CC} ${CCFLAGS} project2_main.cpp

# Tool class - relies on all modules
project2_tool.o : project2_tool.cpp project2_tool.h project2_configuration.o project2_command_line.o project2_report.o
	${CC} ${CCFLAGS} project2_tool.cpp

# Report class - relies on Configuration class
project2_report.o : project2_report.cpp project2_report.h project2_configuration.o
	${CC} ${CCFLAGS} project2_report.cpp

# Configuration class - relies on CommandLine only
project2_configuration.o : project2_configuration.cpp project2_configuration.h project2_command_line.o
	${CC} ${CCFLAGS} project2_configuration.cpp

# CommandLine class - does not rely on other modules, just its header
project2_command_line.o : project2_command_line.cpp project2_command_line.h
	${CC} ${CCFLAGS} project2_command_line.cpp

# Clean - removes all object files and executables
clean : 
	rm -rf *.o ${EXECUTABLE}
