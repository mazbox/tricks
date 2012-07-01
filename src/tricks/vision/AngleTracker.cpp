/**
 *  AngleTracker.cpp
 *
 *  Created by Marek Bereza on 25/08/2011.
 */

#include "AngleTracker.h"
#include "ofMain.h"

tricks::vision::AngleTracker::AngleTracker() {
	lastTimeTrackedAngle = -1000;
	lastAngle = -1000;
	useRadians = false;
}
float tricks::vision::AngleTracker::track(float angle) {
	float currTime = ofGetElapsedTimef();
    if(currTime - lastTimeTrackedAngle>0.2) {
        // start tracking
        lastAngle = angle;
        lastTimeTrackedAngle = currTime;
        return angle;
    } else {
        lastTimeTrackedAngle = currTime;
		if(useRadians) angle = ofRadToDeg(angle);
        if(abs(ofWrapDegrees(angle-lastAngle))>90) {
            angle += 180;
        }
        lastAngle = angle;
		if(useRadians) return ofDegToRad(angle);
        else return angle;
    }
}

void tricks::vision::AngleTracker::usingRadians(bool useRadians) {
	this->useRadians = useRadians;
}
