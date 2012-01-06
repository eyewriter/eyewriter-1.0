/*
 *  buttonToggle.cpp
 *  openFrameworks
 *
 *  Created by theo on 17/08/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "buttonToggle.h"
#include "testApp.h"

buttonToggle::buttonToggle(){
    
    active  = false;
    hasLeft = true;
    counter = 0.0f;
    //maxCount = ((testApp *)ofGetAppPtr())->buttonSensitivity;
    //maxCount = 1.0f;
}

void buttonToggle::setMaxCounter(float nCounter){
    maxCount = nCounter;
}

void buttonToggle::setup( string onName, string offName,  bool startsActive, float xIn, float yIn, float w, float h){
    
    maxCount = ((testApp *)ofGetAppPtr())->buttonSensitivity;
    
    displayText[1] = onName;
    displayText[0] = offName;
    
    active = startsActive;
    
    x		= xIn;
    y		= yIn;
    width	= w;
    height	= h;
}

bool buttonToggle::update(float xIn, float yIn){
    
    
    bool changed = false;		
    
    float currentTime = ofGetElapsedTimef();
    
    if( inRect(xIn, yIn) ){
        if(!turned){
            if (firstTrigger){ 
                timeStamp = currentTime;
                //cout << "hover timestamp: " << timeStamp << endl;
                turned = true;
                firstTrigger = false;
            }
        }
        
        else{ 
            float timeDiff = currentTime - timeStamp;
            //cout << "timeDiff " << timeDiff << endl;
            pct = timeDiff/maxCount;
            
            if (timeDiff >= maxCount){
                active = !active;
                changed = true;
                //cout << "BUTTON TRIGGERED" << endl;
                turned = false;
                timeStamp = currentTime;
                pct = 0.0f;
            }
        }
    }
    else { //mouse not inRect
        turned = false;
        firstTrigger = true;
        pct = 0.0f;
    }
    
    return changed;
    
    
    /*
     //---- old, uses fps
     bool changed = false;
     
     float amntShouldHappened = 60.0f;
     
     float currentTime = ofGetElapsedTimef();
     float diff = currentTime - preTime;
     if( diff <= 0.0001 ){
     diff = 0.0001;
     }
     
     float fps = ofClamp(1.0/diff, 2, 60.0);
     //cout << "fps " << fps << endl;
     
     float update = amntShouldHappened / fps;
     
     if( inRect(xIn, yIn) ){
     
     if( hasLeft ){
     counter += 0.6f*update;
     //cout << "TOGGLE counter is " << counter << endl;
     cout << "TOGGLE diff is " << diff << endl;
     if(counter >= maxCount ){
     active  = !active;
     counter = 0.0f;
     
     hasLeft = false;
     changed = true;
     }
     }
     }else{
     if( !hasLeft ){
     hasLeft = true;
     }else{
     counter *= 0.93f/update;
     }
     }
     
     preTime = ofGetElapsedTimef();
     
     return changed;
     */
}	

bool buttonToggle::getState(){
    return active;
}

void buttonToggle::draw(float opacity){
    ofFill();
    
    float pctActive = ofMap(pct, 0.0, 1.5, 0.0, 110.0);			
    if( !active ){
        ofSetColor(160 - pctActive, 160 + pctActive, 160 - pctActive, opacity);
        //ofSetColor(180 - pctActive, 180.0, 180 - pctActive);
    }else{
        ofSetColor(10 + pctActive, 240 - pctActive, 10 + pctActive, opacity);
        //ofSetColor(100 + pctActive, 180, 100 + pctActive);
    }
    ofRect(x, y, width, height); 
    
    ofNoFill();
    ofSetColor(30, 30, 30, opacity);
    ofRect(x, y, width, height); 
    
    float textWidth = 8.0f * displayText[active].length();
    float remainX = (width - textWidth)/2;
    
    float textHeight = 14.0f;
    float remainY = (height - textHeight)/2.0f + (textHeight/2.0f);
    
    ofSetColor(100, 100, 160, opacity);
    ofDrawBitmapString(displayText[active], x + remainX, y + remainY);
}

int buttonToggle::fromString(const std::string& s){
    std::istringstream stream (s);
    int t;
    stream >> t;
    return t;
}

void buttonToggle::draw(string s){
    
    ofFill();
    ofSetColor(fromString(s));
    
    float pctActive = ofMap(pct, 0.0, 1.5, 0.0, 110.0);		
    ofRect(x, y, width, height); 
    if (pct>.1){
        ofPushStyle();
        ofSetLineWidth(4);
        ofNoFill();
        
        ofRect(x, y, width, height); 
        ofPopStyle();
    }
}

float buttonToggle::getY(){
    return y;
}

float buttonToggle::getX(){
    return x;
}

