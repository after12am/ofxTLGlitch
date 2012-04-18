
#ifndef _ofxTLGlitch_h
#define _ofxTLGlitch_h

#include "ofMain.h"
#include <string.h>
#include "ofxTimeline.h"


class ofxTLGlitch {
	
public:
	
	ofxTLGlitch();
	~ofxTLGlitch();
	
	void setup(string movie);
	void update(ofEventArgs& e);
	void draw(ofEventArgs& e);
	void mousePressed(int x, int y, int button);
	
	void togglePlay();
	void pause();
	void play();
	void reset();
	bool isPlaying() { return timeline.getIsPlaying(); }
	
	void toggleTimelineShowing();
	void showTimeline();
	void hideTimeline();
	bool isTimelineShowing() { return isShowing; }
	
	void setWidth(int width);
	
protected:
	
	vector<int> formats;
	
	bool isShowing;
	bool isReset;
	
	ofxTimeline timeline;
	ofVideoPlayer video;
};

#endif
