#include "ofApp.h"
#include "ofxUniformGui.h"

void ofApp::setup() {
    
    
    shader.load("blob");
    
    for (int i = 0; i < 20; things.push_back(Thing()), i++);
    
    tex.allocate(512, 1, GL_RGB32F);
    mesh = ofMesh::plane(ofGetWidth(), ofGetHeight());
    
    ofxUniformGui::get()->setShowKey('s');

}


void ofApp::update() {

    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    for (auto &thing : things) {
        thing.update();
    }
    
    if (tex.getWidth() < things.size()) {
        ofLogError() << "thing texture not big enough!";
        ofExit();
    }

    int l = tex.getWidth() * tex.getHeight() * 3;
    float pixa[l];
    
    for (int i = 0; i < things.size(); i++) {
        pixa[i * 3] = things[i].pos.x / ofGetWidth();
        pixa[i * 3 + 1] = things[i].pos.y / ofGetHeight();
        pixa[i * 3 + 2] = 0;
    }
    
    tex.loadData(pixa, tex.getWidth(), tex.getHeight(), GL_RGB);
}


void ofApp::draw() {

    ofBackground(255, 255, 255);
    

    shader.begin();

    shader.setUniformTexture("tex", tex, 0);
    shader.setUniform2f("windowSize", ofGetWidth(), ofGetHeight());
    
    
    ofPushMatrix();
    ofTranslate(ofGetWidth() >> 1, ofGetHeight() >> 1);
    mesh.draw();
    ofPopMatrix();
    
    shader.end();
    
    
}


void ofApp::keyPressed(int key) {

}


void ofApp::keyReleased(int key) {

}


void ofApp::mouseMoved(int x, int y) {

}


void ofApp::mouseDragged(int x, int y, int button) {

}


void ofApp::mousePressed(int x, int y, int button) {

}


void ofApp::mouseReleased(int x, int y, int button) {

}


void ofApp::windowResized(int w, int h) {

}


void ofApp::gotMessage(ofMessage msg) {

}


void ofApp::dragEvent(ofDragInfo dragInfo) { 

}