// auDiskTool - A Tool for Monitoring Disk Devices 
// Header file for CommandLine class 
// COMP2710 Project 2
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: project2_command_line.h
// Written in Vi text editor
// Version: 5/1/2015, v1
// Sources used: Dr. Qin's presentation on Project 2 class designs
// 		 Dr. Qin's presentation on namespaces
// 		 Dr. Qin's sample for converting strings to ints

#ifndef PROJECT2_COMMAND_LINE_H
#define PROJECT2_COMMAND_LINE_H

#include<string>
#include<sstream>
#include<iostream>
using std::string;
using std::istringstream;	// for converting string to ints
using std::cout;
using std::endl;
using std::cin;
using std::getline;

// typedef for unsigned ints used in this class
typedef unsigned int u_int;

// Add into auDiskTool namespace
namespace auDiskTool {

	/********** DATA STRUCTURES **********/

	// enumerated type for command types
	enum cmd_t {
		RUN,
		SET,
		PRINT,
		SAVE,
		HELP,
		EXIT,
		CMD_CLEARED
	};

	// enumerated type for flag types
	enum flag_t {
		INTERVAL,
		COUNT,
		REPORT,
		CONF,
		BLK_READ,
		BLK_READ_S,
		KB_READ_S,
		BLK_WRTN,
		BLK_WRTN_S,
		KB_WRTN_S,
		FLAG_CLEARED
	};
	
	// Command data structure to store last entered command
	struct Command {
		cmd_t type;
		flag_t flag;
		u_int value;
		string reportPath;	// report file path *IF* type == SET && flag == REPORT
	};

	/********** CLASS DEFINITION **********/
	class CommandLine {
		private:
			Command cmd;		// stores command last entered
			// these are utility functions to convert input to types
			/**
			 * Function accepts a string and converts it to the enum type
			 * cmd_t if the string matches one of the cmd_t
			 * @param inputString	the string entered by the user
			 * @return the inputString as a valid cmd_t. If no valid cmd_t found, return CLEARED
			 */
			cmd_t str_to_cmd_t(string const& inputString);
			/**
			 * Function accepts a string and converts it to the enum type
			 * flag_t if the string matches one of the flag_t
			 * @param inputString	the string entered by ther user
			 * @return the inputString as a valid flag_t. If no valid flag_t found, return CLEARED
			 */
			flag_t str_to_flag_t(string const& inputString);
			/**
			 * Parses a string command into the command struct
			 * @param inputString	the entire command string entered by user
			 * @return bool true if command is VALID, false otherwise
			 */
			bool parse_command(string cmdString);
		public:
			/**
			 * Constructor: initializes cmd to cleared values
			 */
			CommandLine();
			/**
			 * Getter for command type
			 * @return cmd_t type of command last entered
			 */
			cmd_t get_type();
			/**
			 * Getter for command flag
			 * @return flag_t flag of command last entered
			 */
			flag_t get_flag();
			/**
			 * Getter for value entered
			 * @return u_int value of parameter entered
			 */
			u_int get_value();
			/**
			 * Getter for string input (for report path)
			 * @return string value entered
			 */
			string get_str_value();
			/**
			 * Prompts user to enter a command. Relies on parse_command(string) 
			 * to properly form command structure.
			 */
			void get_command();
	}; // class CommandLine

} // namespace auDiskTool

#endif
