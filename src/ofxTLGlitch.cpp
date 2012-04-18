
#include "ofxTLGlitch.h"
#include "ofxTLUtils.h"
#include <iostream>
#include <vector.h>


ofxTLGlitch::ofxTLGlitch() {
	
	
//	formats.push_back(GL_ALPHA);
//	formats.push_back(GL_ALPHA4);
//	formats.push_back(GL_ALPHA8);
//	formats.push_back(GL_ALPHA12);
//	formats.push_back(GL_ALPHA16);
formats.push_back(GL_LUMINANCE);
//	formats.push_back(GL_LUMINANCE4);
//	formats.push_back(GL_LUMINANCE8);
//	formats.push_back(GL_LUMINANCE12);
//	formats.push_back(GL_LUMINANCE16);
//	formats.push_back(GL_LUMINANCE_ALPHA);
//	formats.push_back(GL_LUMINANCE4_ALPHA4);
//	formats.push_back(GL_LUMINANCE6_ALPHA2);
//	formats.push_back(GL_LUMINANCE8_ALPHA8);
//	formats.push_back(GL_LUMINANCE12_ALPHA4);
//	formats.push_back(GL_LUMINANCE12_ALPHA12);
//	formats.push_back(GL_LUMINANCE16_ALPHA16);

formats.push_back(GL_INTENSITY);
//	formats.push_back(GL_INTENSITY4);
//	formats.push_back(GL_INTENSITY8);
//	formats.push_back(GL_INTENSITY12);
//	formats.push_back(GL_INTENSITY16);
//	formats.push_back(GL_R3_G3_B2);
formats.push_back(GL_RGB);
//	formats.push_back(GL_RGB4);
//	formats.push_back(GL_RGB5);
//	formats.push_back(GL_RGB8);
//	formats.push_back(GL_RGB10);
//	formats.push_back(GL_RGB12);
//	formats.push_back(GL_RGB16);
//	formats.push_back(GL_RGBA);
//	formats.push_back(GL_RGBA2);
//	formats.push_back(GL_RGBA4);
//	formats.push_back(GL_RGB5_A1);
//	formats.push_back(GL_RGBA8);
//	formats.push_back(GL_RGB10_A2);
//	formats.push_back(GL_RGBA12);
//	formats.push_back(GL_RGBA16);
	
	isShowing = true;
	isReset = false;
	
	ofAddListener(ofEvents.update, this, &ofxTLGlitch::update);
	ofAddListener(ofEvents.draw, this, &ofxTLGlitch::draw);
}

ofxTLGlitch::~ofxTLGlitch() {
	
	try {
		ofRemoveListener(ofEvents.update, this, &ofxTLGlitch::update);
		ofRemoveListener(ofEvents.draw, this, &ofxTLGlitch::draw);
	} catch (...) {
		
	}
}

//--------------------------------------------------------------
void ofxTLGlitch::setup(string movie){
	
	/* setup video
	 ==============*/
	video.loadMovie(movie);
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
void ofxTLGlitch::update(ofEventArgs& e){
	
	if (isReset) {
		
		video.setPosition(0);
		timeline.stop();
		
		timeline.setCurrentTime(0);
		
		if (isPlaying()) {
			timeline.play();
			video.play();
		}
		
		isReset = false;
	}
	
	video.update();
}

//--------------------------------------------------------------
void ofxTLGlitch::draw(ofEventArgs& e){
	
	/* draw video
	 ================*/
	
	float innerFormat = formats[ floor(ofMap(timeline.getKeyframeValue("inner format"), 0, 100, 0, formats.size() - 1)) ];
	float packFormat = formats[ floor(ofMap(timeline.getKeyframeValue("pack format"), 0, 100, 0, formats.size() - 1)) ];
	float widthPrc = timeline.getKeyframeValue("width") / 100;
	float heightPrc = timeline.getKeyframeValue("height") / 100;
	
	
	/* overlay with gray rect field
	 ===============================*/
	
	ofEnableAlphaBlending();
	
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	if (isShowing) {
		glPushMatrix();
		glColor4f(100, 100, 100, .3);
		glPopMatrix();		
	}
	
	ofPushMatrix();
	ofTexture tex;
	// OF_IMAGE_QUALITY_BEST, OF_IMAGE_QUALITY_HIGH, OF_IMAGE_QUALITY_MEDIUM, OF_IMAGE_QUALITY_LOW, OF_IMAGE_QUALITY_WORST
	//ofTexCompression compression;
	//tex.setCompression(compression);
	tex.allocate(video.width, video.height, innerFormat);
	tex.loadData(video.getPixels(), video.width * widthPrc, video.height * heightPrc, packFormat);
	tex.draw( (ofGetWidth() - video.width) / 2, (ofGetHeight() - video.height) / 2, video.width, video.height);
	ofPopMatrix();
	
	
	/* draw timeline
	 =======================*/
	timeline.draw();
}

void ofxTLGlitch::togglePlay() {
	
	if (isPlaying()) pause();
	else play();
}

void ofxTLGlitch::pause() {
	
	timeline.stop();
	video.setPaused(true);
}

void ofxTLGlitch::play() {
	
	timeline.play();
	video.play();
}

void ofxTLGlitch::toggleTimelineShowing() {
	
	if (isShowing) timeline.hide();
	else timeline.show();
}

void ofxTLGlitch::showTimeline() {
	
	isShowing = true;
	timeline.show();
}

void ofxTLGlitch::hideTimeline() {
	
	isShowing = false;
	timeline.hide();
}

void ofxTLGlitch::reset() {
	
	isReset = true;
}

void ofxTLGlitch::mousePressed(int x, int y, int button) {
	
	if ((!timeline.getIsPlaying()) && y < 30) {
		
		video.setPosition(timeline.getCurrentTime() / video.getDuration());
	}
}

void ofxTLGlitch::setWidth(int width) {
	
	timeline.setWidth(width);
}
