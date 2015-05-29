//
//  Created by Will Gallia on 17/05/2015.
//

#pragma once

#include "ofShader.h"

class ofxUniformGuiShader : public ofShader {
    
public:
    bool load(string shaderName);
    bool load(string vertName, string fragName, string geomName="");
    
#if (OF_VERSION_MINOR== 8 && OF_VERSION_PATCH >= 4) || OF_VERSION_MAJOR > 8
    void begin() const;
#else
    void begin();
#endif
};