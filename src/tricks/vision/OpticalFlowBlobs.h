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
 *  Description: This takes an optical flow image and works out the regions of most movement.
 *				 It takes a parameter threshold which is the movement threshold which must
 *				 be exceeded to cause a blob.
 *
 *				 Use getSites() to get a list of points with the biggest movement.
 *				 
 *  OpticalFlowBlobs.h, created by Marek Bereza on 12/10/2011.
 */

#pragma once
#include "ofxOpenCv.h"
#include "ofxCvOpticalFlowLK.h"

namespace tricks {
	namespace vision {

		class OpticalFlowBlobs {
		public:
			OpticalFlowBlobs();
			void setup(int width, int height);			
			void update(const ofxCvOpticalFlowLK &flow);
			void draw(float x, float y, float width, float height);
			float threshold;
			vector<ofVec2f> getSites();
			
			
		private:
			
			vector<ofVec2f> sites;
			
			// squares of x and y components of optical flow
			IplImage *sqrX;
			IplImage *sqrY;
			
			// square of the magnitude of the optical flow
			ofxCvFloatImage sqrDistFlow;
			
			// 8 bit flowfield magnitude
			ofxCvGrayscaleImage flowMagImg;
			
			// thresholded flowfield magnitude
			ofxCvGrayscaleImage flowThreshImg;
			ofxCvContourFinder contourFinder;
		};
	}
}