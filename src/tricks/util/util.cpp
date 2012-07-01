#include "ofMain.h"
#include "util.h"

void tricks::util::drawFramerate(int color) {
	ofSetHexColor(color);
	ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, ofGetHeight()-20);
}

void tricks::util::setDataPathRootToAppContents() {
#ifndef _WIN32 
	char path[512];
	getcwd(path, 512);
	string dataRoot = path;
	dataRoot += "/../data/";
	ofSetDataPathRoot(dataRoot);
#endif
}



string padZeros(int t) {
	if(t<10) return ofToString(t);
	else return "0"+ofToString(t);
}
string tricks::util::dateTimeString() {
	return padZeros(ofGetDay())
	+ "." + padZeros(ofGetMonth()) + "." + padZeros(ofGetYear()) + " "
	+ padZeros(ofGetHours()) +"-"+padZeros(ofGetMinutes()) +"-"+
	padZeros(ofGetSeconds());
}


string tricks::util::getHomeDirectory() {
	#ifndef _WIN32 
	FILE *fp = popen("who am I", "r");
	if(fp!=NULL) {
		printf("popen made it\n");
		char name[512];
		string username;
		ofSleepMillis(100);
		if(fgets(name, 512, fp)) {
			printf("fgets\n");
			username = name;
			if(username.find(' ')!=-1) {
				username = username.substr(0, username.find(' '));
				string home = "/Users/"+username;
				return home;
			}
			
		}
		pclose(fp);
	} else {
		printf("Couldn't find user's name, going with default\n");
	}
#else
	printf("getHomeDirectory() not supported on windows yet\n");
#endif
	return "";
}

string tricks::util::getDesktopPath() {
	return getHomeDirectory() + "/Desktop";
}
#include <sys/stat.h>

string tricks::util::getPreferencesDirectory(string appName) {
	
#ifndef _WIN32
	string prefsDir = getHomeDirectory() + "/Library/Preferences/"+appName;
	struct stat stFileInfo; 
	
	// Attempt to get the file attributes 
	if(stat(prefsDir.c_str(),&stFileInfo)!=0) { 
	
		if(mkdir(prefsDir.c_str(), 0777)==0) {
			return prefsDir;
		} else {
			printf("Failed to create preferences directory: %s\n", prefsDir.c_str());
			return "";
		}
	}
#else
	printf("getPreferencesDirectory() not supported on windows yet\n");
	return "";
#endif

}

int tricks::util::randInt(int from, int to) {

	return from + (rand()%(to-from));
}


float tricksUtilStopwatch = 0;
void tricks::util::startStopwatch() {
	tricksUtilStopwatch = ofGetElapsedTimef();
}

float tricks::util::stopStopwatch(string label) {
	float duration = ofGetElapsedTimef() - tricksUtilStopwatch;
	if(label!="") printf("%s duration: %f seconds\n", label.c_str(), duration);
	return duration;
}




int tricks::util::wrap(int i, int num) {
	while(i<0) i += num;
	return i % num;
}