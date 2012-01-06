/*
 *  typingScene.cpp
 *  openFrameworks
 *
 *  Created by andrea bradshaw on 4/10/2010.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "pongScene.h"

//switch to guim
extern  int buttonCount; 

//--------------------------------------------------------------
void pongScene::setup(){
	
    ballSize = 50;
	ballPoint.set(20,20);
	
	ballVelocity.set(ofRandom(-5,5), ofRandom(2,9));
	
	fasterButton.setup("FASTER", ofGetWidth()-220,10,100,100);
	//fasterButton.setMaxCounter(1.0f);
	fasterButton.setRetrigger(true);
	
	slowerButton.setup("SLOWER", ofGetWidth()-110,10,100,100);
	//slowerButton.setMaxCounter(1.0f);
	slowerButton.setRetrigger(true);
	
    //color stuff
    rMod = ofRandom(0,200);
    gMod = ofRandom(0,200);
    bMod = ofRandom(0,200);
}
//--------------------------------------------------------------
void pongScene::update(float mouseX, float mouseY){
	float mx = mouseX;
	float my = mouseY;
	
	if (fasterButton.update(mx, my)){
		ballVelocity.x *= 1.5;
		ballVelocity.y *= 1.5;
	}
	
	if (slowerButton.update(mx, my)){
		ballVelocity.x /= 1.5;
		ballVelocity.y /= 1.5;
	}
	
	float speed = 60.0f / MAX( ofGetFrameRate() , 5);
	//float speed = 1.5f;
	
	ballPoint.x += ballVelocity.x * speed;
	ballPoint.y += ballVelocity.y * speed;
	
	if (ballPoint.x < ballSize) {
		ballPoint.x = ballSize;
		ballVelocity.x *= -1;
	}
	if (ballPoint.x > ofGetWidth()-ballSize) {
		ballPoint.x = ofGetWidth()-ballSize;
		ballVelocity.x *= -1;
	}
	if (ballPoint.y < ballSize) {
		ballPoint.y = ballSize;
		ballVelocity.y *= -1;
	}
	
	if (ballPoint.y > ofGetHeight()-95){
		float diff = rectPoint.x - ballPoint.x;
		if (fabs(diff) < 110/2){
            reColor();
			ballPoint.y = ofGetHeight()-95;
			ballVelocity.y *= -1;
		}
	}
	
	if (ballPoint.y > ofGetHeight()){
		ballPoint.x = ofRandom(0,ofGetWidth());
		ballPoint.y = 20;
		ballVelocity.set(ofRandom(-5,5), ofRandom(2,9));
		
		
		
	}
	
	
	rectPoint.x = mx;
	rectPoint.y = ofGetHeight()-40;
}	

//--------------------------------------------------------------
void pongScene::draw(){
	ofPushStyle();	
    
	ofFill();
	ofSetColor(255 - rMod, 255 - gMod, 255 - bMod);
	ofCircle(ballPoint.x, ballPoint.y, ballSize);
	
    ofSetColor(255);
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofRect(rectPoint.x, rectPoint.y, 110, 20);
	ofSetRectMode(OF_RECTMODE_CORNER);
	
    ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()), 20, 20);
	ofPopStyle();
	
	fasterButton.draw(255);
	slowerButton.draw(255);
	
	//drawCursor();
}

void pongScene::reColor(){
    
    rMod = ofRandom(0,255);
    gMod = ofRandom(0,255);
    bMod = ofRandom(0,255);
}

