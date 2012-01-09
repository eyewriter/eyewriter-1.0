//
//  eyeOsc.cpp
//  temptTracker021
//
//  Created by joseph saavedra on 1/5/12.
//  Copyright 2012 Saavedra. All rights reserved.
//

#include <iostream>
#include "eyeOsc.h"

void eyeOsc::setup(){
    
    ofxXmlSettings XML;
	XML.loadFile("settings/globalSettings.xml"); //in app/bin/data/settings
	HOST = XML.getValue("app:osc:host", "");
    PORT = XML.getValue("app:osc:port", 0);
    
	// open an outgoing connection to HOST:PORT
	sender.setup( HOST, PORT );
    
}
void eyeOsc::update(float eyeX, float eyeY){
    x = eyeX;
    y = eyeY;
    
    ofxOscMessage mX;
	mX.setAddress( "/eye/pos/x" );
	mX.addIntArg( x );
	sender.sendMessage( mX );
    
    ofxOscMessage mY;
	mY.setAddress( "/eye/pos/y" );
	mY.addIntArg( y );
	sender.sendMessage( mY );
    //cout << "x: " << x << " y: " << y << endl;
    
    //need to add message for eye BLINK
}
void eyeOsc::draw(){
    
    ofFill();
    ofSetColor(255,255,255);
    ofDrawBitmapString( ">>> eyeOSC <<<", 10, 20 );
   	string info;
	info = "sending osc messages to: " + string( HOST ) + " on port: " + ofToString( PORT );
	ofDrawBitmapString( info, 10, 40 );

    ofDrawBitmapString( "/eye/pos/x " + ofToString(x), x + 50, y );
    ofDrawBitmapString( "/eye/pos/y " + ofToString(y), x, y - 50 );
}

void eyeOsc::dragEvent(ofDragInfo dragInfo){
    
}
void eyeOsc::gotMessage(ofMessage msg){
    
    
}