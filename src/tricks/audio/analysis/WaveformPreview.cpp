/**
 *  WaveformPreview.cpp
 *
 *  Created by Marek Bereza on 07/02/2012.
 */

#include "WaveformPreview.h"


WaveformPreview::WaveformPreview() {
	preview = NULL;
	audioFileLength = 0;
}

WaveformPreview::~WaveformPreview() {
	if(preview!=NULL) {
		delete [] preview;
	}
}

void WaveformPreview::generatePreview(float *samples, int length) {
	audioFileLength = length;
	previewLength = (int)ceil((float)length / (float)SAMPLES_PER_PREVIEW_FRAME);
	preview = new float[previewLength];
	float max = 0;
	for(int i = 0; i < previewLength; i++) {
		int from = i*SAMPLES_PER_PREVIEW_FRAME;
		int to = MIN((i+1)*SAMPLES_PER_PREVIEW_FRAME, length);
		
		for(int j = from; j < to; j++) {
			float v = ABS(samples[j]);
			if(max<v) max = v;
			else max *= 0.999;
		}
		preview[i] = max;
	}
}
void WaveformPreview::draw(const ofRectangle &r, int start, int end) {
	if(preview==NULL) return;
	if(end==-1) end = audioFileLength;
	float h2 = r.height/2;
	// horizontal line
	ofLine(r.x, r.y + h2, r.x + r.width, r.y + h2);
	int ps = floor(ofMap(start, 0, audioFileLength, 0, previewLength));
	int pe = floor(ofMap(end, 0, audioFileLength, 0, previewLength));
	for(int i = r.x; i < r.width+r.x; i++) {
		int offset = floor(ofMap(i, r.x, r.x+r.width, ps, pe));	
		float val = preview[offset]*h2;
		ofLine(i, r.y + h2-val, i, r.y + val+h2);
	}
}