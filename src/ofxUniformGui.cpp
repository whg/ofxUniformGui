//
//  ofxUniformGui.cpp
//
//  Created by Will Gallia on 12/05/2015.
//

#include "ofxUniformGui.h"

#include "ofShader.h"
#include "Poco/RegularExpression.h"

using Poco::RegularExpression;

// it would be nice if a shared_ptr would work here, but I can't manage to stop ~ofxPanel from
// crashing when we destruct ofxUniformGui

static ofxUniformGui *uniformGui = NULL;
//shared_ptr<ofxUniformGui> uniformGui;

ofxUniformGui::ofxUniformGui() {
    panel.setup("Shader Uniforms");
    
//
    ofAddListener(ofEvents().draw, this, &ofxUniformGui::draw);
    ofAddListener(ofEvents().exit, this, &ofxUniformGui::exit);
    ofRegisterKeyEvents(this);
    
    cout << "constructed ofxuniformgui\n";

    showKey = 'u';
    visible = true;
}

ofxUniformGui::~ofxUniformGui() {
    for (auto fandp : shaders) {
        vector<ofAbstractParameter*> params = fandp.second.second;
        
        for (auto param : params) {
            delete param;
        }
    }
    cout << "desctructed ofxuniformgui\n";
}

ofxUniformGui* ofxUniformGui::get() {
    if (!uniformGui) {
        uniformGui = new ofxUniformGui;
    }
    return uniformGui;
}

void ofxUniformGui::exit(ofEventArgs &args) {
    if (uniformGui) {
        delete uniformGui;
    }
}

void ofxUniformGui::addShader(const ofShader *shader, string filename) {
    
    ofFile file(filename);
    
    shaders[shader].first = filename;
    
    static string tokens[] = { "line", "type", "name", "default", "min", "max" };
    static int NTOKENS = 6;
    
    RegularExpression re("^\\s*uniform\\s+([^\\s]+)\\s+([^\\s;]+)\\s*=\\s*([vec0-9., ()]+)\\s*;\\s*//[\\sa-zA-z]*([0-9.]+)\\s*-\\s*([0-9.]+).*");
    vector<RegularExpression::Match> matches;
    
    string line;
    
    while(std::getline(file, line)) {
    
        re.match(line, 0, matches);
        
        if (matches.size() >= NTOKENS) {
            
            map<string, string> values;
            for (int i = 0; i < NTOKENS; i++) {
                values[tokens[i]] = line.substr(matches[i].offset, matches[i].length);
            }
            
            ofLogNotice() << line;
            
            float min = atof(values["min"].c_str());
            float max = atof(values["max"].c_str());
            
            if (values["type"].find("vec") == string::npos) {
                
                // primitive types
            
                if (values["type"] == "int") {
                    int def = atoi(values["default"].c_str());
                    add(shader, values["name"], def, min, max);
                }
                else if (values["type"] == "float") {
                    float def = atof(values["default"].c_str());
                    add(shader, values["name"], def, min, max);
                }
            }
            else {
                if (values["type"] == "vec2") {
                    RegularExpression vec2Re("vec2\\(([0-9.]+)\\s*,\\s*([0-9.]+)\\)");
                    vec2Re.match(values["default"], 0, matches);
                    
                    if (matches.size() >= 3) {
                        string smin = values["default"].substr(matches[1].offset, matches[1].length);
                        string smax = values["default"].substr(matches[2].offset, matches[2].length);
                        ofVec2f def(atof(smin.c_str()), atof(smax.c_str()));
                        
                        add(shader, values["name"], def, min, max);
                    }
                    else {
                        ofLogError() << "can't get default values of vec2 " << values["name"];
                    }
                    
                }
            }
            
            
            
        }
    }
    
    ofParameterGroup paramGroup;
    paramGroup.setName(filename);

    for (auto param : shaders[shader].second) {
        paramGroup.add(*param);
    }
    panel.add(paramGroup);

}

ofParameterGroup& ofxUniformGui::getShader(string name) {
    
}

void ofxUniformGui::update(const ofShader *shader) {
//    for (auto fandp : shaders) {
//        const ofShader *shader = fandp.first;
    vector<ofAbstractParameter*> params = shaders[shader].second;
    
        for (auto param : params) {
            
            string name = param->getName();
            if (ofParameter<float> *fp = dynamic_cast< ofParameter<float>* >(param)) {
                shader->setUniform1f(name, fp->get());
            }
            else if (ofParameter<ofVec2f> *v2p = dynamic_cast< ofParameter<ofVec2f>* >(param)) {
                shader->setUniform2f(name, v2p->get());
            }
        
        }
//    }
}


void ofxUniformGui::draw(ofEventArgs &args) {
    if (visible) {
        panel.draw();
    }
}

void ofxUniformGui::keyPressed(ofKeyEventArgs &args) {
    if (args.key == int(showKey)) {
        visible ^= true;
    }
    
}

void ofxUniformGui::keyReleased(ofKeyEventArgs &args) { }

//void ofxUniformGui::draw() {
//    panel.draw();
//}
