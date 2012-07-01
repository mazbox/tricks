/**
 *  DataRecorder.cpp
 *
 *  Created by Marek Bereza on 10/10/2011.
 */

#include "DataRecorder.h"

bool floatStringPairSorter(const pair<float,string> &a, const pair<float,string> &b) {
	return a.first < b.first;
}

void tricks::util::DataRecorder::record(float time, string data) {
	entries.push_back(make_pair(time,data));
}

void tricks::util::DataRecorder::save(string file) {
	sort(entries.begin(), entries.end(), &floatStringPairSorter);
	ofstream myfile;
	myfile.open (file.c_str());
	for(int i = 0; i < entries.size(); i++) {
		myfile << ofToString(entries[i].first) << " " << entries[i].second << endl;
	}
	myfile.close();
}