#include "ofApp.h"


void ofApp::setup() {
    
    
    shader.load("blob.vert", "blob.frag");
    
    for (int i = 0; i < 20; things.push_back(Thing()), i++);
    
    tex.allocate(512, 1, GL_RGB32F);
    mesh = ofMesh::plane(ofGetWidth(), ofGetHeight());

    uniformGui.addShader(shader, "blob.frag");
}


void ofApp::update() {

    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    for (auto &thing : things) {
        thing.update();
    }
    
    if (tex.getWidth() < things.size()) {
        ofLogError() << "agent texture not big enough!";
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

    shader.setUniform1f("time", ofGetElapsedTimef());
    shader.setUniform2f("mouse", mouseX, mouseY);
    shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    
    shader.setUniform1i("nblobs", things.size());
    shader.setUniformTexture("tex", tex, 0);
    shader.setUniform2f("windowSize", ofGetWidth(), ofGetHeight());
    
    uniformGui.update();
    
    ofPushMatrix();
    ofTranslate(ofGetWidth() >> 1, ofGetHeight() >> 1);
    mesh.draw();
    ofPopMatrix();
    
    shader.end();
    
    uniformGui.draw();
    
}


void ofApp::keyPressed(int key) {
//    if (key == 'd') drawDebug ^= true;
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