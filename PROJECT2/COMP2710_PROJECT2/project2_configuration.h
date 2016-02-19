// auDiskTool - A Tool for Monitoring Disk Devices 
// Header file for Configuration class 
// COMP2710 Project 2
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: project2_configuration.h
// Written in Vi text editor
// Version: 4/29/2015, v1
// Sources used: Dr. Qin's presentation on Project 2 class designs
// 		 Dr. Qin's presentation on namespaces

#ifndef PROJECT2_CONFIGURATION_H
#define PROJECT2_CONFIGURATION_H

#include<iostream>
#include<string>
#include<fstream>
#include "project2_command_line.h"
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using auDiskTool::CommandLine;
using auDiskTool::flag_t;

// Class uses unsigned integers
typedef unsigned int u_int;

// Constant for default .conf filename
const string CONFIG_FILENAME = "audisktool.conf";

// Add to auDiskTool namespace
namespace auDiskTool {

	/********** CLASS DEFINITION **********/
	class Configuration {
		private:
			string reportPath;	// stores current report path, set to default
			u_int interval;				// interval between records
			u_int count;				// count of records
			bool blkReadFlag;			// various parameter flags
			bool blkReadSFlag;
			bool kbReadSFlag;
			bool blkWrtnFlag;
			bool blkWrtnSFlag;
			bool kbWrtnSFlag;
			bool changed;				// detect if conf changed
		public:
			/**
			 * Constructor: sets reportPath to defualt filename
			 * Also sets the default parameters. These are changed when .conf file opened
			 */
			Configuration();
			/**
 			 * Sets the configuration given a certain command.
 			 * Ex. If the setting calls to change the report path, will do so.
 			 * Update changed flag if a parameter was changed
 			 * @param paramToChange	CommandLine object with info to change
 			 * @return True if successful, false if no change needed
 			 */
			bool set_parameter(CommandLine paramToChange);
			/**
			 * Getter for the report path
			 * @return string representing the report file path
			 */
			string get_report_path();
			// These getters are required for Tool::run() to be able to access the configuration info
			/**
			 * Getter for a flag's current status. A flag other than parameter settings
			 * will return the status of the changed flag.
			 * @param flagSelect 	flag_t specifies which flag value is desired
			 */
			bool get_flag_state(flag_t flagSelect);
			/**
			 * Getter for interval
			 * @return the current interval (in seconds)	
			 */
			u_int get_interval();
			/**
			 * Getter for count
			 * @return the number of records to be taken
			 */
			u_int get_count();
			/**
			 * Prints the current config information to the user
			 */
			void print_conf();
			/**
			 * Loads the .conf file. Errors will return false, if succesful returns true.
			 * @return True if successful, false if not
			 */
			bool load_conf();
			/**
			 * Saves the .conf file. If changed is set to FALSE, return false without saving
			 * @return True if successful, false if not
			 */
			bool save_conf();
	}; // class Configuration

} // namespace auDiskTool

#endif
