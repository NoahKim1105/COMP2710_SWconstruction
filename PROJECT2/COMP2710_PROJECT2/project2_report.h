// auDiskTool - A Tool for Monitoring Disk Devices 
// Header file for Report class 
// COMP2710 Project 2
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: project2_report.h
// Written in Vi text editor
// Version: 4/29/2015, v1
// Sources used: Dr. Qin's presentation on Project 2 class designs
// 		 Dr. Qin's presentation on namespaces

#ifndef PROJECT2_REPORT_H
#define PORJECT2_REPORT_H

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include "project2_configuration.h"
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using auDiskTool::Configuration;

// Class uses unsigned ints
typedef unsigned int u_int;

// Add to namespace auDiskTool
namespace auDiskTool {

	/********** DATA STRUCTURES **********/
	// Record data structure
	struct Record {
		u_int blk_read;
		double blk_read_s;
		double kb_read_s;
		u_int blk_wrtn;
		double blk_wrtn_s;
		double kb_wrtn_s;
		string device;
	};

	/********** CLASS DEFINITION **********/
	class Report {
		private:
			// Vector holds all records
			vector<Record> recordList;
			// the report path is stored in the Configuration class!
		public:
			/**
			 * Constructor: default
			 */
			Report();
			/**
			 * Adds a new record to the report list, given a pre-formed record
			 * This pre-formed record should only have parameters shown as
			 * specified in Configuration (handled by Tool)
			 * @param newRecord	Record struct to be added to the list
			 */
			void add_record(Record newRecord);
			/**
 			 * Cleared the report contents so that brand new data can be written
 			 * to a new file. This way contents of report.adt aren't transferred
 			 * to a new file.
 			 */
			void clear_report();
			/**
			 * Loads a report from file stored in current Configuration
			 * @param currConfig	Configuration object that stores the report path
			 * @return bool true if successful, false otherwise
			 */
			bool load_report(Configuration currConfig);
			/**
			 * Saves report to file stores in current Configuration
			 * @param currConfig	Configuration object that stores the report path
			 * @return bool true if successful, false otherwise
			 */
			bool save_report(Configuration currConfig);
			/**
			 * Prints report to the console output
			 */
			void print_report();
	}; // class Report

} // namespace auDiskTool

#endif
