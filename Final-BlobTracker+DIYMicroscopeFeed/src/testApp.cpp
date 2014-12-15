//  ofxBlobTracker.cpp
//  museoDelJuguete
//
//  Created by Patricio Gonz‡lez Vivo on 3/26/12.
//  Copyright (c) 2012 PatricioGonzalezVivo.com. All rights reserved.

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
//	camWidth 		= 320;	// try to grab at this size. 
//	camHeight 		= 240;
//	
//	//list of devices to choose the correct camera feed
//	vector<ofVideoDevice> devices = vidGrabber.listDevices();
//	
//    for(int i = 0; i < devices.size(); i++){
//		cout << devices[i].id << ": " << devices[i].deviceName; 
//        if( devices[i].bAvailable ){
//            cout << endl;
//        }else{
//            cout << " - unavailable " << endl; 
//        }
//	}
	
//	#ifdef _USE_LIVE_VIDEO //uncomment to use live video
//		vidGrabber.setDeviceID(0);
//		vidGrabber.setDesiredFrameRate(60);
//		vidGrabber.initGrabber(camWidth,camHeight);
//        vidGrabber.setVerbose(true);
//
//	#else
		movieWidth = 640;
		movieHeight = 480;
        vidPlayer.loadMovie("paramecium.mp4");
        vidPlayer.play();
//	#endif

    colorImg.allocate(movieWidth, movieHeight);
	grayImage.allocate(movieWidth, movieHeight);

	threshold = 85;
    
    ofAddListener(blobTracker.blobAdded, this, &testApp::blobAdded);
    ofAddListener(blobTracker.blobMoved, this, &testApp::blobMoved);
    ofAddListener(blobTracker.blobDeleted, this, &testApp::blobDeleted);
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(100,100,100);

    bool bNewFrame = false;

//	#ifdef _USE_LIVE_VIDEO
//      vidGrabber.update();
//	   bNewFrame = vidGrabber.isFrameNew();
//    #else
        vidPlayer.update();
        bNewFrame = vidPlayer.isFrameNew();

//	#endif

	if (bNewFrame){

//		#ifdef _USE_LIVE_VIDEO
//          colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
//	    #else
            colorImg.setFromPixels(vidPlayer.getPixels(), movieWidth, movieHeight);
//        #endif

        grayImage = colorImg;

        blobTracker.update(grayImage, threshold);
	}

}

//--------------------------------------------------------------
void testApp::draw(){
	
	

	// draw the incoming, the grayscale, the bg and the thresholded difference
	ofSetHexColor(0xffffff);
	colorImg.draw(20,20);
//	grayImage.draw(360,20);

	// then draw the contours:

	blobTracker.draw(20,20);

	// or, instead we can draw each blob individually,
	// this is how to get access to them:

    for (int i = 0; i < blobTracker.size(); i++){
        ofFill();
        ofSetColor(255,0,0);
        ofCircle(blobTracker[i].centroid.x * ofGetWidth(), 
                 blobTracker[i].centroid.y * ofGetHeight(), 
                 10);
        ofSetColor(0);
        ofDrawBitmapString(ofToString( blobTracker[i].id ),
                           blobTracker[i].centroid.x * ofGetWidth(), 
                           blobTracker[i].centroid.y * ofGetHeight());
    }

}

void testApp::blobAdded(ofxBlob &_blob){
    ofLog(OF_LOG_NOTICE, "Blob ID " + ofToString(_blob.id) + " added" );
}

void testApp::blobMoved(ofxBlob &_blob){
    ofLog(OF_LOG_NOTICE, "Blob ID " + ofToString(_blob.id) + " moved" );
}

void testApp::blobDeleted(ofxBlob &_blob){
    ofLog(OF_LOG_NOTICE, "Blob ID " + ofToString(_blob.id) + " deleted" );
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	if (key == 'f') {
		ofToggleFullscreen();
	}

	switch (key){
		case ' ':
			blobTracker.bUpdateBackground = true;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
	}
	cout << threshold << endl;
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
