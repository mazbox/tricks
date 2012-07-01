

class OfflineRenderSource {
public:

	virtual int getLength() = 0;
	virtual int getNumChannels() = 0;
	
	// length is in frames, not samples 
	// (i.e. in stereo, 1 would represent 
	// 2 samples (left and right)
	virtual int getSamples(float *buffer, int length) = 0;
};