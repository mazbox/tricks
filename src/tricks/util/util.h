/**     ___           ___           ___                         ___           ___     
 *     /__/\         /  /\         /  /\         _____         /  /\         /__/|    
 *    |  |::\       /  /::\       /  /::|       /  /::\       /  /::\       |  |:|    
 *    |  |:|:\     /  /:/\:\     /  /:/:|      /  /:/\:\     /  /:/\:\      |  |:|    
 *  __|__|:|\:\   /  /:/~/::\   /  /:/|:|__   /  /:/~/::\   /  /:/  \:\   __|__|:|    
 * /__/::::| \:\ /__/:/ /:/\:\ /__/:/ |:| /\ /__/:/ /:/\:| /__/:/ \__\:\ /__/::::\____
 * \  \:\~~\__\/ \  \:\/:/__\/ \__\/  |:|/:/ \  \:\/:/~/:/ \  \:\ /  /:/    ~\~~\::::/
 *  \  \:\        \  \::/          |  |:/:/   \  \::/ /:/   \  \:\  /:/      |~~|:|~~ 
 *   \  \:\        \  \:\          |  |::/     \  \:\/:/     \  \:\/:/       |  |:|   
 *    \  \:\        \  \:\         |  |:/       \  \::/       \  \::/        |  |:|   
 *     \__\/         \__\/         |__|/         \__\/         \__\/         |__|/   
 *
 *  Description: 
 */

#pragma once

#include "ofMain.h"
namespace tricks {
	namespace util {
		
		/** draws the framerate in desired colour at the bottom left */
		void drawFramerate(int color = 0xFF0000);
		
		/** 
		 * For packaging mac apps - you need to add the line
		 * cp -r bin/data "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/"
		 * to your "run script build phase"
		 */
		void setDataPathRootToAppContents();
		
		/** Gives you a string time stamp */
		string dateTimeString();
		
		/** Gets the home directory (mac) */
		string getHomeDirectory();
		
		/** Gets you the path to the desktop for mac */
		string getDesktopPath();
		
		/** 
		 * Gets you the path the prefs directory for this app, 
		 * and creates a new one if it doesn't exist. You need
		 * to specify the app name so it knows what to name
		 * the directory.
		 */
		string getPreferencesDirectory(string appName);
		
		/**
		 * Random integer
		 */
		int randInt(int from, int to);
		

		/**
		 * Like modulo but wraps negative numbers back into positive too
		 * e.g. wrap(3, 5) = 5
				wrap(6, 5) = 1
				wrap(-1,5) = 4
		 */
		int wrap(int i, int num);
		
		/**
		 * To time how long something takes, call this before
		 * the thing you want to time, and then endStopwatch()
		 * to stop timing and display the results in the console.
		 */
		void startStopwatch();
		
		/**
		 * Stop the stop watch and prints out the duration to the
		 * console if a label is specified
		 */
		float stopStopwatch(string label = "");
		
		
	}
}