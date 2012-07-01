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
 *  Accumulator.h, created by Marek Bereza on 10/10/2011.
 */

// this doesn't really do anything right now.


class Accumulator {
public:
	void setup(int width, int height) {
		fbo1.allocate(width, height, GL_RGBA);
		fbo2.allocate(width, height, GL_RGBA);
		fbo3.allocate(width, height, GL_RGBA);
		bg = &fbo1;
		fg = &fbo2;
	}
	
	ofFbo *bg;
	ofFbo *fg;
	
	void begin() {
		fg->begin();
		ofClear(0, 0, 0, 0);
	}
	
	void end() {
		fg->end();
		
	
	}
	
	ofFbo fbo1;
	ofFbo fbo2;
	ofFbo fbo3;
};