
#include "ofxTLGlitch.h"
#include "ofxTLUtils.h"
#include <iostream>
#include <vector.h>

#define NOT_IMPL ofLogError("ofxTLGlitch", string(__PRETTY_FUNCTION__) + "not implemented yet"); throw "not implemented yet";

int formats[] = {
//	GL_ALPHA,
//	GL_ALPHA4,
//	GL_ALPHA8,
//	GL_ALPHA12,
//	GL_ALPHA16,
	GL_LUMINANCE,
//	GL_LUMINANCE4,
//	GL_LUMINANCE8,
//	GL_LUMINANCE12,
//	GL_LUMINANCE16,
//	GL_LUMINANCE_ALPHA,
//	GL_LUMINANCE4_ALPHA4,
//	GL_LUMINANCE6_ALPHA2,
//	GL_LUMINANCE8_ALPHA8,
//	GL_LUMINANCE12_ALPHA4,
//	GL_LUMINANCE12_ALPHA12,
//	GL_LUMINANCE16_ALPHA16,
	GL_INTENSITY,
//	GL_INTENSITY4,
//	GL_INTENSITY8,
//	GL_INTENSITY12,
//	GL_INTENSITY16,
//	GL_R3_G3_B2,
	GL_RGB,
//	GL_RGB4,
//	GL_RGB5,
//	GL_RGB8,
//	GL_RGB10,
//	GL_RGB12,
//	GL_RGB16,
//	GL_RGBA,
//	GL_RGBA2,
//	GL_RGBA4,
//	GL_RGB5_A1,
//	GL_RGBA8,
//	GL_RGB10_A2,
//	GL_RGBA12,
//	GL_RGBA16
};

//--------------------------------------------------------------
ofxTLGlitch::ofxTLGlitch() {
	
	isShowing = true;
	isReset = false;
	isEnableKeyPressed = true;
	
	ofAddListener(ofEvents.update, this, &ofxTLGlitch::update);
	ofAddListener(ofEvents.draw, this, &ofxTLGlitch::draw);
	ofAddListener(ofEvents.keyPressed, this, &ofxTLGlitch::keyPressed);
	ofAddListener(ofEvents.mousePressed, this, &ofxTLGlitch::mousePressed);
	ofAddListener(ofEvents.windowResized, this, &ofxTLGlitch::windowResized);
}

//--------------------------------------------------------------
ofxTLGlitch::~ofxTLGlitch() {
	
	try {
		ofRemoveListener(ofEvents.update, this, &ofxTLGlitch::update);
		ofRemoveListener(ofEvents.draw, this, &ofxTLGlitch::draw);
		ofRemoveListener(ofEvents.keyPressed, this, &ofxTLGlitch::keyPressed);
		ofRemoveListener(ofEvents.mousePressed, this, &ofxTLGlitch::mousePressed);
		ofRemoveListener(ofEvents.windowResized, this, &ofxTLGlitch::windowResized);
	} catch (...) {
		
	}
}

//--------------------------------------------------------------
void ofxTLGlitch::loadVideo(string name){
	
	/* setup video
	 ==============*/
	video.loadMovie(name);
	video.setLoopState(OF_LOOP_NORMAL);
	
	
	/* setup timeline
	 =================*/
	timeline.setup();
	timeline.setDurationInSeconds(video.getDuration());
	timeline.setLoopType(OF_LOOP_NORMAL);
	timeline.addKeyframes("inner format", "innerFormat.xml", ofRange(0, 100))->setDefaultValue(1);
	timeline.addKeyframes("pack format", "packFormat.xml", ofRange(0, 100))->setDefaultValue(1);
	timeline.addKeyframes("width", "width.xml", ofRange(95, 100))->setDefaultValue(1);
	timeline.addKeyframes("height", "height.xml", ofRange(0, 100))->setDefaultValue(1);
	timeline.addKeyframes("offset", "offset.xml", ofRange(0, 100));
	timeline.setSnapping(true);
	timeline.enableSnapToBPM(120.f);
	timeline.enableDrawBPMGrid(true);
	timeline.enableSnapToOtherElements(true);
	timeline.setMovePlayheadOnDrag(false);
	timeline.setMovePlayheadOnPaste(true);
	timeline.setAutosave(false);
	timeline.setCurrentTime(0);
	timeline.play();
	
	/* start video
	 ==============*/
	video.play();
}

