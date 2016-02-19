// auDiskTool - A Tool for Monitoring Disk Devices 
// Header file for Tool class 
// COMP2710 Project 2
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: project2_tool.h
// Written in Vi text editor
// Version: 4/30/2015, v1
// Sources used: Dr. Qin's presentation on Project 2 class designs
// 		 Dr. Qin's presentation on namespaces
// 		 Dr. Qin's sample code to convert strings to ints

#ifndef PROJECT2_TOOL_H
#define PROJECT2_TOOL_H

#include<iostream>
#include<string>
#include<sstream>			// convert string to int
#include<fstream>
#include<unistd.h>			// for sleep(seconds) function
#include "project2_command_line.h"
#include "project2_configuration.h"
#include "project2_report.h"
using std::cout;
using std::string;
using std::istringstream;
using std::ifstream;
using std::getline;
using namespace auDiskTool;

// Add Tool class into the namespace as well
namespace auDiskTool {

	/********** CLASS DEFINITION **********/
	class Tool {
		private:
			CommandLine cmdLine;
			Configuration config;
			Report report;
			ifstream diskstatStream;
			unsigned long lastSectsRead, lastSectsWrtn;	// used by parse_diskstat()
			/**
			 * Function responds to cmd input. As in, after running
			 * CommandLine.get_command(), this function responds to 
			 * the newly entered command.
			 */
			void respond_cmd();
			/**
			 * RUN action; executes the tool's stat-collecting and
			 * reporting functions
			 */
			void run();
			/**
			 * Parses the data in diskstat and create a Record from 
			 * that data.
			 * @return Record a FILTERED Record, as in, follows from 
			 * 		parameters spec'd in config
			 */
			Record parse_diskstat();
			/**
			 * HELP action; executes whenever the user wants to know
			 * the available commands OR when the user enters an
			 * invalid command. 
			 * Displays help contents.
			 */
			void help();
		public:
			/**
			 * Constructor: default constructor, doesn't do anything
			 * but allocate memory for the object.
			 */
			Tool();
			/**
			 * Initializes all of the data modules to be ready to receive
			 * and display information. This includes opening files such as
			 * diskstat and the default configuration file. It also opens the
			 * default report file (if it exists) and loads records into the
			 * report.
			 */
			void init();
			/**
			 * Handles running the entire program instead of main().
			 * Called once from main(), runs through program. Terminates when
			 * user wishes to exist program.
			 */
			void start();
			/**
			 * Cleanup function: called when program ends. Must ensure that
			 * if the config file needs to be saved that it is saved. Also
			 * closes all open files properly.
			 */
			void exit();
	}; // class Tool

} // namespace auDiskTool

#endif
