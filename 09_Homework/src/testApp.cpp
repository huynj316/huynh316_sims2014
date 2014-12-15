#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
    
    
    //  Load our texture
    //  in NON-ARB mode... that means their texCoords goes from 0-1
    //
    ofDisableArbTex();
    ofLoadImage(tex, "paramecium.png");
    ofEnableArbTex();
    
    //  Load the shader
    //
    shader.load("","shader.frag");
    
    //  Set up our vector field and particles
    //
    vf.setup(ofGetWidth(), ofGetHeight(), 10);
    for (int i = 0; i < 1000; i++) {
        Particle p;
        p.setInit(ofPoint(ofRandom(ofGetWidth()),ofRandom(ofGetHeight())));
        particles.push_back(p);
    }
    
    //  Alocate the FBOs
    //  a FBO is like a screen... we can render and draw in it.
    //  but instead of been render on the monitor is render into memory (Frame Buffer Object)
    //  http://openframeworks.cc/documentation/gl/ofFbo.html
    //
    fbo.allocate(ofGetWidth(), ofGetHeight());
    fboSmall.allocate(vf.cols, vf.rows);

    nDrawLayer = 1; // Original Texture;
    bDrawVield = true;
}

//--------------------------------------------------------------
void testApp::update(){

    int width = ofGetWidth();
    int height = ofGetHeight();
    
    //  Render our shader into an FBO
    //
    fbo.begin();
    ofClear(0);
    ofSetColor(255);
    shader.begin();
    shader.setUniformTexture("texture", tex,0);
    shader.setUniform2f("mouse", mouseX, mouseY);
    shader.setUniform1f("time", ofGetElapsedTimef());
    glBegin(GL_QUADS);
    
    glTexCoord2f(0, 0);
    glVertex2f(0, 0);
    
    glTexCoord2f(1.0, 0);
    glVertex2f(width, 0);
    
    glTexCoord2f(1.0, 1.0);
    glVertex2f(width, height);
    
    glTexCoord2f(0, 1.0);
    glVertex2f(0, height);
    
    glEnd();
    shader.end();
    fbo.end();
    
    //  Render the FBO inside another smaller FBO
    //  (this will lower the amount of pixels to get from the GPU) ;)
    //
    fboSmall.begin();
    ofClear(0);
    ofSetColor(255);
    fbo.draw(0,0,fboSmall.getWidth(),fboSmall.getHeight());
    fboSmall.end();
    
    //  Get those pixels from the GPU!
    //
    ofFloatPixels pixels;
    fboSmall.readToPixels(pixels);
    
    //  Update the Vector field with the pixels
    //
    for (int x = 0; x < vf.table.size(); x++) {
        for (int y = 0; y < vf.table[x].size(); y++) {
            ofFloatColor color = pixels.getColor(x, y);

            //  From RGB (0-1) to XYZ (-1,1)
            //
            ofPoint force = ofPoint(color.r,color.g,color.b);
            force *= 2.;
            force -= ofPoint(1,1,1);
            
            vf.table[x][y] = force*ofPoint(-1,-1,0);
        }
    }
    
    vf.update();
    
    for (int i = 0; i < particles.size(); i++) {
        particles[i].addForce( vf.getForce(particles[i].getPosition()) * 0.1 );
        particles[i].update();
        particles[i].infiniteWalls();
    }
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(0);
    
    ofSetColor(255);
    if(nDrawLayer == 0){
        // Don't draw nothing
    } else if (nDrawLayer == 1){
        //  Draw the heightmap
        tex.draw(0,0,ofGetWidth(),ofGetHeight());
    } else if (nDrawLayer == 2){
        //  Draw the computed normals
        fbo.draw(0, 0);
    } else if (nDrawLayer == 3){
        //  Draw the scaled normal texture
        fboSmall.draw(0,0,ofGetWidth(),ofGetHeight());
    }
    
    if(bDrawVield){
        //  Draw the vector field
        vf.draw();
    }
    
    for (int i = 0; i < particles.size(); i++) {
        particles[i].draw();
    }
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    //  Reload the shader
    //
    shader.load("","shader.frag");
    
    if (key == ' ') {
        nDrawLayer = (nDrawLayer+1)%4;
    } else if ( key == 'v'){
        bDrawVield = !bDrawVield;
    }
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
