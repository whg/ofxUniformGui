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
    
    ug->addShader(this, vertName);
    ug->addShader(this, fragName);
    
    if (geomName.empty() == false) {
        ug->addShader(this, vertName);
    }
    
    return ofShader::load(vertName, fragName, geomName);
}

#if (OF_VERSION_MINOR== 8 && OF_VERSION_PATCH >= 4) || OF_VERSION_MAJOR > 8
void ofxUniformGuiShader::begin() const {
#else
void ofxUniformGuiShader::begin() {
#endif
    
    ofShader::begin();
    
    ofxUniformGui::get()->update((ofShader*)this);
}
