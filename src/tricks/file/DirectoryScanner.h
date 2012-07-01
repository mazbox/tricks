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
 *				 
 *  DirectoryScanner.h, created by Marek Bereza on 29/11/2011.
 */


#include "ofMain.h"

namespace tricks {
	namespace file {
		class DirectoryScanner {
		public:
			void addExtension(string ext) {
				extensions.push_back(ofToLower(ext));
			}
			
			void scan(string directory) {
				ofDirectory dir;
				int numItems = dir.listDir(directory);
				for(int i = 0; i < numItems; i++) {
					//printf("%s\n",dir.getName(i).c_str());
					ofFile f = dir.getFile(i);
					if(f.isDirectory()) {
						scan(f.path());
					} else {
						for(int i = 0; i < extensions.size(); i++) {
							if(ofToLower(f.getExtension())==extensions[i]) {
								results.push_back(f.path());
								break;
							}
						}
					}
				}

			}

			vector<string> results;
			
		private:
			vector<string> extensions;
		};
	}
}