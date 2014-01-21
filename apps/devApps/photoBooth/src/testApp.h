#pragma once

#include "ofMain.h"
#include "ofxGifDecoder.h"

class ofxGifFileExtended : public ofxGifFile {
public:
	ofxGifFileExtended(ofxGifFile gif, ofFile file);
	void						draw(int x, int y, bool drawPalette = false);
	void						scale(float sizeMult);
	void						update();
private:
	int							m_frameIndex;
	float						m_sizeMult;
	ofFile						m_file;
	unsigned long long			m_loadTimeMs;
};

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
	private:
		ofVideoGrabber				m_vidGrabber;
		int							m_appWidth, m_appHeight;
	
		ofxGifDecoder				m_gifDecoder;
		vector<ofxGifFileExtended>	m_gifs;
};
