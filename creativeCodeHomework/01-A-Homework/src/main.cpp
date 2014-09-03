/*referenced examples from cwhitney/algo2013
 Title: Water & Light
 by Julie Huynh
 created 08/03/14
 */


#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){
	
	ofAppGlutWindow window;
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new testApp());

}
