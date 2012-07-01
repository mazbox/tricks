/**
 *  MidiPointer.cpp
 *
 *  Created by Marek Bereza on 22/07/2011.
 */

#include "MidiPointer.h"

bool MidiPointer::midiIsSetup = false;
ofxMidiIn MidiPointer::midiIn;

enum MidiPointerType {
	MidiPointerType_INT,
	MidiPointerType_FLOAT,
	MidiPointerType_BOOL
};

struct MidiPointerVar {
	MidiPointerVar() {}
	MidiPointerVar(MidiPointerType type, float min, float max, void *ptr) {
		this->type = type;
		this->min = min;
		this->max = max;
		this->ptr = ptr;
	}
	MidiPointerType type;
	float min;
	float max;
	void *ptr;
};

map<int,MidiPointerVar> midiPointers;

void MidiPointer::point(int note, bool &var) {
	if(!midiIsSetup) setupMidi();
	midiPointers[note] = MidiPointerVar(MidiPointerType_BOOL, 0, 1, (void*)&var);
}

void MidiPointer::point(int cc, float &var, float min, float max) {
	if(!midiIsSetup) setupMidi();
	midiPointers[cc] = MidiPointerVar(MidiPointerType_FLOAT, min, max, (void*)&var);
}

void MidiPointer::point(int cc, int &var, int min, int max) {
	if(!midiIsSetup) setupMidi();
	midiPointers[cc] = MidiPointerVar(MidiPointerType_INT, min, max, (void*)&var);
}


class MidiPointerListener: public ofxMidiListener {
public:
	void newMidiMessage(ofxMidiEventArgs& eventArgs) {
		printf("Message received: %d %d %d\n", eventArgs.status, eventArgs.byteOne, eventArgs.byteTwo);
		if(eventArgs.status==144) { // note on
			int id = eventArgs.byteOne;
			
			if(midiPointers.find(id)!=midiPointers.end()) {
				if(midiPointers[id].type==MidiPointerType_BOOL) {
					bool *v = (bool*)midiPointers[id].ptr;
					(*v) = !(*v);
				}
			}
		} else if(eventArgs.status==128) { // note off
		} else if(eventArgs.status==176) { // cc
			int id = eventArgs.byteOne;
			int value = eventArgs.byteTwo;
			if(midiPointers.find(id)!=midiPointers.end()) {
				if(midiPointers[id].type==MidiPointerType_FLOAT) {
					float *v = (float*)midiPointers[id].ptr;
					(*v) = ofMap(value, 0, 127, midiPointers[id].min, midiPointers[id].max);
				} else if(midiPointers[id].type==MidiPointerType_INT) {
					int *v = (int*)midiPointers[id].ptr;
					(*v) = ofMap(value, 0, 127, midiPointers[id].min, midiPointers[id].max);
				}
			}
		}
//		if(eventArgs.by
	}
};
MidiPointerListener midiPointerListener;

void MidiPointer::setupMidi(int port) {

	printf("Setting up midi on port %d\n", port);
//	midiIn.setVerbose(true);
	midiIn.listPorts();
	midiIn.openPort(port);
	midiIn.addListener(&midiPointerListener);
	midiIsSetup = true;
}



	
