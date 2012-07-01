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
 *				 
 *  CamFluid.h, created by Marek Bereza on 10/10/2011.
 */

#pragma once
#include "ofMain.h"
#include "MSAFluid.h"
#include "ofxOpenCv.h"
#include "ofxCvOpticalFlowLK.h"
namespace tricks {

	namespace vision {
				

		class CamFluid {
		public:
			
			void setup(int width, int height);
			void update(unsigned char *pix, bool rgb = false);
			void draw();
			MSA::FluidSolver fluid;
			ofxCvOpticalFlowLK flow;
			ofxCvGrayscaleImage greyCurr;
		protected:
			bool flipX, flipY;
			
			MSA::FluidDrawerGl drawer;
			
			
			
			ofxCvColorImage colorImg;
			
			ofxCvGrayscaleImage greyPrev;
			
			ofxCvGrayscaleImage diffImg;
			ofxCvGrayscaleImage bgImg;
			ofxCvGrayscaleImage blendImg;
			int width;
			int height;
			
			float blendSpeed;
			void addToFluid(float x, float y, float dx, float dy, bool addColor = true, bool addForce = true);
			void opticalFlowToFluid();
			float aspect2;
		};
	}
}