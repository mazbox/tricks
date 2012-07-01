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
 *  QuadWarp.h, created by Marek Bereza on 18/10/2011.
 */

#pragma once

#include "ofMain.h"
namespace tricks {
	namespace gl {
		namespace util {
			
			class ShaderQuadWarp {
			public:
				void setup(int width, int height);
				void begin();
				void end();
				
				
				// ofPoints rather than
				// ofVec2fs to be compatible
				// with ofxSimpleGuiToo's
				// slider2d
				ofPoint tl;
				ofPoint bl;
				ofPoint tr;
				ofPoint br;
				
				private:
					ofFbo fbo;
					ofShader shader;
					void loadShader();
			};
		}
	}
}