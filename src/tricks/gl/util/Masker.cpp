 /**
 * Masker.cpp
 * Masker
 *
 * Created by Marek Bereza on 29/04/2011.
 *
 */

#include "Masker.h"



void Masker::setMask(unsigned char *img, float width, float height, ofVec2f *p) {
	this->pix = img;
	this->bytesPerPixel = 3;
	this->imageWidth = width;
	setPoints(p);
}

ofColor Masker::getCentreColor() {
	return centreColor;
}

void Masker::draw() {
	// we draw a triangle fan to blend the colours
	ofVec2f centre = (points[0]+points[1]+points[2]+points[3])/4;
	centreColor = (colors[0]*0.25+colors[1]*0.25+colors[2]*0.25+colors[3]*0.25);
	// create the fan coords
	for(int i = 0; i < 10; i++) {
		float pos = (float)i/10.f;
		fan[i] = points[0]*(1.f - pos) + points[1]*pos;
		fanColors[i] = getColorFromImage(fan[i]);
		
		fan[i+10] = points[1]*(1.f - pos) + points[2]*pos;
		fanColors[i+10] = getColorFromImage(fan[i+10]);
		
		fan[i+20] = points[2]*(1.f - pos) + points[3]*pos;
		fanColors[i+20] = getColorFromImage(fan[i+20]);
		
		fan[i+30] = points[3]*(1.f - pos) + points[0]*pos;
		fanColors[i+30] = getColorFromImage(fan[i+30]);
	}
	
	glBegin(GL_TRIANGLE_FAN);
	ofSetColor(centreColor);
	glVertex2f(centre.x, centre.y);
	for(int i = 0; i < 40; i++) {
		ofSetColor(fanColors[i]);
		glVertex2f(fan[i].x, fan[i].y);
		
	}
	ofSetColor(fanColors[0]);
	glVertex2f(fan[0].x, fan[0].y);
	glEnd();
	
	
}



ofColor Masker::getColorFromImage(ofVec2f p) {
	int x = p.x;
	int y = p.y;
	int offset = x + y*imageWidth;
	offset *= bytesPerPixel;
	return ofColor(pix[offset],pix[offset+1],pix[offset+2]);
}

void Masker::setPoints(ofVec2f *p) {
	points[0] = p[0];
	points[1] = p[1];
	points[2] = p[2];
	points[3] = p[3];
	
	colors[0] = getColorFromImage(points[0]);
	colors[1] = getColorFromImage(points[1]);
	colors[2] = getColorFromImage(points[2]);
	colors[3] = getColorFromImage(points[3]);
}
