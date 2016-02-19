// auDiskTool - A Tool for Monitoring Disk Devices 
// Implementation for Tool class 
// COMP2710 Project 2
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: project2_tool.cpp
// Written in Vi text editor
// Version: 4/30/2015, v1
// Sources used: Dr. Qin's presentation on Project 2 class designs
// 		 Dr. Qin's presentation on namespaces
// 		 StackOverflow forums for sleep() delay function info
// 		 StackOverflow forums to place instream back to start of diskstats file

#include "project2_tool.h"

namespace auDiskTool {

	/**
	 * Default constructor used for tool
	 */
	Tool::Tool() {};

	/**
	 * Initialization function. Opens appropiate files and loads
	 * in the default configurations and data.
	 * Also welcomes the user :)
	 */
	void Tool::init() {
		// All three objects in Tool already called constructors at runtime.
		// Load the configuration from the default conf file
		if (!config.load_conf()) {
			cout << "WARNING: could not load default .conf file \"" << CONFIG_FILENAME
				<< "\". Using default configuration instead\n";
		}

		// Load the report from the default report filename spec'd in config
		if (!report.load_report(config)) {
			cout << "WARNING: Default report file not found. A new file will be"
				<< " made after exectuing \"run\" command once\n";
		}

		// Open the diskstat file (ONLY ONCE) to prepare for data gathering.
		// File will be closed upon execution of Tool::exit()
		diskstatStream.open("/proc/diskstats");
		if (!diskstatStream.is_open()) {
			cout << "FATAL ERROR: Could not open \"/proc/diskstats\" file!"
				<< " Program cannot function without file and must terminate\n";
			exit();
		}

		// Display welcome message
		cout << "Welcome to auDiskTool, v1.0.\nFor list of commands, type \'help\'\n";
	}

	/**
	 * Runs the program. Handles the loop-until EXIT is entered. Coordinates
	 * function calls.
	 */
	void Tool::start() {
		// Retrieve the user's first command
		cmdLine.get_command();

		// Start program loop
		while (cmdLine.get_type() != EXIT) {
			// Respond to the user's command
			respond_cmd();
			// Get next command
			cmdLine.get_command();
		}
	}	

	/**
	 * Handles exiting the program properly. This includes closing files, saving
	 * the configuration (if it was changed), and saying goodbye.
	 */
	void Tool::exit() {
		// Call function to save configuration. IF config was edited, notify user
		if (config.save_conf()) {
			cout << "Configuration was changed. File \"" << CONFIG_FILENAME << "\" was updated successfully.\n";
		}

		// Check if diskstat is still open. If so, close it.
		if (diskstatStream.is_open()) {
			diskstatStream.close();
		}

		// Say goodbye to the user
		cout << "Goodbye, user. End of Line_\n";
	} 

	/**
	 * Displays help information to the user
	 */
	void Tool::help() {
		// Display help information, line-by-line
		cout << "run - run the monitoring tool\n";
		cout << "set interval [value] - set sampling period (in seconds) to [value]\n";
		cout << "set count [value] - set number of records to save to [value]\n";
		cout << "set report [name] - set the report filename to [name]\n";
		cout << "set blk_read\t\t[0|1] - set print_blk_read to 0 (IGNORE) or 1 (RECORD)\n";
		cout << "set blk_read/s\t\t[0|1] - set print_blk_read/s to 0 (IGNORE) or 1 (RECORD)\n";
		cout << "set kb_read/s\t\t[0|1] - set print_kb_read/s to 0 (IGNORE) or 1 (RECORD)\n";
		cout << "set blk_write\t\t[0|1] - set print_blk_wrtn to 0 (IGNORE) or 1 (RECORD)\n";
		cout << "set blk_write/s\t\t[0|1] - set print_blk_wrtn/s to 0 (IGNORE) or 1 (RECORD)\n";
		cout << "set kb_write/s\t\t[0|1] - set print_kb_wrtn/s to 0 (IGNORE) or 1 (RECORD)\n";
		cout << "print conf - display current paramter configuration\n";
		cout << "print report - display current contents of the record file\n";
		cout << "save - if configuration has changed, saves audisktool.conf. Note: File is saved upon exit as well\n";
		cout << "exit - exit the tool\n";
	}

	/**
	 * Responsible for handling a command input. Redirects program flow
	 * according to whatever is specified by the user in the command line
	 */
	void Tool::respond_cmd() {
		// Switch case depending on command type and flags (if applicable)
		switch (cmdLine.get_type()) {
			case RUN:
				run();
				break;
			case SET:
				if (!config.set_parameter(cmdLine)) {
					cout << "Parameter was already set to desired value, not changed.\n";
				}
				// Check if report path was changed, if so, clear current records
				else {
					if (cmdLine.get_flag() == REPORT) {
						report.clear_report();
						cout << "New report file detected: Clearing current contents for new report.\n";
						if (report.load_report(config)) {
							cout << "Program detected existing report at specified location. Contents loaded into program.\n";
						}
					}
				}
				break;
			case PRINT:
				switch (cmdLine.get_flag()) {
					case CONF:
						config.print_conf();
						break;
					case REPORT:
						report.print_report();
						break;
				}
				break;
			case SAVE:
				if (config.save_conf()) {
					cout << "Configuration saved successfully.\n";
				}
				else {
					cout << "ERROR: Could not save conf file.";

					// Check status of changed flag
					if (!config.get_flag_state(FLAG_CLEARED)) {
						cout << " Configuration was not changed since last saved.\n";
					}
					else {
						cout << " File I/O error.\n";
					}
				}
				break;
			case HELP:
			default:
				help();
				break;
		} // switch (cmdLine.get_type())
	}

