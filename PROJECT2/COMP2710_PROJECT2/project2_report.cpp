// auDiskTool - A Tool for Monitoring Disk Devices 
// Implementation for Report class 
// COMP2710 Project 2
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: project2_report.cpp
// Written in Vi text editor
// Version: 4/30/2015, v1
// Sources used: Dr. Qin's presentation on Project 2 class designs
// 		 Dr. Qin's presentation on namespaces

#include "project2_report.h"

namespace auDiskTool {

	/**
	 * Constructor: Default
	 */
	Report::Report() {}

	/**
	 * Adds a new record to the recordList to be written to the report file
	 * later. 
	 */
	void Report::add_record(Record newRecord) {
		recordList.push_back(newRecord);
	}

	/**
	 * Empties the recordList vector so that new entries can be put in.
	 * Only used when a new report path is entered
	 */
	void Report::clear_report() {
		recordList.clear();
	}

	/**
	 * Saves the report to the filename specified in currConfig.
	 * Returns true if successful, false otherwise.
	 */
	bool Report::save_report(Configuration currConfig) {
		// Declare output file stream and open the file
		ofstream reportFile;
		reportFile.open(currConfig.get_report_path().c_str());
		if (reportFile.fail()) {
			return false;
		}

		// Save records to the report, one at a time
		reportFile << recordList.size() << endl;	// include size of report first

		for (int i = 0; i < recordList.size(); i++) {
			reportFile << recordList[i].device << " ";
			reportFile << recordList[i].blk_read << " ";
			reportFile << recordList[i].blk_read_s << " ";
			reportFile << recordList[i].kb_read_s << " ";
			reportFile << recordList[i].blk_wrtn << " ";
			reportFile << recordList[i].blk_wrtn_s << " ";
			reportFile << recordList[i].kb_wrtn_s << endl;
		}

		reportFile.close();
		return true;
	}

	/**
	 * Loads the report from a file into the recordList.
	 * Returns true if successful, false otherwise.
	 */
	bool Report::load_report(Configuration currConfig) {
		// Variables
		u_int recordListSize;
		Record tempRec;

		// Open the input file stream
		ifstream reportFile;
		reportFile.open(currConfig.get_report_path().c_str());
		if (reportFile.fail()) {
			return false;
		}

		// Load the size of the array first
		reportFile >> recordListSize;

		// Load in all the details of the records
		while (recordListSize > 0 && reportFile >> tempRec.device 
							>> tempRec.blk_read 
							>> tempRec.blk_read_s
							>> tempRec.kb_read_s 
							>> tempRec.blk_wrtn 
							>> tempRec.blk_wrtn_s 
							>> tempRec.kb_wrtn_s) 
		{
			add_record(tempRec);
			recordListSize--;
		}

		reportFile.close();
		return true;
	}

	/**
	 * Prints the report to the user. Must format a table and replace all 0's with N/A
	 */
	void Report::print_report() {
		// Set precision to only 2 decimal places max
		cout.setf(std::ios::fixed);
		cout.setf(std::ios::showpoint);
		cout.precision(2);

		// Initial Check: If list is empty, return
		if (recordList.empty()) {
			cout << "No record found in report!\n";
			return;
		}

		cout << "Any value of 0 will print as 'N/A' to indicate the parameters did not specify for it to be printed. Can also mean that no I/O operations were performed during that test.\n";

		// Print size of record list
		cout << recordList.size() << " records found in report:\n";

		// Set up the table
		cout << "device\tblk_read\tblk_read/s\tkb_read/s\tblk_write\tblk_write/s\tkb_write/s\n";

		// Print out record information, one by one
		for (int i = 0; i < recordList.size(); i++) {
			cout << recordList[i].device << "\t";

			if (recordList[i].blk_read == 0) cout << "N/A\t\t";
			else cout << recordList[i].blk_read << "\t\t";

			if (recordList[i].blk_read_s == 0) cout << "N/A\t\t";
			else cout << recordList[i].blk_read_s << "\t\t";

			if (recordList[i].kb_read_s == 0) cout << "N/A\t\t";
			else cout << recordList[i].kb_read_s << "\t\t";

			if (recordList[i].blk_wrtn == 0) cout << "N/A\t\t";
			else cout << recordList[i].blk_wrtn << "\t\t";

			if (recordList[i].blk_wrtn_s == 0) cout << "N/A\t\t";
			else cout << recordList[i].blk_wrtn_s << "\t\t";

			if (recordList[i].kb_wrtn_s == 0) cout << "N/A\n";
			else cout << recordList[i].kb_wrtn_s << "\n";
		}
	}

} // namespace auDiskTool
