#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetWindowTitle( "particle example" );
	ofBackground( 0, 0, 0 );
	ofSetFrameRate( 60 );
	
	if ( !m_emitter.loadFromXml( "circles.pex" ) )
	{
		ofLog( OF_LOG_ERROR, "testApp::setup() - failed to load emitter config" );
	}
	mouseDragged(ofGetWidth()/2, 0, 0);
	mouseDragged(ofGetWidth()/2, ofGetHeight()/2, 0);

	m_emitter.bothDirections = false;
}

//--------------------------------------------------------------
void testApp::update(){
	m_emitter.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	m_emitter.draw(0, 0);
	
	ofSetColor(255, 255, 255);
	string toDisplay = "FPS: " + ofToString(ofGetFrameRate(), 2) 
		+ "\nAngle: " + ofToString(m_emitter.angle)
		+ "\nAngle variance: " + ofToString(m_emitter.angleVariance);
	ofDrawBitmapString(toDisplay, 20, 20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	float normX = (float)x / ofGetWidth();
	float normY = (float)y / ofGetHeight();
	ofVec2f vecDiff = ofVec2f(normX - m_lastMousePos.x, - (normY - m_lastMousePos.y));
	ofVec2f vecReference = ofVec2f(1.0f, 0.0f);
	m_emitterAngle = vecDiff.angle(vecReference);
	m_lastMousePos = ofPoint(normX, normY);
	m_emitter.angle = m_emitterAngle;
	m_emitter.sourcePosition.x = x;
	m_emitter.sourcePosition.y = y;
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}