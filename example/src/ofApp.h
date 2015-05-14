#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "ofxUniformGui.h"

struct Thing {
    ofVec2f pos, vel;
    Thing() {
        pos = ofVec2f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
        float d = 3;
        vel = ofVec2f(ofRandom(-d, d), ofRandom(-d, d));
    }
    
    void update() {
        pos+= vel;
        
        if (pos.x < 0 || pos.x > ofGetWidth()) vel.x*= -1;
        if (pos.y < 0 || pos.y > ofGetHeight()) vel.y*= -1;
    }
    
};

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofShader shader;
    ofxUniformGui uniformGui;
    
    vector<Thing> things;
    ofTexture tex;
    ofMesh mesh;
};
