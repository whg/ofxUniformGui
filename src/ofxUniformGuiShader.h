//
//  Created by Will Gallia on 17/05/2015.
//

#pragma once

#include "ofShader.h"

class ofxUniformGuiShader : public ofShader {
    
public:
    bool load(string vertName, string fragName, string geomName="");
    
    void begin() const;
};