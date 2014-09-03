#include "rectangle.h"

//------------------------------------------------------------------
rectangle::rectangle(){
	shaper = 1.0;
}


//------------------------------------------------------------------
void rectangle::draw(){
	ofFill();
	ofSetRectMode(OF_RECTMODE_CENTER);
//	ofSetColor(155, 100, 255);
	ofSetCircleResolution(60);
	ofCircle(pos.x, pos.y, radius);
	
}
//------------------------------------------------------------------
void rectangle::interpolateByPct(float myPct){
	pct = powf(myPct, shaper);
	pos.x = (1-pct) * posa.x + (pct) * posb.x;
	pos.y = (1-pct) * posa.y + (pct) * posb.y;
	
	radius = (1-pct) * radiusa + (pct) * radiusb;	

}