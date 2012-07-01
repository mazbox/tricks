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
 *  DistanceConstraint.h, created by Marek Bereza on 01/07/2012.
 */


#pragma once

#include "Constraint.h"
namespace tricks {
	namespace physics {
		class DistanceConstraint: public Constraint {
		public:
			Body *b1;
			Body *b2;
			float distance;
			
			DistanceConstraint(Body *b1, Body *b2, float distance) {
				this->b1 = b1;
				this->b2 = b2;
				this->distance = distance;
			}
			
			virtual void draw() {
				ofSetHexColor(0xFFFFFF);
				ofLine(b1->pos, b2->pos);
			}
			
			virtual void resolve() {
				float force = distance - b1->pos.distance(b2->pos);
				
				ofVec2f direction = (b1->pos-b2->pos).normalized();
				ofVec2f acceleration = direction*force*0.1;
				
				b1->addForce(acceleration);
				acceleration *= -1;
				b2->addForce(acceleration);
			
			}
		};
	}
}