/**
 *  OpticalFlowBlobs.cpp
 *
 *  Created by Marek Bereza on 12/10/2011.
 */

#include "OpticalFlowBlobs.h"

tricks::vision::OpticalFlowBlobs::OpticalFlowBlobs() {
	threshold = 50;
}
void tricks::vision::OpticalFlowBlobs::setup(int width, int height) {
	sqrX			= cvCreateImage(cvSize(width, height), IPL_DEPTH_32F, 1);
	sqrY			= cvCreateImage(cvSize(width, height), IPL_DEPTH_32F, 1);
	sqrDistFlow		.allocate(width, height);	
	
	flowThreshImg	.allocate(width, height);	
	flowMagImg	.allocate(width, height);	

}


void tricks::vision::OpticalFlowBlobs::update(const ofxCvOpticalFlowLK &flow) {
	// square the x and y components of the optical flow
	cvMul(flow.vel_x, flow.vel_x, sqrX);
	cvMul(flow.vel_y, flow.vel_y, sqrY);
	
	// add them together
	cvAdd(sqrX, sqrY, sqrDistFlow.getCvImage());
	
	
	// convert to 8 bit
	cvConvertScale(sqrDistFlow.getCvImage(), flowMagImg.getCvImage(), 1, 0);
	
	// copy for debug
	flowThreshImg = flowMagImg;
	

	// threshold
	flowThreshImg.threshold(threshold);
	
	// find contours
	contourFinder.findContours(flowThreshImg, 25, 320*240, 70, false, true);
	

}

vector<ofVec2f> tricks::vision::OpticalFlowBlobs::getSites() {
	sites.clear();
	for(int i =0 ; i < contourFinder.blobs.size(); i++) {
		sites.push_back(contourFinder.blobs[i].centroid);
	}
	return sites;
}

void tricks::vision::OpticalFlowBlobs::draw(float x, float y, float width, float height) {
	flowThreshImg.draw(x,y,width,height);
	contourFinder.draw(x, y, width, height);
}