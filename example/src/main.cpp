#include "ofMain.h"
#include "ofApp.h"

int main( ){

    
//    shared_ptr< ofGLProgrammableRenderer> ren = shared_ptr<ofGLProgrammableRenderer>(new ofGLProgrammableRenderer(ofGetWindowPtr()));
//    ofSetCurrentRenderer(ren);
	ofSetupOpenGL(600,600, OF_WINDOW);
	ofRunApp(new ofApp());

}
