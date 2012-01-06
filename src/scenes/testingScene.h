//
//  testingScene.h
//  temptTracker021
//
//  Created by joseph saavedra on 1/6/12.
//  Copyright 2012 Saavedra. All rights reserved.
//

#include "ofMain.h"
#include "baseScene.h"
#include "buttonTrigger.h"
#include "buttonToggle.h"

class testingScene : public baseScene{
    
    public:
    
    void setup();
    void update(float eyeX, float eyeY);
    void draw();
    
    buttonTrigger			BTrig;
    buttonToggle            BTog;
};