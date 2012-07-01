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
 * Description: 
 *
 * Centerer.h
 *
 * Centers and scales opengl content within an area to fill
 * the screen.
 *
 * You set this up with your desired resolution, then you 
 * do your drawing between begin() and end(). You also send 
 * all your 
 *
 * Created by Marek Bereza on 19/07/2011.
 *
 */
#pragma once

#include "ofMain.h"

namespace tricks { 
    namespace gl {
        namespace util {
    

            class Centerer {
            public:
                
				enum CentererMode {
					FILL_HEIGHT,
					FILL_WIDTH
				};
				
                /**
                 * You pass in here the dimensions you want to draw with.
                 * E.g. if your screen was 1440x900 and you wanted
                 * to draw to 1024x768 scaled and centered to the screen
                 * call setup(1024, 768);
                 */
                void setup(float width, float height, CentererMode mode = FILL_HEIGHT) {
                    this->mode = mode;
//                    bool fullscreen = ofGetWindowMode()==OF_FULLSCREEN;
                    float actualWidth = ofGetWidth();
                    float actualHeight = ofGetHeight();
                    this->width = width;
                    this->height = height;
					
					if(mode==FILL_HEIGHT) {
						fakeGameModeScale = (float)actualHeight/height;
						float resizedScreenWidth = (float)actualWidth/fakeGameModeScale;
						offset = ofVec2f((resizedScreenWidth - width)/2, 0);
					} else {
						fakeGameModeScale = (float) actualWidth/width;
						float resizedScreenHeight = (float) actualHeight/fakeGameModeScale;
						offset = ofVec2f(0, (resizedScreenHeight - height)/2);
					}
                }
                
                void begin() {
                    // do a fake OF_GAME_MODE - the real one locks up the computer when it crashes
                    glPushMatrix();
                    glScalef(fakeGameModeScale, fakeGameModeScale, fakeGameModeScale);
                    glTranslatef(offset.x, offset.y, 0);
                }
				
				
                
                void end() {
                    ofSetHexColor(0);
                    // letterbox
					if(mode==FILL_HEIGHT) {
						ofRect(-1000, 0, 1000, height);
						ofRect(width, 0, 1000, height);
					} else {
						ofRect(0, -1000, width, 1000);
						ofRect(0, height, width, 1000);
					}
                    glPopMatrix();
                }
                
				
                
                void transformMouse(float &x, float &y) {
                    x /= fakeGameModeScale;
                    y /= fakeGameModeScale;
                    x -= offset.x;
					y -= offset.y;
					//printf("%f %f\n", x, y);
                }

				
                
                
                
            private:
                float fakeGameModeScale;

				ofVec2f offset;
                
                float width;
                float height;
				CentererMode mode;
            };
        }
    }
}