// auDiskTool - A Tool for Monitoring Disk Devices 
// Implementation for CommandLine class 
// COMP2710 Project 2
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: project2_command_line.cpp
// Written in Vi text editor
// Version: 5/1/2015, v1
// Sources used: Dr. Qin's presentation on Project 2 class designs
// 		 Dr. Qin's presentation on namespaces
// 		 Dr. Qin's sample code for command line parsing
// 		 Dr. Qin's new sample code for converting string to int

#include "project2_command_line.h"

namespace auDiskTool {

	/**
	 * Constructor: clear all values in cmd struct
	 */
	CommandLine::CommandLine() {
		cmd.type = CMD_CLEARED;
		cmd.flag = FLAG_CLEARED;
		cmd.value = 0;
		cmd.reportPath = "";
	}

	/**
	 * Getter for command type
	 */
	cmd_t CommandLine::get_type() {
		return cmd.type;
	}

	/**
	 * Getter for command flag
	 */
	flag_t CommandLine::get_flag() {
		return cmd.flag;
	}
	
	/**
	 * Getter for the u_int value
	 */
	u_int CommandLine::get_value() {
		return cmd.value;
	}

	/**
	 * Getter for string value (report path)
	 */
	string CommandLine::get_str_value() {
		return cmd.reportPath;
	}

	/**
	 * Utility function to convert a string into a cmd_t
	 */
	cmd_t CommandLine::str_to_cmd_t(string const& inputString) {
		if (inputString == "run") return RUN;
		if (inputString == "set") return SET;
		if (inputString == "print") return PRINT;
		if (inputString == "save") return SAVE;
		if (inputString == "help") return HELP;
		if (inputString == "exit") return EXIT;
		return CMD_CLEARED; // no valid string found
	}

	/**
 	 * Utility function to convert a string into a flag_t
 	 */
	flag_t CommandLine::str_to_flag_t(string const& inputString) {
		if (inputString == "interval") return INTERVAL;
		if (inputString == "count") return COUNT;
		if (inputString == "report") return REPORT;
		if (inputString == "conf") return CONF;
		if (inputString == "blk_read") return BLK_READ;
		if (inputString == "blk_read/s") return BLK_READ_S;
		if (inputString == "kb_read/s") return KB_READ_S;
		if (inputString == "blk_write") return BLK_WRTN;
		if (inputString == "blk_write/s") return BLK_WRTN_S;
		if (inputString == "kb_write/s") return KB_WRTN_S;
		return FLAG_CLEARED; // no valid string found
	}

	/**
	 * Prompts the user for a command. Continues pestering user if command entered 
	 * is invalid.
	 */
	void CommandLine::get_command() {
		// Variables
		string enteredCommand;
		bool isValidCommand;

		// Ask user for a command
		do {
			cout << "\n>";
			getline(cin, enteredCommand);
			isValidCommand = parse_command(enteredCommand);
			
			// Remind user to use 'help' if invalid command
			if (!isValidCommand) {
				cout << "Invalid command. Please use the 'help' command for more information.\n";
			}
	
		} while (!isValidCommand);
	}

	/**
	 * Parses a string into the 3 elements of a command. Saves elements
	 * into appropiate sections of the cmd data structure
	 * Returns true if command that entered was valid
	 */
	bool CommandLine::parse_command(string cmdString) {
		// Position variable to keep track of important locations in command
		int position; 

		// Find the command type - space seperated
		position = cmdString.find(" ");
		// Get the type as a string, convert to cmd_t and save
		cmd.type = str_to_cmd_t(cmdString.substr(0, position));

		// Check if type returned is CLEARED, if so, invalid command
		if (cmd.type == CMD_CLEARED) return false;

		// Remove the type from the command string
		cmdString = cmdString.substr(position + 1);

		// If cmdString does not contain the cmd.type, as in, position = npos 
		// and the substr returned the full cmdString again, then there are no flags.
		// Otherwise, there is a flag that needs to be read.
		if (str_to_cmd_t(cmdString) != cmd.type) {
			// check if supposed to have flag in first place, if not, invalid
			if (cmd.type == HELP || cmd.type == RUN || cmd.type == SAVE || cmd.type == EXIT) {
				// If type is help, run, save, or exit, no flags should've been given, invalid.
				return false;
			}

			// locate the flag in the command string
			position = cmdString.find(" ");
			// Obtain the flag string, convert to flag_t and save
			cmd.flag = str_to_flag_t(cmdString.substr(0, position));

			// Same as before: check if flag is CLEARED, if so, invalid command
			if (cmd.flag == FLAG_CLEARED) return false;

			// Remove the flag from the command string
			// cmdString should now either hold only the flag OR
			// only the value (if present)
			cmdString = cmdString.substr(position + 1);

			// Same as first if-branch, except for cmd.flag
			if (str_to_flag_t(cmdString) != cmd.flag) {
				// Check if supposed to have a value in first place:
				if (cmd.flag == CONF || cmd.type != SET) {
					// If flag is conf or the type is not set, no value should be entered
					return false;
				}

				// Check if flag is for REPORT. If so, 
				// need to save value as a string.
				if (cmd.flag == REPORT) {
					cmd.reportPath = cmdString;
				}
				// Else: it's an int value to save
				else {
					istringstream valueBuffer(cmdString);
					valueBuffer >> cmd.value;
				}
			}
			// Else: no value to save, check if supposed to have one first
			else {
				if (cmd.flag != CONF && cmd.type == SET) {
					// If flag is one that needed a value set but none provided, invalid command
					return false;
				}
				cmd.value = 0;
				cmd.reportPath.clear();
			}
		}
		// Else: no flag or value
		else {
			// Check is supposed to have a flag or not:
			if (cmd.type == SET || cmd.type == PRINT) {
				// If type is set or print and no flag given, invalid command
				return false;
			}

			cmd.flag = FLAG_CLEARED;
			cmd.value = 0;
			cmd.reportPath.clear();
		}

		return true;
	}

} // namespace auDiskTool
