//
//  ofxTLVideoGlitch.h
//
//  Created by Okami Satoshi on 12/05/05.
//  Copyright (c) 2012 Okami Satoshi. All rights reserved.
//

#include <iostream>
#include "ofxTLVideoGlitch.h"


void ofxTLVideoGlitch::load(string name) {
	video.loadMovie(name);
	video.setLoopState(OF_LOOP_NORMAL);
}

void ofxTLVideoGlitch::update() {
	video.update();
}

void ofxTLVideoGlitch::draw(float width, float height, float innerFormat, float packFormat) {
	ofTexture tex;
	tex.allocate(video.width, video.height, innerFormat);
	tex.loadData(video.getPixels(), video.width * width, video.height * height, packFormat);
	tex.draw( (ofGetWidth() - video.width) / 2, (ofGetHeight() - video.height) / 2, video.width, video.height);
}

void ofxTLVideoGlitch::pause() {
	video.setPaused(true);
}

void ofxTLVideoGlitch::play() {
	video.play();
}

void ofxTLVideoGlitch::setPosition(float position) {
	video.setPosition(position);
}

float ofxTLVideoGlitch::getDuration() {
	return video.getDuration();
}

int ofxTLVideoGlitch::getWidth() {
	return video.width;
}

int ofxTLVideoGlitch::getHeight() {
	return video.height;
}

unsigned char* ofxTLVideoGlitch::getPixels() {
	return video.getPixels();
}