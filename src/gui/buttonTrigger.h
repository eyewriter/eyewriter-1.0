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
	
	buttonTrigger(){
		active  = false;
		hasLeft = true;
		counter = 0.0f;
		pct = 0.0f;
        maxCount = 3.0f;
        //maxCount = ((trackingManager*)ofGetAppPtr())->buttonPressTime;
		//maxCount = buttonPressTimer; //this is set from controlPanel
		allowRetrigger = false;
		numTriggers = 0;
		bFlash = false;
		bHasFont = false;
		
	}
	
	void setDisplayFont(ofTrueTypeFont * fontIn){
		font = fontIn;
		bHasFont = true;
	}
		
	void setRetrigger(bool retrigger){
		allowRetrigger = retrigger;
	}

	void setMaxCounter(float nCounter){
		maxCount = nCounter;
	}
	
	void setup( string onName, float xIn, float yIn, float w, float h ){
		displayText = onName;
		
		x		= xIn;
		y		= yIn;
		width	= w;
		height	= h;
		numTriggers = 0;
		flashLength = 0.2;
	}

	int getNumTriggers(){
		if( allowRetrigger ){
			return numTriggers;
		}else{
			return 0;
		}
	}
	
	void setFlashLength(float timeF){
		flashLength = MAX(0, timeF);
	}

	bool update(float xIn, float yIn){
		//printf("fuck!\n");
	
        //maxCount = buttonPressTimer; 
        
		bool changed = false;		
        
        float currentTime = ofGetElapsedTimef();
        
        if( inRect(xIn, yIn) ){
            if(!active){
                timeStamp = currentTime;
                cout << "hover timestamp: " << timeStamp << endl;
                active = true;
            }
            
            else if (active){
                float timeDiff = currentTime - timeStamp;
                //cout << "timeDiff " << timeDiff << endl;
                pct = timeDiff/maxCount;
                if (timeDiff >= maxCount){
                    cout << "BUTTON TRIGGERED" << endl;
                    bFlash = true;
					flashTill = ofGetElapsedTimef() + flashLength;
                    active = false;
                    changed = true;
                }
            }
        }
        else { //mouse not inRect
            active = false;
            pct = 0;
        }
        
		if( bFlash && ofGetElapsedTimef() > flashTill ){
			bFlash = false;
		}   
        
        return changed;
        /*float amntShouldHappened = 60.0f;
		
		float currentTime = ofGetElapsedTimef();
		float diff = currentTime - preTime;
		if( diff <= 0.0001 ){
			diff = 0.0001;
		}
        
		float fps = ofClamp(1.0/diff, 2, 60.0);
		float update = amntShouldHappened / fps;
        
		//printf("Diff is %f fps is %f\n", diff, fps);
	
		pct *= 0.85f/update;
		
		if( inRect(xIn, yIn) ){
			
			if( hasLeft || allowRetrigger ){
				counter += 0.125f*update;
                //cout << "TRIGGER counter is " << counter << endl;
                //cout << "TRIGGER preTime is " << preTime << endl;
				pct = counter;
				if(counter >= maxCount ){					
					hasLeft = false;
					changed = true;
					if( allowRetrigger ){
						counter = 0.0;
						numTriggers++;
					}
				
					bFlash = true;
					flashTill = ofGetElapsedTimef() + flashLength;
				}
			}
		}else{
			numTriggers = 0;
			if( !hasLeft ){
				hasLeft = true;
			}else{
				counter *= 0.93f / update;
			}
		}
		
		if( bFlash && ofGetElapsedTimef() > flashTill ){
			bFlash = false;
		}
		
		preTime = ofGetElapsedTimef();
		
         */
	}	
	
	void draw(float opacity = 255){
		ofFill();
		
		float pctActive = ofMap(pct, 0.0, maxCount, 0.0, 110.0);		
		
		//pctActive = ofClamp(pctActive, 0, 110.0);	
		if( bFlash){
			ofSetColor(0, 100, 240, opacity);
		}else{
			ofSetColor(120 - pctActive, 120+pctActive*2, 120 - pctActive, opacity);
		}
		
		ofRect(x, y, width, height); 

		ofNoFill();
		ofSetColor(30, 30, 30, opacity);
		ofRect(x, y, width, height); 

		if (!bHasFont){
			float textWidth = 8.0f * displayText.length();
			float remainX = (width - textWidth)/2;
			
			float textHeight = 14.0f;
			float remainY = (height - textHeight)/2.0f + (textHeight/2.0f);
			
			ofSetColor(100, 100, 160);
			ofDrawBitmapString(displayText, x + remainX, y + remainY);
		} else {
			ofRectangle bounds = font->getStringBoundingBox(displayText, 0,0);
			
			float textWidth = bounds.width;
			float remainX = (width - textWidth)/2;
			
			float textHeight = bounds.height;
			float remainY = (height - textHeight)/2.0f + (textHeight/2.0f);
			ofSetColor(60, 60, 60);
			font->drawString(displayText, x + remainX, y + remainY);
		}

		//ofDrawBitmapString("pctActive is" +ofToString(pct), 200, y);
	}
	
	int fromString(const std::string& s)
	{
		std::istringstream stream (s);
		int t;
		stream >> t;
		return t;
	}
	
	void draw(string s){
		
		ofFill();
		ofSetColor(fromString(s));
		
		float pctActive = ofMap(pct, 0.0, maxCount, 0.0, 110.0);		
		ofRect(x, y, width, height); 
		if (pct>.1){
			ofPushStyle();
			ofSetLineWidth(4);
			ofNoFill();
			
			if( bFlash){
				ofSetColor(0, 100, 240);
			}else{
				ofSetColor(120+pctActive*2, 120+pctActive*2, 120 + pctActive*2, 255);
			}
				
			ofRect(x, y, width, height); 
			ofPopStyle();
		}
	}
	
	
	int     numTriggers;
	
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