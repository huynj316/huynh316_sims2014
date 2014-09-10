#pragma once

#include "ofMain.h"
#include "trail.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
		//trail
		vector<trail>	trailList;
	
		//orbit
		float amplitudeX;
		float amplitudeY;
		float period;
	
//		//pencil tool
//		vector < ofPoint > points;
		
		//circle path
		vector < ofPoint > points;
	
	
		float radiusC;
	
		//atan2 tool
		void drawDot(ofPoint _pos);
	
		vector<float> sinHistory;
	
		ofPoint center;
		ofPoint dotPos;
	
		float   angleT;
		float   radiusT;
	
		bool    bPlay;
		
		
};
