/**
 *  DataPlayer.cpp
 *
 *  Created by Marek Bereza on 10/10/2011.
 */

#include "DataPlayer.h"
tricks::util::DataPlayer::DataPlayer() {
	listener = NULL;
	playhead = 0;
}

void tricks::util::DataPlayer::setListener(DataPlayerListener *listener) {
	this->listener = listener;

}

void tricks::util::DataPlayer::load(string file) {
	
	
	string STRING;
	ifstream infile;
	infile.open (file.c_str());
	while(!infile.eof()) // To get you all the lines.
	{
		getline(infile,STRING); // Saves the line in STRING.
		if(STRING!="") {
			vector<string> s = ofSplitString(STRING, " ");
			entries.push_back(pair<float,string>());
			entries.back().first = ofToFloat(s[0]);
			s.erase(s.begin());
			entries.back().second = ofJoinString(s, " ");
		}
	}
	infile.close();
	
	printf("Read %d entries\n", entries.size());
	start();
}

void tricks::util::DataPlayer::start() {
	playhead = 0;
}

void tricks::util::DataPlayer::update(float playheadTime) {
	if(listener==NULL) return;
	
	while(playhead<entries.size() && entries[playhead].first<=playheadTime) {
		listener->dataPlayerCallback(entries[playhead].first, entries[playhead].second);
		playhead++;
	}
}
