//
//  ofxUniformGuiShader.cpp
//  ofxUniformGuiExample
//
//  Created by Will Gallia on 17/05/2015.
//
//

#include "ofxUniformGuiShader.h"

#include "ofxUniformGui.h"

bool ofxUniformGuiShader::load(string shaderName) {
    return load(shaderName + ".vert", shaderName + ".frag");
}

bool ofxUniformGuiShader::load(string vertName, string fragName, string geomName) {
    
    ofxUniformGui *ug = ofxUniformGui::get();
    
    ug->addShader(const_cast<ofxUniformGuiShader*>(this), vertName);
    ug->addShader(const_cast<ofxUniformGuiShader*>(this), fragName);
    
    if (geomName.empty() == false) {
        ug->addShader(const_cast<ofxUniformGuiShader*>(this), vertName);
    }
    
    return ofShader::load(vertName, fragName, geomName);
}

void ofxUniformGuiShader::begin() const {
    
    ofShader::begin();
    
    ofxUniformGui::get()->update(const_cast<ofxUniformGuiShader*>(this));
}
