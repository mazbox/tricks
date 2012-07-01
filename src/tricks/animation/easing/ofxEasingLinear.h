#ifndef _PENNER_LINEAR
#define _PENNER_LINEAR

#include "ofxEasing.h"
class ofxEasingLinear: public ofxEasing {

	public:

		// return c*t/d + b;
		// b is offset
		// d is total duration
		// t is position
		// c is distance
		// so we want b = 0, d = 1, t = [0,1], c = 1
		float easeNone(float t,float b , float c, float d); // ??
		float easeIn(float t,float b , float c, float d);
		float easeOut(float t,float b , float c, float d);
		float easeInOut(float t,float b , float c, float d);

};

#endif
