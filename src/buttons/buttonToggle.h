/*
 *  buttonToggle.h
 *  openFrameworks
 *
 *  Created by theo on 17/08/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once 

#include "ofMain.h"
#include "buttonRect.h"

class buttonToggle : public buttonRect{
	
	public:
	
	buttonToggle();	
	void    setMaxCounter(float nCounter);
	void    setup( string onName, string offName,  bool startsActive, float xIn, float yIn, float w, float h);
	bool    update(float xIn, float yIn);
	bool    getState();
	void    draw(float opacity = 255);
    void    draw(string s);
	int     fromString(const std::string& s);	
    float   getY();
    float   getX();
    
    float   timeDiff;
    float   timeStamp;
    bool    firstTrigger;
    bool    turned;
    float   pct;
    
	float   preTime;
	float   counter;
	bool    hasLeft;
	float   maxCount;
	string  displayText[2];
	bool    active;
	
};