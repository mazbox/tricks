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
 *  PeakDetector.h, created by Marek Bereza on 09/09/2011.
 */



class PeakDetector {
public:
		
	float threshold;
	
	int minLowCount;
	int minHighCount;
	
	
	PeakDetector() {
		reset();
	}
	void reset() {
		volume = 0;
		threshold = 0.1;
		lowVolCount = 0;
		minLowCount = 1000;
		minHighCount = 100;
	}
	
	
	/**
	 * Basic algorithm - if there is a sound that goes over the threshold
	 * for minHighCount samples, having been under the thresh for minLowCount
	 * samples, it's a peak
	 */
	void analyze(float *buff, int length, vector<int> &outPeaks) {
		for(int i = 0; i < length; i++) {
			if(volume>ABS(buff[i])) {
				volume *= 0.99;
			} else {
				volume = ABS(buff[i]);
			}

			if(volume<threshold) {
				lowVolCount++;
				highVolCount = 0;
			} else {
				if(highVolCount>minHighCount) {
					// done a peak!
					outPeaks.push_back(lastPeak);
					highVolCount = 0;
					lowVolCount = 0;
				} else {
					if(lowVolCount>minLowCount) {
						if(highVolCount==0) lastPeak = i;
						highVolCount++;
					} else {
						lowVolCount = 0;
					}
				}
				
				
			}
		}
	}
	void findEnvelopes(float *buff, int length, vector<int> &outPeaks) {
		vector<int> pks;
		
		analyze(buff, length, pks);
		for(int i = 0; i < pks.size(); i++) {
			int end = length; 
			if(i+1<pks.size()) end = pks[i+1];
			
			// find the end of the envelope somewhere in here...
			for(int j = pks[i]; j < end; j++) {
				
			}
			
			outPeaks.push_back(pks[i]);
			outPeaks.push_back((end+pks[i])/2);
		}
	}
	
	void findNonSilentRegions(float *buff, int length, vector<int> &outPeaks, int minNumSilents) {
		int i = 0;
		int zeroCount = 0;
		
		// consume any initial sound
		if(buff[i]!=0) {
			outPeaks.push_back(i);
			while(buff[i]!=0 && i < length) { i++; }
			if(i<length && buff[i]==0) outPeaks.push_back(i);
		}
		
		// so now we definitely have silence to start with
		

		for(; i < length; i++) {
			while(i < length && buff[i]==0) {
				zeroCount++;
				i++;
			}
			// we've had a zero
			if(zeroCount>minNumSilents) {
				outPeaks.push_back(i);
				while(i < length && buff[i]!=0) {
					i++;
				}
				outPeaks.push_back(i);
				zeroCount = 0;
			}
			
			
			
		}
	}

	int lastPeak;

	
	int highVolCount;
	int lowVolCount;
	float volume;
	
};