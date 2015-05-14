//
//  ofxUniformGui.cpp
//  emptyExample
//
//  Created by Will Gallia on 12/05/2015.
//
//

#include "ofxUniformGui.h"


#include "ofShader.h"
#include "Poco/RegularExpression.h"


using Poco::RegularExpression;


void ofxUniformGui::addShader(ofShader &shader, string filename) {
    
    ofFile file(filename);
    
    shaders[filename].first = &shader;
    
    static string tokens[] = { "line", "type", "name", "default", "min", "max" };
    static int NTOKENS = 6;
    
    RegularExpression re("^\\s*uniform\\s+([^\\s]+)\\s+([^\\s;]+)\\s*=\\s*([0-9.]+)\\s*;\\s*//[\\sa-zA-z]*([0-9.]+)\\s*-\\s*([0-9.]+).*$");
    vector<RegularExpression::Match> matches;
    
    string line;
    
    while(std::getline(file, line)) {
    
        re.match(line, 0, matches);
        
        
        
        if (matches.size() >= NTOKENS) {
            
            map<string, string> values;
            for (int i = 0; i < NTOKENS; i++) {
                values[tokens[i]] = line.substr(matches[i].offset, matches[i].length);
            }
            
            
            float min = atof(values["min"].c_str());
            float max = atof(values["max"].c_str());
            
            if (values["type"] == "int") {
                int def = atoi(values["default"].c_str());
                add(filename, values["name"], def, min, max);
            }
            else if (values["type"] == "float") {
                float def = atof(values["default"].c_str());
                add(filename, values["name"], def, min, max);
            }
            
        }
    }
    
    panel.setup("Shader Uniforms");
//    for (auto param : params) {
//        string filename = param.first;
//        auto parameterList = param.second;
//        
//        ofParameterGroup paramGroup;
//        paramGroup.setName(filename);
//        for (auto p : parameterList) {
//            paramGroup.add(*p);
//        }
//        panel.add(paramGroup);
//
//    }

    ofParameterGroup paramGroup;
    paramGroup.setName(filename);

    for (auto param : shaders[filename].second) {

//        for (auto p : parameterList) {
        paramGroup.add(*param);
//        }

        
    }
    panel.add(paramGroup);

}

ofParameterGroup& ofxUniformGui::getShader(string name) {
    
}

void ofxUniformGui::update() {
    for (auto fandp : shaders) {
        ofShader *shader = fandp.second.first;
        vector<ofAbstractParameter*> params = fandp.second.second;
        
        for (auto param : params) {
            ofParameter<float> *p = (ofParameter<float>*) param;
            shader->setUniform1f(p->getName(), p->get());
        }
    }
}

void ofxUniformGui::draw() {
    panel.draw();
}
