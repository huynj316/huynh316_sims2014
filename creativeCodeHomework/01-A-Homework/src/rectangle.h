#pragma once
#include "ofMain.h"

class rectangle {

	public:
	
		rectangle();
	
		void draw();
		void interpolateByPct(float myPct);

		ofPoint pos;
	
		ofPoint posa;
		ofPoint posb;
		
		float pct;
		float shaper;
		
		float radius;
		float radiusa;
		float radiusb;
};
