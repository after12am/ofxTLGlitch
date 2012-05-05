//
//  ofxTLImageGlitch.cpp
//  emptyExample
//
//  Created by Okami Satoshi on 12/05/05.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "ofxTLImageGlitch.h"


void ofxTLImageGlitch::load(string name) {
	image.loadImage(name);
}

void ofxTLImageGlitch::update() {
	image.update();
}

void ofxTLImageGlitch::draw(float width, float height, float innerFormat, float packFormat) {
	ofTexture tex;
	tex.allocate(image.width, image.height, innerFormat);
	tex.loadData(image.getPixels(), image.width * width, image.height * height, packFormat);
	tex.draw( (ofGetWidth() - image.width) / 2, (ofGetHeight() - image.height) / 2, image.width, image.height);
}

void ofxTLImageGlitch::pause() {
	
}

void ofxTLImageGlitch::play() {
	
}

void ofxTLImageGlitch::setPosition(float position) {
	
}

float ofxTLImageGlitch::getDuration() {
	return duration;
}

int ofxTLImageGlitch::getWidth() {
	return image.width;
}

int ofxTLImageGlitch::getHeight() {
	return image.height;
}

unsigned char* ofxTLImageGlitch::getPixels() {
	return image.getPixels();
}