	/**
	 * Executes the RUN action. 
	 */
	void Tool::run() {
		// Declare variables
		Record tempRec;	// hold records to be added, 1 at a time
		
		// Display the current parameters to be used
		config.print_conf();
		cout << "Please wait. Based on interval given, tool should complete in about " 
			<< (config.get_count() * config.get_interval()) << " seconds...\n";
		
		// Run parse_diskstat() once to get values for lastSectsRead/Wrtn set
		parse_diskstat();	
	
		// Begin main sampling loop
		for (u_int i = 0; i < config.get_count(); i++) {
			sleep(config.get_interval());	// sleep for interval seconds 
			tempRec = parse_diskstat();	// query diskstat for 1 record on sda only
			report.add_record(tempRec);	// add record to the report
		}
	
		// Run completed, save the report to disk
		if (report.save_report(config)) {
			cout << "\nThe file \"" << config.get_report_path() << "\" has been updated.\n";
		}
		else {
			cout << "\nERROR: Could not save report to \"" << config.get_report_path() << "\"\n";
		}
	}

	/**
	 * Parses the diskstat file to obtain info for device "sda"
	 * This info is then converted into useful information and saved into a Record struct
	 * This Record struct is pre-filtered according to the flags in config
	 * NOTE: ASSUMES SECTOR SIZE ON THIS SYSTEM IS 512 BYTES
	 */
	Record Tool::parse_diskstat() {
		// Variables
		unsigned long sectsRead, sectsWrtn;
		unsigned long deltaSectsRead, deltaSectsWrtn;
		int strIndex;
		string dataLine = "";
		Record resultRec = {0, 0.0, 0.0, 0, 0.0, 0.0, ""};

		// Get the line containing data needed
		// Continue until a line with sda is found
		getline(diskstatStream, dataLine);
		while ((strIndex = dataLine.find("sda")) == string::npos) {
			getline(diskstatStream, dataLine);
		}

		// Extract device ID and store it in the record
		dataLine = dataLine.substr(strIndex);
		strIndex = dataLine.find(" "); // find the space delimiter between device and data
		resultRec.device = dataLine.substr(0, strIndex);
		dataLine = dataLine.substr(strIndex + 1);	// remove device info from data string

		// Parse the number of sectors read (FIELD 3)/wrtn (FIELD 7) as given by diskstats
		for (int i = 0; i < 2; i++) {
			strIndex = dataLine.find(" ");
			dataLine = dataLine.substr(strIndex + 1);	// remove irrelevant data
		}
		strIndex = dataLine.find(" ");
		istringstream sectsReadBuffer(dataLine.substr(0, strIndex));
		sectsReadBuffer >> sectsRead;
		
		for (int i = 0; i < 4; i++) {
			strIndex = dataLine.find(" ");
			dataLine = dataLine.substr(strIndex + 1);	// remove irrelevant data
		}	
		strIndex = dataLine.find(" ");
		istringstream sectsWrtnBuffer(dataLine.substr(0, strIndex));
		sectsWrtnBuffer >> sectsWrtn;

		// Calculate difference from measurements only once
		deltaSectsRead = sectsRead - lastSectsRead;
		deltaSectsWrtn = sectsWrtn - lastSectsWrtn;

		// Using newly parsed values, calculate desired parameters
		if (config.get_flag_state(BLK_READ)) {
			resultRec.blk_read = (u_int)(deltaSectsRead);
		}	
		if (config.get_flag_state(BLK_READ_S)) {
			resultRec.blk_read_s = (static_cast<double>(deltaSectsRead)) / config.get_interval();
		}
		if (config.get_flag_state(KB_READ_S)) {
			resultRec.kb_read_s = (static_cast<double>(deltaSectsRead)) / (2 * config.get_interval());
		}
		if (config.get_flag_state(BLK_WRTN)) {
			resultRec.blk_wrtn = (u_int)(deltaSectsWrtn);
		}
		if (config.get_flag_state(BLK_WRTN_S)) {
			resultRec.blk_wrtn_s = (static_cast<double>(deltaSectsWrtn)) / config.get_interval();
		}
		if (config.get_flag_state(KB_WRTN_S)) {
			resultRec.kb_wrtn_s = (static_cast<double>(deltaSectsWrtn)) / (2 * config.get_interval());
		}

		// Reset ops for the next reading
		lastSectsRead = sectsRead;
		lastSectsWrtn = sectsWrtn;

		// Place 'cursor' back to start of file
		diskstatStream.clear();
		diskstatStream.seekg(0, diskstatStream.beg);

		return resultRec;
	}

} // namespace auDiskTool
