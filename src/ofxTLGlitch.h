
#ifndef _ofxTLGlitch_h
#define _ofxTLGlitch_h

#include "ofMain.h"
#include <string.h>
#include "ofxTimeline.h"


class ofxTLGlitch {
	
public:
	
	ofxTLGlitch();
	~ofxTLGlitch();
	
	void loadVideo(string name);
	void loadImage(string name);
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
	
	ofxTimeline timeline;
	ofVideoPlayer video;
	
	
	void keyPressed(ofKeyEventArgs& args);
	void mousePressed(ofMouseEventArgs& args);
	void windowResized(ofResizeEventArgs& args);
};

#endif
