#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	ofSetCircleResolution(60);
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
	ofBackground(ofColor::black);
	
	//sound
//	beacon.loadSound("sounds/beacon.wav");
	
	//particle start
    
    nPtsW = 20;
    nPtsH = 20;
    
    for (int i = 0; i < nPtsW; i++){
        for (int j = 0; j < nPtsH; j++){
            
            float x = ofMap(i,0,nPtsW, 0,ofGetWidth());
            float y = ofMap(j,0,nPtsH, 0,ofGetHeight());
            Particle myParticle;
            myParticle.setInitialCondition(x,y,0,0);
            // more interesting with diversity :)
            // uncomment this: 
            //myParticle.damping = ofRandom(0.01, 0.05);
            particles.push_back(myParticle);
        }    
    }
	//particle end
	
	
    thinkGear.setup();
    ofAddListener(thinkGear.attentionChangeEvent, this, &testApp::attentionListener);
    ofAddListener(thinkGear.meditationChangeEvent, this, &testApp::meditationListener);
	ofAddListener(thinkGear.blinkChangeEvent, this, &testApp::blinkListener);
    
    font.loadFont("font/DroidSansMono.ttf", 20);
	
    
    distAw = 0.0;
    prevAw = 0.0;
    currAw = 0.0;
    distMw = 0.0;
    prevMw = 0.0;
    currMw = 0.0;
    
    atChangeTime = 0.0;
    attention = 0.0;
    meChangeTime = 0.0;
    meditation = 0.0;
	

	
}
//--------------------------------------------------------------
void testApp::update(){

//particle start
	int count = 0;
	
	for (int i = 0; i < nPtsW; i++){
        for (int j = 0; j < nPtsH; j++){
			
            
            float x = ofMap(i,0,nPtsW, 0,ofGetWidth());
            float y = ofMap(j,0,nPtsH, 0,ofGetHeight());    
			
            particles[count].resetForce();
            
            
            particles[count].addAttractionForce(x, y, (attention*10), 0.1);
			//            // particles[i * nPtsH + j].addClockwiseForce(mouseX, mouseY, 100, 0.4);
            particles[count].addRepulsionForce((meditation*10), (attention*10), 500, 0.2);
			//
			//cout << mouseY << endl;
            
            particles[count].addDampingForce();
            particles[count].update();
            
            count++;
            
        }
	}
//particle end	
	
    thinkGear.update();
    
    float cur = ofGetElapsedTimef();
	
    float progress = cur - atChangeTime;
    progress = ofClamp(progress, 0.0, 1.0);
    if (progress == 0.0) prevAw = currAw;
    currAw = ofxTweenLite::tween(prevAw, distAw, progress, OF_EASE_SINE_INOUT);
    
    progress = cur - meChangeTime;
    progress = ofClamp(progress, 0.0, 1.0);
    if (progress == 0.0) prevMw = currMw;
    currMw = ofxTweenLite::tween(prevMw, distMw, progress, OF_EASE_SINE_INOUT);
	
	
    
}
//--------------------------------------------------------------
void testApp::draw(){
	
//particle start
	//ofBackgroundHex(0x000000);
    
    
    ofSetColor(ofRandom(255));
	for (int i = 0; i < particles.size(); i++){
		particles[i].draw();
	}
//particle end
	
	
    //ofBackgroundGradient(ofColor::white, ofColor::gray);
    
    ofPushStyle();
    ofSetColor(ofColor::black);
    string qStr = "";
    if (thinkGear.getSignalQuality() == 0.0)
    {
        qStr = "good";
    }
    else 
    {
        qStr = "poor (" + ofToString(thinkGear.getSignalQuality()) + ")";
    }
//    font.drawString("signal quality = " + qStr, 10, 40);    
    ofPopStyle();
	
	//blink
//	font.drawString("Blink", 10, (blink)); 
    
	//directions
	//if (attention > 1 && meditation > 1) {
//		beacon.play();
//		beacon.setVolume(attention);
//		font.drawString("CONCENTRATE ON DOT", ofGetWidth()/2, ofGetHeight()/2);
//	}

	
    //attention bar
    ofPushMatrix();
    ofTranslate(0, 30);
    ofPushStyle();
    ofSetColor(ofColor::black);
//    font.drawString("Attention", 10, ofGetHeight()/11 - 10);
    ofNoFill();
	
//  ofCircle(ofGetWidth()/2, ofGetHeight()/2, currAw);
    ofSetColor(ofColor::yellow, ofMap(currAw, 0.0, ofGetWidth(), 50, 255));
    ofFill(); 
	
//	ofCircle(ofGetWidth()/2, ofGetHeight()/2, currAw);
	ofSetColor(ofColor::black, ofMap(currAw, 0.0, ofGetWidth(), 50, 255));
//	font.drawString(ofToString(attention), 10, ofGetHeight()/11 + 40);
	

	
    ofPopStyle();
    ofPopMatrix();
    
	//key circle
	ofSetColor(ofColor::black);
//	ofTranslate(0, 30);
	
//	ofCircle(ofGetWidth()/2, (ofGetHeight()/2)+30, 2);
	
	//meditation bar
    ofPushMatrix();
    ofTranslate(0, 30);
    ofPushStyle();
    ofSetColor(ofColor::black);
//    font.drawString("Meditation", 10, (ofGetHeight()/3.5) - 10); 
    ofNoFill();
	
//	ofCircle(ofGetWidth()/2, ofGetHeight()/2, currMw);   
    ofSetColor(ofColor::cyan, ofMap(currMw, 0.0, ofGetWidth(), 50, 255));
    ofFill();
	
//	ofCircle(ofGetWidth()/2, ofGetHeight()/2, currMw);
	ofSetColor(ofColor::black, ofMap(currMw, 0.0, ofGetWidth(), 50, 255));
//	font.drawString(ofToString(meditation), 10, (ofGetHeight()/3.5) + 40); 
	
	
    ofPopStyle();
    ofPopMatrix();
    
				
    ofSetWindowTitle("fps = " + ofToString(ofGetFrameRate()));
	
	if (blink > 60 ) {
		ofSetBackgroundAuto(false);
	} else if (blink < 60) {
		ofSetBackgroundAuto(true);
	}

	
}


//--------------------------------------------------------------
void testApp::attentionListener(float &param){
    attention = param;
    distAw = ofMap(attention, 0.0, 100.0, 0, ofGetWidth());
    atChangeTime = ofGetElapsedTimef();
}
//--------------------------------------------------------------
void testApp::meditationListener(float &param){
    meditation = param;
    distMw = ofMap(meditation, 0.0, 100.0, 0, ofGetWidth());
    meChangeTime = ofGetElapsedTimef();    
}
//--------------------------------------------------------------
void testApp::blinkListener(float &param){
	cout << "blink: "<<param<<endl;
	blink = param;
}
//--------------------------------------------------------------


void testApp::keyPressed(int key){
	if (key == ' ') {
		ofToggleFullscreen();
	}
	
	if (key == 'a') {
		ofSetBackgroundAuto(false);
	}
	
	if (key == 'd') {
		ofSetBackgroundAuto(true);
	}

}
//--------------------------------------------------------------
void testApp::keyReleased(int key){}
//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){}
//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){}
//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){}
//--------------------------------------------------------------
void testApp::windowResized(int w, int h){}
//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){}
//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){}