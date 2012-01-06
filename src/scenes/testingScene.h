//
//  testingScene.h
//  temptTracker021
//
//  Created by joseph saavedra on 1/6/12.
//  Copyright 2012 Saavedra. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "baseScene.h"
#include "buttonTrigger.h"
#include "buttonToggle.h"


class testingScene : public baseScene{
    
    public:
    
    void setup();
    void update(float eyeX, float eyeY);
    void draw();
    void mouseDragged(int x, int y, int button);
    
    buttonTrigger       BTrig;
    buttonToggle        BTog;
    
    buttonTrigger       decSensitivity;
    buttonTrigger       incSensitivity;
    
    float               currSensitivity;
};
