/**
 *  CamFluid.cpp
 *
 *  Created by Marek Bereza on 10/10/2011.
 */
#include "ofxSimpleGuiToo.h"

#include "CamFluid.h"
void tricks::vision::CamFluid::setup(int width, int height) {
	greyCurr.allocate(width, height);
	greyPrev.allocate(width, height);
	
	blendImg.allocate(width, height);
	bgImg.allocate(width, height);
	diffImg.allocate(width, height);
	
	flow.allocate(width, height);
	this->width = width;
	this->height = height;
	colorImg.allocate(width, height);

	// setup fluid stuff
	fluid.setup(100, 100);
	
   	fluid.enableRGB(false).setFadeSpeed(0.01).setDeltaT(0.5).setVisc(0.00017).setColorDiffusion(0.00011);
	drawer.setup(&fluid);
	
	// aspect ratio squared
	aspect2 = (float)ofGetWidth()/(float)ofGetHeight();
	aspect2 *= aspect2;
	blendSpeed = 0.9;
	flipX = false;
	flipY = false;
	gui.addToggle("FlipX", flipX);
	gui.addToggle("FlipY", flipY);
	gui.addContent("Cam", greyCurr);
	gui.addTitle("Fluid");
	gui.addContent("Fluid Image", drawer);
	gui.addSlider("viscocity", fluid.viscocity, 0.00001, 0.0001);
	gui.addSlider("Fade Speed", fluid.fadeSpeed, 0.01, 0.1);
	gui.addToggle("wrapX", fluid.wrap_x);
	gui.addSlider("deltaT", fluid.deltaT, 0.01, 0.1);
	gui.addSlider("solver iterations", fluid.solverIterations, 2, 15);
	gui.addSlider("Diffusion", fluid.colorDiffusion, 0.0, 0.0015 );
	gui.addSlider("Blend Speed", blendSpeed, 0.7, 0.99);
	
}

void tricks::vision::CamFluid::update(unsigned char *pix, bool rgb) {
	if(pix==NULL) return;
	if(rgb) {
		colorImg.setFromPixels(pix, width, height);
		greyCurr = colorImg;

	} else {
		greyCurr.setFromPixels(pix, width, height);
	}

	
	greyCurr.mirror(flipY, flipX);	
	

	flow.calc(greyPrev, greyCurr, 1);
	flow.blur(3);
	greyPrev = greyCurr;
	opticalFlowToFluid();
	fluid.update();
	
	diffImg.absDiff(greyCurr, bgImg);
	
	blendImg = greyCurr;
	blendImg.convertToRange(0, 255*(1.f-blendSpeed));
	bgImg.convertToRange(0, 255*(blendSpeed));
	bgImg += blendImg;
	
}

void tricks::vision::CamFluid::draw() {
	
	//flow.draw(0, 0, ofGetWidth(), ofGetHeight());
	//ofSetHexColor(0x0077CC);
	//drawer.draw(0, 0, ofGetWidth(), ofGetHeight());
	ofSetHexColor(0xFFFFFF);
	diffImg.draw(0,0,ofGetWidth(), ofGetHeight());
}

void tricks::vision::CamFluid::opticalFlowToFluid() {

	int								x, y;
	float							dx, dy;

	float iw					= 1.0f/flow.captureWidth;
	float iy					= 1.0f/flow.captureHeight;

	int particleEmitCounter		= 0;
	float flowThreshold			= 10;
	float opticalFlowFluidMult	= 0.01;
	float multX					= (float)ofGetWidth()/flow.captureWidth;
	float multY					= (float)ofGetHeight()/flow.captureHeight;

	for ( y = 0; y < flow.captureHeight; y+=flow.captureRowsStep ){
		for ( x = 0; x < flow.captureWidth; x+=flow.captureColsStep ){
			
			dx					= cvGetReal2D( flow.vel_x, y, x );
			dy					= cvGetReal2D( flow.vel_y, y, x );
			if(dx*dx+dy*dy > flowThreshold) {
				
				addToFluid((float)x/flow.captureWidth, (float)y/flow.captureHeight, dx*opticalFlowFluidMult, dy*opticalFlowFluidMult);
				
			}
		}
	}
}


void tricks::vision::CamFluid::addToFluid(float x, float y, float dx, float dy, bool addColor, bool addForce) {
	
	float speed = dx * dx  + dy * dy * aspect2;
	
	//cout << dx << " " << dy << endl;
	
    if(speed > 0) {
		
        if(x<0) x = 0;
        else if(x>1) x = 1;
        if(y<0) y = 0;
        else if(y>1) y = 1;
		
        float colorMult = 50;
        float velocityMult = 30;
		
        int index = fluid.getIndexForPos(MSA::Vec2f(x, y));
		
		
		
		
		//APPSETTINGS - color picker from global variables
		if(addColor) {
			MSA::Color c(1,1,1);
			fluid.addColorAtIndex(index, c);
		
		
			
		}
		
		if(addForce) {
			MSA::Vec2f f(dx * velocityMult, dy * velocityMult);
			fluid.addForceAtIndex(index, f);
		}
		
	}
	
	
}
