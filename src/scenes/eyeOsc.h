//
//  eyeOsc.h
//  temptTracker021
//
//  Created by joseph saavedra on 1/5/12.
//  Copyright 2012 Saavedra. All rights reserved.
//

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"
#include "baseScene.h"

//--------------------------------------------------------
class eyeOsc : public baseScene{
    
public:
    
    void setup();
    void update(float eyeX, float eyeY);
    void draw();
    
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);		
    
    ofTrueTypeFont		font;
    
    int x;
    int y;
    
    ofxOscSender    sender;

    string          HOST;
    int             PORT;
    
};