#include "testApp.h"
#include "vector.h"




//--------------------------------------------------------------
void testApp::setup(){
	
	//ofSetFrameRate(30);
	ofSetVerticalSync(true);
	//ofHideCursor();
	
	
	
	glitch.setup("../video/smile.mp4");
}

//--------------------------------------------------------------
void testApp::update(){
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ofBackground(.15*255);
	
	
	
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	bool isPlaying = glitch.isPlaying();
	
	if(key == ' '){
		
		glitch.togglePlay();
		
	}
	if(key == 'h'){
		
		glitch.toggleTimelineShowing();
	}
	
	if (key == 'r') {
		
		glitch.reset();
	}
	
	if (key == 'f') {
		
		ofToggleFullscreen();
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
	glitch.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
	glitch.setWidth(w);
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}