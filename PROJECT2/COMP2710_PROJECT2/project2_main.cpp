// auDiskTool - A Tool for Monitoring Disk Devices 
// Contains the main function
// COMP2710 Project 2
// Mark Gallagher Jr | mag0038@auburn.edu
// Filename: project2_main.cpp
// Written in Vi text editor
// Version: 4/30/2015, v1
// Sources used: Dr. Qin's presentation on Project 2 class designs
// 		 Dr. Qin's presentation on namespaces

#include "project2_tool.h"
using namespace auDiskTool;

int main() {
	// Initialize the tool
	Tool tool;
	tool.init();

	// Run the program
	tool.start();

	// Terminate safely when complete
	tool.exit();

	return 0;
}
