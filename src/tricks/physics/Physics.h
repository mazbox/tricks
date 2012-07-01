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
 *  Physics.h, created by Marek Bereza on 01/07/2012.
 */
#pragma once
#include "ofMain.h"
#include "Body.h"
#include "Constraint.h"
#include "DistanceConstraint.h"

namespace tricks {
	namespace physics {
		class Physics {
		
		public:
			Physics() {
				bounding = false;
				bounds.set(0, 0, 1024, 768);
				gravity.set(0,0);
				damping = 1;
				boundsBounciness = 0;
				impulseEnabled = false;
				collisionDamping = 0.1;
			}
			
			
			float collisionDamping;
			ofRectangle bounds;
			bool bounding;
			
			vector<Body*> bodies;
			vector<Constraint*> constraints;
			
			ofVec2f gravity;
			float damping;
			float boundsBounciness;
			bool impulseEnabled;
			
			
			// whether to allow impulse preservation
			void enableImpulse(bool enable = true) {
				impulseEnabled = enable;
			}
			
			// how much bounce to give body/body collisions
			void setCollisionDamping(float cd) {
				this->collisionDamping = cd;
			}
			
			// how bouncy to make the walls
			void setBoundsBounciness(float boundsBounciness) {
				this->boundsBounciness = boundsBounciness;
			}
			
			// how much drag should the particles have
			void setDamping(float damping) {
				this->damping = damping;
			}
			
			// set the bounds of the simulation
			void setBounds(ofRectangle &bounds) {
				this->bounds = bounds;
				bounding = true;
			}
			
			// whether to have bounding or not.
			void enableBounding(bool enable = true) {
				bounding = enable;
			}
			
			
			// add a body to the simulation
			void addBody(Body *body) {
				bodies.push_back(body);
			}
			
			
			// add gravity of a vector of your desired choice
			void setGravity(float x, float y) {
				gravity.set(x, y);
			}
			
			// add any constraint to the physics engine
			void addConstraint(Constraint *constraint) {
				constraints.push_back(constraint);
			}
			
			// add a distance constraint
			void addDistanceConstraint(Body *b1, Body *b2, float distance) {
				constraints.push_back(new DistanceConstraint(b1, b2, distance));
			}
			
			
			
			// attract all particles to eachother (call every frame)
			void attractToEachother() {
				
				for(int i = 0; i < bodies.size(); i++) {
					for(int j = 0; j < bodies.size(); j++) {
						if(i!=j) {
							bodies[i]->attract(bodies[j]->pos, 0.1);
						}
					}
				}
			}
			
			
			// repel all particles from eachother (call every frame)
			void repelFromEachother() {
				
				for(int i = 0; i < bodies.size(); i++) {
					for(int j = 0; j < bodies.size(); j++) {
						if(i!=j) {
							bodies[i]->repel(bodies[j]->pos, 0.1);
						}
					}
				}
			}
			void update() {
				
				
				if(gravity.x!=0 || gravity.y!=0) {
					for(int i = 0; i < bodies.size(); i++) {
						bodies[i]->addForce(gravity);
					}
				}
				
				if(bounding) doBorderCollision();
				
				// standard collision
				doCollision(false);	
				
				// update acceleration
				for(int i = 0; i < bodies.size(); i++) {
					bodies[i]->update(damping);
				}
				
				
				for(int i = 0; i < constraints.size(); i++) {
					constraints[i]->resolve();
				}
				
				
				// impulse
				if(impulseEnabled) doCollision(true);
			}
			
			
			void draw() {
				
				for(int i = 0; i < constraints.size(); i++) {
					constraints[i]->draw();
				}
				
				for(int i = 0; i < bodies.size(); i++) {
					bodies[i]->draw();
				}
			}
			
			
			
		private:
			void doBorderCollision() {
				// border collision
				int l=bodies.size();
				
				for(int i=0; i<l; i++){
					Body *body = bodies[i];
					float radius = body->radius;
					float x = body->pos.x;
					float y = body->pos.y;
					
					if(x-radius < bounds.x) {
						// impulse
						if(impulseEnabled) {
							
							float velX = body->pos.x - body->prev.x;
							body->prev.x = body->pos.x + velX*boundsBounciness;
						}
						
						// position
						body->pos.x = radius + bounds.x;
						
					} else if(x + radius > bounds.x + bounds.width){
						
						// impulse
						if(impulseEnabled) {
							float velX = body->pos.x - body->prev.x;
							body->prev.x = body->pos.x + velX*boundsBounciness;
						} 
						
						// position
						body->pos.x = (bounds.x + bounds.width)-radius;
					}
					
					if(y-radius < bounds.y){
						// impulse
						if(impulseEnabled) {
							float velY = body->pos.y - body->prev.y;
							body->prev.y = body->pos.y + velY*boundsBounciness;
						}
						
						// position
						body->pos.y = radius+bounds.y;
						
					} else if(y + radius > bounds.y + bounds.height){
						// impulse
						if(impulseEnabled) {
							float velY = body->pos.y - body->prev.y;
							body->prev.y = body->pos.y + velY*boundsBounciness;
						}
						
						// position
						body->pos.y = bounds.y+bounds.height-radius;
					}
				}
			}
			
			
		
			void doCollision(bool preserveImpulse) {
				
				int l = bodies.size();
				
				// collision
				for(int i=0; i<l; i++){
					Body *body1 = bodies[i];
					for(int j=i+1; j<l; j++){
						
						Body *body2 = bodies[j];
						
						ofVec2f d = body1->pos - body2->pos;
						
						float slength = d.lengthSquared();
						float length = sqrt(slength);
						float target = body1->radius + body2->radius;
						
						if(length < target){
							// record previous velocity
							ofVec2f v1 = body1->pos - body1->prev;
							ofVec2f v2 = body2->pos - body2->prev;
							
							
							// resolve the body overlap conflict
							float factor = (length-target)/length;
							
							
							body1->pos -= d*factor*0.5;
							body2->pos += d*factor*0.5;
							
							if(preserveImpulse) {
		
								// compute the projected component factors
								float f1 = (collisionDamping*(d.x*v1.x+d.y*v1.y))/slength;
								float f2 = (collisionDamping*(d.x*v2.x+d.y*v2.y))/slength;
								
								// swap the projected components
								v1.x += f2*d.x-f1*d.x;
								v1.y += f2*d.y-f1*d.y;
								
								v2.x += f1*d.x-f2*d.x;
								v2.y += f1*d.y-f2*d.y;
								
								// the previous position is adjusted
								// to represent the new velocity
								body1->prev = body1->pos - v1;
								body2->prev = body2->pos - v2;
							}
						}
					}
				}
			}
		};
	}
}