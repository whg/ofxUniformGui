//
//  ofxUniformGui.h
//  Created by Will Gallia on 12/05/2015.
//

#pragma once

#include "ofxGui.h"


class ofxUniformGui {
public:
    ofxUniformGui();
    
    ofxPanel panel;
        
    void addShader(ofShader &shader, string filename);
    
    ofParameterGroup& getShader(string name);
    
    map<string, std::pair<ofShader*, vector<ofAbstractParameter*> > > shaders;
//    map<string, vector<ofAbstractParameter*> > params;


    template <typename T>
    void add(string filename, string name, T defaultValue, float min, float max) {
        shaders[filename].second.push_back(new ofParameter<T>(name, defaultValue, T(min), T(max)));
    }
    
    
    
    void update();
    void draw();

};