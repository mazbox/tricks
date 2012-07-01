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
 *  Description:  This tracks a rotation - if you give it a rotation of n degrees, it'll make sure it doesn't jump 180 degrees, just keeps it in phase if it's one of those things
 *                that jumps about. Works in degrees or radians. (degrees by default)
 *				 
 *  AngleTracker.h, created by Marek Bereza on 25/08/2011.
 */

#pragma once
namespace tricks { 
	namespace vision {
		
	
		class AngleTracker {
		public:
			AngleTracker();
			
			/** Set this to true if you want radians instead of degrees */
			void usingRadians(bool useRadians);
			 
			/** pass in your angle here and get the real angle out. */
			float track(float angle);
			
			
			
		private:
			float lastTimeTrackedAngle;
			float lastAngle;
			bool useRadians;
		};
	}
}