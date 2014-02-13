#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	
	// init variables
	m_appWidth = 640;
	m_appHeight = 480;
	
	// setup video feed
	m_vidGrabber = ofVideoGrabber();
	m_vidGrabber.setVerbose(true);
	m_vidGrabber.listDevices();

	m_vidGrabber.initGrabber(m_appWidth, m_appHeight);
	
	// load all GIF files in subfolder "gifDir"
	ofDirectory gifDir("gifDir");
	gifDir.allowExt("gif");
	gifDir.listDir();
	for(int i = 0; i < gifDir.numFiles(); i++){
		if (m_gifDecoder.decode(gifDir.getPath(i)) == true) {
			ofLogNotice("Found and decoded GIF: " + gifDir.getPath(i));
			ofxGifFileExtended currGif(m_gifDecoder.getFile(), ofFile(gifDir.getPath(i)));
			m_gifs.push_back(currGif);
		}
	}
}

//--------------------------------------------------------------
void testApp::update(){	
	m_vidGrabber.update();
	
    for (int i = 0; i < m_gifs.size(); i++) {	
		m_gifs[i].update();
    }
}

//--------------------------------------------------------------
void testApp::draw(){
	// flip and draw video feed
	ofPushMatrix();
	ofSetRectMode( OF_RECTMODE_CENTER );
	ofTranslate( m_appWidth/2, m_appHeight/2, 0 );
	ofScale( -1, 1, 1 );
	m_vidGrabber.draw( 0, 0, m_appWidth, m_appHeight );
	ofSetRectMode( OF_RECTMODE_CORNER );
	ofPopMatrix();

	// draw all GIFs
    for (int i = 0; i < m_gifs.size(); i++) {		
        int gifW = m_gifs[i].getWidth();
        int gifH = m_gifs[i].getHeight();
		m_gifs[i].draw(i*gifW, 0);
		//ofLogVerbose("Drawing " + ofToString(i) + "\t at x=" + ofToString(m_gifs[i].getWidth()));
    }
}

//--------------------------------------------------------------
void testApp::exit(){
	m_vidGrabber.close();
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


//--------------------------------------------------------------
// GIF file extended
//--------------------------------------------------------------
ofxGifFileExtended::ofxGifFileExtended(ofxGifFile gif, ofFile file) :
	ofxGifFile(gif) {
	m_file = file;
	m_sizeMult = 1.0f;
	m_frameIndex = -1;
	m_loadTimeMs = ofGetElapsedTimeMillis();
	string msg = string("GIF file '" + file.path() + "\t\t " + ofToString(getNumFrames()) + "frames - " + ofToString(getDuration()) + "s");
	msg += "\nDimensions: " + ofToString(getWidth()) + "x" + ofToString(getHeight());
	msg += "\nLoaded at " + ofToString(m_loadTimeMs) + "ms";
	ofLogNotice() << msg;
}

//--------------------------------------------------------------
void ofxGifFileExtended::scale(float sizeMult)
{
	m_sizeMult = sizeMult;
}

//--------------------------------------------------------------
void ofxGifFileExtended::update()
{
	if (m_frameIndex == -1) {
		m_frameIndex = 0;
	} else {
		// Compute correct frame based on machine time and GIF info
		float lastFrameElapsed = ofGetLastFrameTime();
		long gifLifeTimeMs = ofGetElapsedTimeMillis() - m_loadTimeMs;
		
		float gifCurrentPointMs = (long)gifLifeTimeMs % (long)(getDuration() * getNumFrames() * 1000.0f);
		float gifCurrentProgress = gifCurrentPointMs / (getDuration() * getNumFrames() * 1000.0f); // % of progress in animation
		int currentFrame = (int)(gifCurrentProgress * getNumFrames());
		m_frameIndex = currentFrame;
		
		//ofLogVerbose() << "Lifetime: " + ofToString(gifLifeTimeMs/1000.0f) + "s\tIn GIF: " + ofToString(gifCurrentPointMs) + "ms\tCurrent frame: " + ofToString(currentFrame);
	}
}

//--------------------------------------------------------------
void ofxGifFileExtended::draw(int x, int y, bool drawPalette){
	int gifW = getWidth()*m_sizeMult;
	int gifH = getHeight()*m_sizeMult;
	drawFrame(m_frameIndex, x, y, gifW, gifH);
	//drawFrame(m_frameIndex, 0, 0, 60, 60);
	
	if (drawPalette) {
		// draw color palette
		for (int j = 0; j < getPalette().size(); j++) {
			ofSetColor(getPalette()[j].r, getPalette()[j].g, getPalette()[j].b);
			ofRect(gifW + j%15*10, gifH + j/15*10 , 10, 10);
		}
	}
}
