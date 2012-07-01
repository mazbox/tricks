#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;
#include "tricks/audio/util/WavFileRenderSource.h"

string ofToString(int number) {
	stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();
  } 
  
  string ofToString(float number) {
	stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();
  } 
void printUsage() {
	printf("usage: batch_wav dirname [destdir]\n");
}


bool sorter (const pair<string,float> &a, const pair<string,float> &b) { return (a.second<b.second); }


#define ABS(a) (a>0?a:-a)
float getLoudestPart(float *data, int length) {
	float max = 0;
	for(int i = 0; i < length; i++) {
		if(ABS(data[i])>max) max = ABS(data[i]);
	}
	return max;
}

float getSum(float *data, int length) {
	float sum = 0;
	for(int i = 0; i < length; i++) {
		sum += ABS(data[i]);
	}
	return sum;
}
int main(int argc, const char* argv[]) {
//	printf("%d\n", argc);
	if(argc!=2) {
		printUsage();
		return 1;
	}

	vector<pair<string, float> > files;
	DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(argv[1])) == NULL) {
        cout << "Error(" << errno << ") opening " << argv[1] << endl;
        return errno;
    }
    
    while ((dirp = readdir(dp)) != NULL) {
    	string s = string(dirp->d_name);
    	if(s.find(".wav")!=-1) {
	        files.push_back(make_pair(s, 0));
	    }
    }
    closedir(dp);
    
    for(int i = 0; i < files.size(); i++) {
    	WavFile wf;
    	wf.load(string(argv[1]) + "/" + files[i].first);
		float loudest = getSum(wf.data, wf.getLength());
		files[i].second = loudest;
    	cout << files[i].first <<  "    loudest " << ofToString(loudest) << endl;
    }
    
    sort(files.begin(), files.end(), sorter);
    
    for(int i = 0; i < files.size(); i++) {
    	cout << "              " << files[i].first << "     loud: " << ofToString(files[i].second) << endl;
    	WavFile wf;
    	wf.load(string(argv[1]) + "/" + files[i].first);
    	wf.save(string(argv[1]) + "/out-" + ofToString(i) + ".wav");
    }
    
	WavFileRenderSource src;
	//src.load();
	return 0;
}