/**
 * Masker.h
 * Masker
 *
 * Created by Marek Bereza on 29/04/2011.
 *
 */
#pragma once

#include "ofMain.h"


    class Masker {
    public:
        
        void setMask(unsigned char *img, float width, float height, ofVec2f *p);
        void draw();

        ofColor getCentreColor();
    private:

        ofColor getColorFromImage(ofVec2f p);
        
        void setPoints(ofVec2f *p);
        
        unsigned char *pix;
        int bytesPerPixel;
        int imageWidth;
        
        ofColor centreColor;
        ofVec2f points[4];
        ofColor colors[4];
        ofVec2f fan[40];
        ofColor fanColors[40];
    };
