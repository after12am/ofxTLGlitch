//
//  ofxTLVideoGlitch.h
//
//  Created by Okami Satoshi on 12/05/05.
//  Copyright (c) 2012 Okami Satoshi. All rights reserved.
//

#ifndef _ofxTLGlitch_h
#define _ofxTLGlitch_h

#include <string.h>
#include "ofMain.h"
#include "ofxTimeline.h"
#include "ofxTLIGlitch.h"
#include "ofxTLImageGlitch.h"


class ofxTLGlitch {
	
public:
	
	ofxTLGlitch();
	~ofxTLGlitch();
	
	void setupTimeline();
	void loadVideo(string name);
	void loadImage(string name, float duration);
	void update(ofEventArgs&);
	void draw(ofEventArgs&);
	
	void enableKeyPressed() { isEnableKeyPressed = true; }
	void disableKeyPressed() { isEnableKeyPressed = false; }
	
	bool isPlaying() { return timeline.getIsPlaying(); }
	void togglePlay();
	void pause();
	void play();
	void reset();
	
	bool isTimelineShowing() { return isShowing; }
	void toggleTimelineShowing();
	void showTimeline();
	void hideTimeline();
	
	
protected:
	
	bool isShowing;
	bool isReset;
	bool isEnableKeyPressed;
	bool isMousePressed;
	
	ofxTimeline timeline;
	ofxTLIGlitch* media;
	
	void keyPressed(ofKeyEventArgs& args);
	void mousePressed(ofMouseEventArgs& args);
	void windowResized(ofResizeEventArgs& args);
};

#endif
