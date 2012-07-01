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
 *  Body.h, created by Marek Bereza on 01/07/2012.
 */

#pragma once

#include "ofMain.h"
namespace tricks {
	namespace physics {
		class Body {
		public:
			ofVec2f acceleration(ofVec2f pos1, ofVec2f pos2) {
				float G = 1500;
				ofVec2f direction = pos1 - pos2;
				float length = direction.length();
				ofVec2f normal = direction;
				normal.normalize();
				return normal*G/(length*length);
			}
			
			ofVec2f pos;
			ofVec2f prev;
			float damping;
			float maxSpeed;
			float radius;
			bool fixed;
			ofFloatColor color;
			
			Body(float x = 0, float y = 0) {
				fixed = false;
				maxSpeed = 10;
				radius = ofRandom(25, 80);
				damping = 1;
				pos.set(x, y);
				prev.set(x, y);
				color.set(ofRandom(0.5, 1), ofRandom(0, 0.5), ofRandom(0, 0.5));
			}
			
			void setPosition(float x, float y) {
				pos.set(x, y);
				prev = pos;
			}
			void setFixed(bool fixed = true) {
				this->fixed = fixed;
			}
			
			void attract(ofVec2f force, float amount = 1) {
				if(fixed) return;
				prev -= acceleration(force, pos)*amount;
			}
			
			void repel(ofVec2f force, float amount = 1) {
				if(fixed) return;
				prev += acceleration(force, pos)*amount;
			}
			
			void addForce(const ofVec2f &force) {
				if(fixed) return;
				prev -= force;
			}
			void addForce(float x, float y) {
				if(fixed) return;
				prev -= ofVec2f(x, y);
			}
			
			
			void update(float damping) {
				if(fixed) return;
				ofVec2f vel = pos - prev;
				vel.limit(maxSpeed);
				
				ofVec2f p = pos + vel*this->damping*damping;
				
				prev = pos;
				pos = p;
			}
			
			virtual void draw() {
				ofSetColor(color);
				ofCircle(pos, radius);
			}
		};
	}
}