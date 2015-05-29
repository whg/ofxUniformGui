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
    
    void addShader(ofShader *shader, string filename);
    
    static ofxUniformGui* get();

    void draw(ofEventArgs &args);
    void exit(ofEventArgs &args);
    void keyPressed(ofKeyEventArgs &args);
    void keyReleased(ofKeyEventArgs &args);

    void update(ofShader *shader);

    void setVisible(bool v) { visible = v; }
    void show() { setVisible(true); }
    void hide() { setVisible(false); }
    
    void setShowKey(char k) { showKey = k; }
    
protected:
    ofxPanel panel;

    char showKey;
    bool visible;
    
    
protected:
    map<ofShader*, std::pair<string, vector<ofAbstractParameter*> > > shaders;
    
    template <typename T>
    void add(ofShader *shader, string name, T defaultValue, float min, float max) {
        shaders[shader].second.push_back(new ofParameter<T>(name, defaultValue, T(min), T(max)));
    }

};