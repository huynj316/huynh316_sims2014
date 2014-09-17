#pragma once
#include "ofMain.h"

class trail {
	
public:
	
	trail();
	
	void draw();
	void xenoToPoint(float catchX, float catchY);
	
	ofPoint pos, targetPos;
	
	float catchUpSpeed; //take this pct of where i wanna be, +1 catch up of my pos
	
	float radius;
};