//--------------------------------------------------------------
void ofxTLGlitch::loadImage(string name){
	NOT_IMPL
}

//--------------------------------------------------------------
void ofxTLGlitch::update(ofEventArgs&){
	
	if (isReset) {
		
		bool playing = isPlaying();
		
		video.setPosition(0);
		timeline.stop();
		
		timeline.setCurrentTime(0);
		
		if (playing) {
			timeline.play();
			video.play();
		}
		
		isReset = false;
	}
	
	video.update();
}

//--------------------------------------------------------------
void ofxTLGlitch::draw(ofEventArgs&){
	
	int n = sizeof(formats) / sizeof(int);
	float innerFormat = formats[ int(ofMap(timeline.getKeyframeValue("inner format"), 0, 100, 0, n - 1)) ];
	float packFormat = formats[ int(ofMap(timeline.getKeyframeValue("pack format"), 0, 100, 0, n - 1)) ];
	float widthPrc = timeline.getKeyframeValue("width") / 100;
	float heightPrc = timeline.getKeyframeValue("height") / 100;
	
	
	ofEnableAlphaBlending();
	
	
	/* overlay with gray rect field
	 ===============================*/
	
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	if (isShowing) {
		glPushMatrix();
		glColor4f(100, 100, 100, .3);
		glPopMatrix();		
	}
	
	/* draw video
	 ================*/
	
	ofPushMatrix();
	
	// set compression
	//ofTexCompression compression;
	//tex.setCompression(compression);
	
	ofTexture tex;
	tex.allocate(video.width, video.height, innerFormat);
	tex.loadData(video.getPixels(), video.width * widthPrc, video.height * heightPrc, packFormat);
	tex.draw( (ofGetWidth() - video.width) / 2, (ofGetHeight() - video.height) / 2, video.width, video.height);
	
	ofPopMatrix();
	
	
	/* draw timeline
	 =======================*/
	timeline.draw();
	
	
	ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void ofxTLGlitch::keyPressed(ofKeyEventArgs& args) {
	
	if (isEnableKeyPressed) {
		
		if(args.key == ' ') {
			
			togglePlay();
		}
		if(args.key == 'h') {
			
			toggleTimelineShowing();
		}
		if (args.key == 'r') {
			
			reset();
		}
	}
}

//--------------------------------------------------------------
void ofxTLGlitch::mousePressed(ofMouseEventArgs& args) {
	
	if (!timeline.getIsPlaying()) {
		
		if (args.y < 30) {
			
			video.setPosition(timeline.getCurrentTime() / video.getDuration());
		}
	}
}

//--------------------------------------------------------------
void ofxTLGlitch::windowResized(ofResizeEventArgs& args) {
	
	timeline.setWidth(args.width);
}

void ofxTLGlitch::togglePlay() {
	
	if (isPlaying()) {
		pause();
	} else {
		play();
	}	
}

//--------------------------------------------------------------
void ofxTLGlitch::pause() {
	
	timeline.stop();
	video.setPaused(true);
}

//--------------------------------------------------------------
void ofxTLGlitch::play() {
	
	timeline.play();
	video.play();
}

//--------------------------------------------------------------
void ofxTLGlitch::toggleTimelineShowing() {
	
	if (isShowing) {
		hideTimeline();
	} else {
		showTimeline();
	}
}

//--------------------------------------------------------------
void ofxTLGlitch::showTimeline() {
	
	isShowing = true;
	timeline.show();
}

//--------------------------------------------------------------
void ofxTLGlitch::hideTimeline() {
	
	isShowing = false;
	timeline.hide();
}

//--------------------------------------------------------------
void ofxTLGlitch::reset() {
	
	isReset = true;
}
