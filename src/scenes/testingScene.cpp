//
//  testingScene.cpp
//  temptTracker021
//
//  Created by joseph saavedra on 1/6/12.
//  Copyright 2012 Saavedra. All rights reserved.
//

#include <iostream>
#include "testingScene.h"

void testingScene::setup(){
    
    BTrig.setup("catch me!", 50,50,180,180);
    //BTrig.setMaxCounter(1.0); //button sensitivity
    
    BTog.setup("toggle me off","toggle me on",false,250,250,180,180);
    
}


void testingScene::update(float eyeX, float eyeY){
    if (BTrig.update(eyeX, eyeY)){
        BTrig.x = ofRandom(180,ofGetWidth()-180);
        BTrig.y = ofRandom(180,ofGetHeight()-180);
    }
    else if (BTog.update(eyeX, eyeY)){
        BTog.x = ofRandom(180,ofGetWidth()-180);
        BTog.y = ofRandom(180,ofGetHeight()-180);
    }
}


void testingScene::draw(){
    
    BTrig.draw(); 
    BTog.draw();
    
}