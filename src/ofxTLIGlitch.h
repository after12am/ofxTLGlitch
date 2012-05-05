//
//  ofxTLIGlitch.h
//
//  Created by Okami Satoshi on 12/05/05.
//  Copyright (c) 2012 Okami Satoshi. All rights reserved.
//

#ifndef _ofxTLIGlitch_h
#define _ofxTLIGlitch_h


#include "ofMain.h"

class ofxTLIGlitch {
	
public:
	
	virtual void load(string name) = 0;
	virtual void update() = 0;
	virtual void draw(float width, float height, float innerFormat, float packFormat) = 0;
	virtual void pause() = 0;
	virtual void play() = 0;
	virtual void setPosition(float position) = 0;
	virtual float getDuration() = 0;
	virtual unsigned char* getPixels() = 0;
};


#endif
