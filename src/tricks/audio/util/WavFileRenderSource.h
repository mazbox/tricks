
#include "tricks/audio/file/WavFile.h"
#include "tricks/audio/util/OfflineRenderSource.h"
class WavFileRenderSource: public OfflineRenderSource {
public:

	WavFileRenderSource() {
		pos = 0;
	}
	
	void setWavFile(WavFile *wavFile) {
		this->wavFile = wavFile;
		pos = 0;
	}
	
	int getLength() {
		return wavFile->getLength();
	}
	
	int getNumChannels() {
		return wavFile->getNumChannels();
	}
	
	int getSamples(float *buffer, int length) {
		int numToCopy = MIN(length, wavFile->getLength() - pos);	
		if(numToCopy>0) memcpy(buffer, wavFile->data+pos, numToCopy*sizeof(float));
		return numToCopy;
	}
private:
	int pos;
	WavFile *wavFile;
};