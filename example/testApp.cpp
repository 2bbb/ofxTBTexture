#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    image.loadImage("2b31fef7.jpg");
    ofEnableSmoothing();
    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0, 0, 0);
    
    ofSetColor(255, 255, 255);
    
    ofPoint ps[4], tps[4];
    ps[0].set(0, 100);
    ps[1].set(600, 0);
    ps[2].set(600, 300);
    ps[3].set(300, 400);
    
    tps[0].set(0, 100);
    tps[1].set(600, 0);
    tps[2].set(600, 300);
    tps[3].set(300, 400);
    
    ofFbo fbo;
    fbo.allocate(600, 600);
    fbo.begin();
    ofBackground(0, 0, 0);
    ofSetColor(255, 255, 255);
    for(int i = 0; i < 20; i++) {
        ofLine(0, 30 * i, 600, 30 * i);
        ofLine(30 * i, 0, 30 * i, 600);
    }
    fbo.end();
    
    ofxTBTexture tex(fbo.getTextureReference());
//    tex.draw(ps[0], ps[1], ps[2], ps[3], ofRectangle(0, 0, 400, 400));
    tex.draw(ps, tps);
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