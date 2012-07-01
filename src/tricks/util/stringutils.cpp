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
#include "stringutils.h"

string tricks::util::stringutils::getStringInString(string in, string before, string after) {
	if(in.length()>before.length()+after.length()) {
		int start = in.find(before);
		if(start==-1) {
			printf("Couldn't find '%s' in '%s'\n", before.c_str(), in.c_str());
			return "";
		}
		start += before.length();
		
		int end = in.find(after);
		if(end<start) {
			printf( "There is an instance of '%s' before '%s' in '%s'. Can't do getStringInString\n", 
				   after.c_str(), before.c_str(), in.c_str());
			return "";
		}
		return in.substr(start, end-start);
	} else {
		printf("Not enough characters in '%s' to do stringInString\n", in.c_str());
		return "";
	}
}
