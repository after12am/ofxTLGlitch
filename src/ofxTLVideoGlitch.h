//
//  ofxTLVideoGlitch.h
//
//  Created by Okami Satoshi on 12/05/05.
//  Copyright (c) 2012 Okami Satoshi. All rights reserved.
//

#ifndef _ofxTLVideoGlitch_h
#define _ofxTLVideoGlitch_h

#include "ofxTLIGlitch.h"
#include "ofxTimeline.h"
#include "ofMain.h"
#include <string.h>

class ofxTLVideoGlitch : public ofxTLIGlitch {
	
protected:
	
	ofVideoPlayer video;
	
public:
	
	ofxTimeline* timeline;
	
	
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
