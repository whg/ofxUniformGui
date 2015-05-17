//
//  ofxUniformGui.h
//  Created by Will Gallia on 12/05/2015.
//

#pragma once

#include "ofxGui.h"

class ofxUniformGui {
public:
    ofxUniformGui();
    ~ofxUniformGui();
    
    ofxPanel panel;
        
    void addShader(const ofShader *shader, string filename);
    
    ofParameterGroup& getShader(string name);
    
    map<const ofShader*, std::pair<string, vector<ofAbstractParameter*> > > shaders;

    template <typename T>
    void add(const ofShader *shader, string name, T defaultValue, float min, float max) {
        shaders[shader].second.push_back(new ofParameter<T>(name, defaultValue, T(min), T(max)));
    }
    
    
    static ofxUniformGui* get();
//    static shared_ptr<ofxUniformGui> get();

    void draw(ofEventArgs &args);
    void exit(ofEventArgs &args);
    void keyPressed(ofKeyEventArgs &args);
    void keyReleased(ofKeyEventArgs &args);

    void update(const ofShader *shader);


    void setVisible(bool v) { visible = v; }
    void show() { setVisible(true); }
    void hide() { setVisible(false); }
    
protected:
    char showKey;
    bool visible;
};