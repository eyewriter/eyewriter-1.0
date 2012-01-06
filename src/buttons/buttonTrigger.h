/*
 *  buttonTrigger.h
 *  openFrameworks
 *
 *  Created by theo on 17/08/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once 

#include "ofMain.h"
#include "buttonRect.h"
//#include "trackingManager.h"

class buttonTrigger : public buttonRect{
	
	public:
	
	buttonTrigger();
    //~buttonTrigger();
    
    void    setup();
    void    setup( string onName, float xIn, float yIn, float w, float h );
	void    setDisplayFont(ofTrueTypeFont * fontIn);
	void    setRetrigger(bool retrigger);
	void    setMaxCounter(float nCounter);
    int     getNumTriggers();
	void    setFlashLength(float timeF);
	bool    update(float xIn, float yIn);
	void    draw(float opacity = 255);
    float   getY();
    float   getX();
    
	int     fromString(const std::string& s);	
	void    draw(string s);	
	int     numTriggers;
    bool    firstTrigger;
	
	float   preTime;
	float   maxCount;
    float   buttonPressTimer;
    float   timeStamp;
	
	float   flashLength;
	bool    bFlash;
	float   flashTill;
	
	bool    allowRetrigger;
	float   pct;
	bool    trigger;
	float   counter;
	bool    hasLeft;
	string  displayText;
	bool    active;
	
	ofTrueTypeFont * font;
	bool    bHasFont;
	
};