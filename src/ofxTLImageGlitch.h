//
//  ofxTLImageGlitch.h
//
//  Created by Okami Satoshi on 12/05/05.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ofxTLImageGlitch_h
#define _ofxTLImageGlitch_h

#include "ofxTLIGlitch.h"
#include "ofxTimeline.h"
#include "ofMain.h"
#include "ofImage.h"
#include <string.h>

class ofxTLImageGlitch : public ofxTLIGlitch {
	
protected:
	
	ofImage image;
	float duration;
	
public:
	
	ofxTimeline* timeline;
	
	ofxTLImageGlitch(float _duration) {
		duration = _duration;
	}
	
	void load(string name);
	void update();
	void draw(float width, float height, float innerFormat, float packFormat);
	void pause();
	void play();
	void setPosition(float position);
	float getDuration();
	int getWidth();
	int getHeight();
	unsigned char* getPixels();
};

#endif
