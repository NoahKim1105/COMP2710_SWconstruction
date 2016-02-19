// auDiskTool - A Tool for Monitoring Disk Devices 
// Implementation for Configuration class 
// COMP2710 Project 2
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: project2_configuration.cpp
// Written in Vi text editor
// Version: 4/30/2015, v1
// Sources used: Dr. Qin's presentation on Project 2 class designs
// 		 Dr. Qin's presentation on namespaces

#include "project2_configuration.h"

namespace auDiskTool {

	/**
	 * Constructor: initializes configuration to default values
	 */
	Configuration::Configuration() {
		interval = 1;
		count = 10;
		blkReadFlag = true;
		blkReadSFlag = true;
		kbReadSFlag = true;
		blkWrtnFlag = true;
		blkWrtnSFlag = true;
		kbWrtnSFlag = true;
		changed = false;

		reportPath = "report.adt";	
	}

	/**
	 * Prints out the current configuration to the user
	 */
	void Configuration::print_conf() {
		// Start with the interval and count params
		cout << "Monitoring time = " << interval << " seconds, Number of records = " << count << ",\n";
		
		// Print flag states
		cout << "print_blk_read = " << (blkReadFlag ? "1" : "0") << ", ";
		cout << "print_blk_read/s = " << (blkReadSFlag ? "1" : "0") << ", ";
		cout << "print_kb_read/s = " << (kbReadSFlag ? "1" : "0") << ",\n";
		cout << "print_blk_write = " << (blkWrtnFlag ? "1" : "0") << ", ";
		cout << "print_blk_write/s = " << (blkWrtnSFlag ? "1" : "0") << ", ";
		cout << "print_kb_write/s = " << (kbWrtnSFlag ? "1" : "0") << ",\n";

		// Print report path
		cout << "report file name = '" << reportPath << "'" << endl;
	}

	/**
	 * Getter for report path
	 */
	string Configuration::get_report_path() {
		return reportPath;
	}

	/**
	 * Getter for interval
	 */
	u_int Configuration::get_interval() {
		return interval;
	}

	/**
	 * Getter for count
	 */
	u_int Configuration::get_count() {
		return count;
	}

	/**
	 * Getter for flag states
	 */
	bool Configuration::get_flag_state(flag_t flagSelect) {
		switch (flagSelect) {
			case BLK_READ:
				return blkReadFlag;
			case BLK_READ_S:
				return blkReadSFlag;
			case KB_READ_S:	
				return kbReadSFlag;
			case BLK_WRTN:
				return blkWrtnFlag;
			case BLK_WRTN_S:
				return blkWrtnSFlag;
			case KB_WRTN_S:
				return kbWrtnSFlag;
			default:
				return changed;
		} // switch (flagSelect)
	}

	/**
	 * Sets a parameter
	 */
	bool Configuration::set_parameter(CommandLine paramToChange) {
		// Change parameter depending on flag specified by the user
		switch (paramToChange.get_flag()) {
			case INTERVAL:
				if (paramToChange.get_value() != interval) {
					interval = paramToChange.get_value();
					changed = true;
					cout << "Interval changed to " << interval << "\n";
					return true;
				}
				break;
			case COUNT:
				if (paramToChange.get_value() != count) {
					count = paramToChange.get_value();
					changed = true;
					cout << "Count changed to " << count << "\n";
					return true;
				}
				break;
			case REPORT:
				if (paramToChange.get_str_value() != reportPath) {
					reportPath = paramToChange.get_str_value();
					// do not change "changed" to true: doesn't affect saving file if report is changed
					cout << "Report path changed to '" << reportPath << "'\n";
					return true;
				}
				break;
			case BLK_READ:
				if (paramToChange.get_value() != blkReadFlag) {
					blkReadFlag = paramToChange.get_value();
					changed = true;
					cout << "blk_read changed to " << blkReadFlag << "\n";
					return true;
				}
				break;
			case BLK_READ_S:
				if (paramToChange.get_value() != blkReadSFlag) {
					blkReadSFlag = paramToChange.get_value();
					changed = true;
					cout << "blk_read/s changed to " << blkReadSFlag << "\n";
					return true;
				}
				break;
			case KB_READ_S:
				if (paramToChange.get_value() != kbReadSFlag) {
					kbReadSFlag = paramToChange.get_value();
					changed = true;
					cout << "kb_read/s changed to " << kbReadSFlag << "\n";
					return true;
				}
				break;
			case BLK_WRTN:
				if (paramToChange.get_value() != blkWrtnFlag) {
					blkWrtnFlag = paramToChange.get_value();
					changed = true;
					cout << "blk_write changed to " << blkWrtnFlag << "\n";
					return true;
				}
				break;
			case BLK_WRTN_S:
				if (paramToChange.get_value() != blkWrtnSFlag) {
					blkWrtnSFlag = paramToChange.get_value();
					changed = true;
					cout << "blk_write/s changed to " << blkWrtnSFlag << "\n";
					return true;
				}
				break;	
			case KB_WRTN_S:
				if (paramToChange.get_value() != kbWrtnSFlag) {
					kbWrtnSFlag = paramToChange.get_value();
					changed = true;
					cout << "kb_write/s changed to " << kbWrtnSFlag << "\n";
					return true;
				}
				break;
			default:
				break;
		} // switch (paramToChange.get_flag())
		
		return false;
	}

	/**
	 * Saves the configuration file ONLY if the changed flag == TRUE
	 */
	bool Configuration::save_conf() {
		// First check if file should be saved:
		if (changed == false) {
			return false;
		}

		// Open the file
		ofstream confFile;
		confFile.open(CONFIG_FILENAME.c_str());
		if (confFile.fail()) {
			return false;
		}

		// Save configuration into the file
		confFile << interval << " " << count << " ";
		confFile << (blkReadFlag ? 1 : 0) << " ";
		confFile << (blkReadSFlag ? 1 : 0) << " ";
		confFile << (kbReadSFlag ? 1 : 0) << " ";
		confFile << (blkWrtnFlag ? 1 : 0) << " ";
		confFile << (blkWrtnSFlag ? 1 : 0) << " ";
		confFile << (kbWrtnSFlag ? 1 : 0) << "\n";

		// Close file
		confFile.close();
		changed = false;	// change flag back to false to prevent double-writes
		return true;
	}

	/**
	 * Loads the configuration file
	 */
	bool Configuration::load_conf() {
		// Open the file
		ifstream confFile;
		confFile.open(CONFIG_FILENAME.c_str());
		if (confFile.fail()) {
			return false;
		}

		// Load configuration from the file into the appropiate flags
		confFile >> interval >> count >> blkReadFlag >> blkReadSFlag >> kbReadSFlag
			>> blkWrtnFlag >> blkWrtnSFlag >> kbWrtnSFlag;

		// Close file
		confFile.close();
		return true;
	}

} // namespace auDiskTool
