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
 *  Description: 
 */
//  Created by Marek Bereza on 14/07/2011.
//
#pragma once

#include "ofMain.h"
// This takes points from an ellipse
namespace tricks {
	namespace math {

		class Ellipse {
		public:
		
			// create an ellipse with points
			bool create(vector<ofVec2f> &points);
			void draw();
		
		
			// these are the parameters of the ellipse
		
			// the centre
			ofVec2f centre;
		
			// the width at the widest point
			float major;
		
			// the width at the narrowest point
			float minor;
		
			// what angle the widest point is to the horizontal
			// in degrees(!)
			float angle;
			
			
			// calculates and returns four points (in a loop)
			// of the angle-aligned bounding box of the ellipse.
			// Pass in 4 ofVec2f's.
			void getAABB(ofVec2f *points);
			
			ofRectangle boundingBox;
			
			// how much deviation there is from the initial contour points
			// and the ellipse that it describes.
			// the units are in pixels, so the smaller the better.
			float averageError;
			float maxError;
			float getError(float x, float y) ;
		private:
			double conicCoefficients[7];
			void calcEllipse(vector<ofVec2f> &points);
			void calculateError(vector<ofVec2f> &points);
			ofVec2f maxxy;
		};
	}
}