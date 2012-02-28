//
//  mouseControl.cpp
//  mouseControlExample
//
//  Created by joseph saavedra on 1/9/12.

/*

 derived from examples found
 here: http://stackoverflow.com/questions/2734117/simulating-mouse-input-programmatically-in-os-x
 and here: http://stackoverflow.com/questions/4051587/apple-events-to-control-mouse-remotely

*/

#include <iostream>
#include "mouseControl.h"

mouseControl::mouseControl(){

}

void mouseControl::setup(){
    mLeftButton = false;
    mRightButton = false;
    draggingLeftButton = false;
    draggingRightButton = false;

    #ifdef TARGET_OSX
    eventTypeMouseMoved = kCGEventMouseMoved;
    eventTypeLeftDragged = kCGEventLeftMouseDragged;
    eventTypeLeftMouseDown = kCGEventLeftMouseDown;
    eventTypeLeftMouseUp = kCGEventLeftMouseUp;

    eventTypeRightDragged = kCGEventRightMouseDragged;
    eventTypeRightMouseDown = kCGEventRightMouseDown;
    eventTypeRightMouseUp = kCGEventRightMouseUp;
    #endif
    //clickable rectangles
    rect_size = 100;
    rect1_x = ofRandom(rect_size, ofGetWidth()-rect_size);
    rect1_y = ofRandom(rect_size, ofGetHeight()-rect_size);
    rect2_x = ofRandom(rect_size, ofGetWidth()-rect_size);
    rect2_y = ofRandom(rect_size, ofGetHeight()-rect_size);

    rect1L = false;
    rect2L = false;
    rect1R = false;
    rect2R = false;

    //colors
    on.r=0;
    on.g=0;
    on.b=255;

    off.r=255;
    off.g=0;
    off.b=0;

    myMouse.x = ofGetWidth()/2;
    myMouse.y = ofGetHeight()/2;
}

void mouseControl::update(ofPoint myMouse){

    //check to see if the mouse has moved -- if so, run move(_myMouse)
    if(myMouse.x != prevMyMouse.x || myMouse.y != prevMyMouse.y){
        myMouseMoved = true;
        prevMyMouse = myMouse;
    } else myMouseMoved = false;

    if(myMouseMoved){
        move(myMouse);
    }
}

void mouseControl::draw(){
    //ofBackground(255);
    cout << "mouseScene DRAWING" << endl;
    ofSetColor(255);
    ofDrawBitmapString(">>> MOUSE CONTROL <<<", 50,30);
    ofDrawBitmapString("use UP, DOWN, LEFT, RIGHT arrows to move mouse", 50,50);
    ofDrawBitmapString("hit '1' to left click // hold '1' and move to drag", 50,70);
    ofDrawBitmapString("hit '2' to right click", 50,90);
    ofDrawBitmapString("click me!", rect1_x, rect1_y-10);
    ofDrawBitmapString("click me!", rect2_x, rect2_y-10);
    ofDrawBitmapString(event, ofGetWidth()/2+30, 50);


    ofSetColor(off);
    if(rect1L) ofSetColor(on);
    else if(rect1R) ofSetColor(100,255,100);
    ofRect(rect1_x, rect1_y, rect_size, rect_size);

    ofSetColor(off);
    if(rect2L) ofSetColor(on);
    else if(rect2R) ofSetColor(100,255,100);
    ofRect(rect2_x, rect2_y, rect_size, rect_size);
}

void mouseControl::keyPressed(int key){

    switch (key){
        case	OF_KEY_LEFT:
            myMouse.x -= 10;
            if(getLeftButton()){ //if getLeftButton == true, we're dragging
                leftMouseDragged(myMouse);
            } else move(myMouse);
			break;

        case	OF_KEY_RIGHT:
            myMouse.x += 10;
            if(getLeftButton()){ //if getLeftButton == true, we're dragging
                leftMouseDragged(myMouse);
            }else move(myMouse);
			break;

        case	OF_KEY_UP:
            myMouse.y -= 10;
            if(getLeftButton()){ //if getLeftButton == true, we're dragging
                leftMouseDragged(myMouse);
            }else move(myMouse);
			break;

        case	OF_KEY_DOWN:
            myMouse.y += 10;
            if(getLeftButton()){ //if getLeftButton == true, we're dragging
                leftMouseDragged(myMouse);
            }else move(myMouse);
			break;
        case    '1':
            leftButtonDown(myMouse);
            break;

        case    '2':
            rightButtonDown(myMouse);
            break;
    }
}

void mouseControl::keyReleased(int key){
    switch (key){
        case    '1':
            leftButtonUp(myMouse);
            break;
        case    '2':
            rightButtonUp(myMouse);
            break;
    }
}

void mouseControl::mouseMoved(int x, int y ){
    event = "mouse moved x: " + ofToString(x) + " y: " + ofToString(y);
}
void mouseControl::mouseDragged(int x, int y, int button){
    if(button == 0){
        event = "left mouse button dragged x: " + ofToString(x) + " y: " + ofToString(y);
        cout << event << endl;

        if(rect1L){
            rect1_x = x - rect_size/2;
            rect1_y = y - rect_size/2;
        }
        else if(rect2L){
            rect2_x = x - rect_size/2;
            rect2_y = y - rect_size/2;
        }
    }

}
void mouseControl::mousePressed(int x, int y, int button){
    if(button == 0){
        event = "left mouse button pressed x: " + ofToString(myMouse.x) + " y: " + ofToString(myMouse.y);
        if(x > rect1_x && x < rect1_x+rect_size && y > rect1_y && y < rect1_y+rect_size){
            rect1L = true;
        } else rect1L = false;

        if(x > rect2_x && x < rect2_x+rect_size && y > rect2_y && y < rect2_y+rect_size){
            rect2L = true;
        } else rect2L = false;
    }
    else if(button == 2){
        event = "right mouse button pressed x: " + ofToString(myMouse.x) + " y: " + ofToString(myMouse.y);
        if(x > rect1_x && x < rect1_x+rect_size && y > rect1_y && y < rect1_y+rect_size){
            rect1R = true;
        } else rect1R = false;

        if(x > rect2_x && x < rect2_x+rect_size && y > rect2_y && y < rect2_y+rect_size){
            rect2R = true;
        } else rect2R = false;
    }

}
void mouseControl::mouseReleased(int x, int y, int button){
    //left button released
    if(button == 0){
        rect1L = false;
        rect2L = false;

    } else if(button == 2){
        rect1R = false;
        rect2R = false;
    }
}



//---------------------------------------------------
//---------- mouse control functions ----------------
//---------------------------------------------------

void mouseControl::move(ofPoint myMouse){
    mouseCursorPosition.x = myMouse.x;
    mouseCursorPosition.y = myMouse.y;

     #ifdef TARGET_OSX
    mouseEventMove = CGEventCreateMouseEvent ( CGEventSourceCreate(NULL),
                                                         eventTypeMouseMoved,
                                                         mouseCursorPosition,
                                                         kCGMouseButtonLeft);//ignored
                                                //kCGMouseButtonRight);
                                                  //kCGMouseButtonLeft);
    CGEventSetType(mouseEventMove, kCGEventMouseMoved); // Fix Apple Bug
    CGEventPost( kCGSessionEventTap, mouseEventMove );

    //if(ofGetElapsedTimef() > 1000)
       CFRelease(mouseEventMove);
       #endif
}

//-------- left mouse button -------------------

void mouseControl::leftButtonDown(ofPoint myMouse){

    mouseCursorPosition.x = myMouse.x;
    mouseCursorPosition.y = myMouse.y;
     #ifdef TARGET_OSX
    CGMouseButton mouseButton = kCGMouseButtonLeft;

    mouseEventLeftDown = CGEventCreateMouseEvent (  CGEventSourceCreate(NULL),
                                                 eventTypeLeftMouseDown,
                                                 mouseCursorPosition,
                                                 kCGMouseButtonLeft );
    CGEventSetType(mouseEventLeftDown, kCGEventLeftMouseDown); // Fix Apple Bug
    CGEventPost( kCGSessionEventTap, mouseEventLeftDown );

    CFRelease(mouseEventLeftDown);
    #endif
    mLeftButton = true;
}

void mouseControl::leftButtonUp(ofPoint myMouse){

    mouseCursorPosition.x = myMouse.x;
    mouseCursorPosition.y = myMouse.y;
     #ifdef TARGET_OSX
    CGMouseButton mouseButton = kCGMouseButtonLeft;

    mouseEventLeftUp = CGEventCreateMouseEvent (  CGEventSourceCreate(NULL),
                                                  eventTypeLeftMouseDown,
                                                  mouseCursorPosition,
                                                  kCGMouseButtonLeft );
    CGEventSetType(mouseEventLeftUp, kCGEventLeftMouseUp); // Fix Apple Bug
    CGEventPost( kCGSessionEventTap, mouseEventLeftUp );

    CFRelease(mouseEventLeftUp);
    mLeftButton = false;
    if(draggingLeftButton){
        CFRelease(mouseEventLeftDragged);
        draggingLeftButton = false;
    }
    #endif
}

bool mouseControl::getLeftButton(){
    return mLeftButton;
}


//-------- right mouse press -------------------

void mouseControl::rightButtonDown(ofPoint myMouse){
    mouseCursorPosition.x = myMouse.x;
    mouseCursorPosition.y = myMouse.y;
     #ifdef TARGET_OSX
    CGMouseButton mouseButton = kCGMouseButtonRight;

    mouseEventRightDown = CGEventCreateMouseEvent (  CGEventSourceCreate(NULL),
                                                 eventTypeRightMouseDown,
                                                 mouseCursorPosition,
                                                 kCGMouseButtonRight );
    CGEventSetType(mouseEventRightDown, kCGEventRightMouseDown); // Fix Apple Bug
    CGEventPost( kCGSessionEventTap, mouseEventRightDown );
    CFRelease(mouseEventRightDown);
    #endif
    mRightButton = true;
}

void mouseControl::rightButtonUp(ofPoint myMouse){
    mouseCursorPosition.x = myMouse.x;
    mouseCursorPosition.y = myMouse.y;
     #ifdef TARGET_OSX
    CGMouseButton mouseButton = kCGMouseButtonRight;

    mouseEventRightUp = CGEventCreateMouseEvent (  CGEventSourceCreate(NULL),
                                                      eventTypeRightMouseUp,
                                                      mouseCursorPosition,
                                                      kCGMouseButtonRight );
    CGEventSetType(mouseEventRightUp, kCGEventRightMouseUp); // Fix Apple Bug
    CGEventPost( kCGSessionEventTap, mouseEventRightUp );
    CFRelease(mouseEventRightUp);
    mRightButton = false;
    if(draggingRightButton){
        CFRelease(mouseEventRightDragged);
        draggingRightButton = false;
    }
    #endif
}

bool mouseControl::getRightButton(){
    return mRightButton;
}



//------- mouse dragged ------------------------

void mouseControl::leftMouseDragged(ofPoint myMouse){
    mouseCursorPosition.x = myMouse.x;
    mouseCursorPosition.y = myMouse.y;
     #ifdef TARGET_OSX
    CGMouseButton mouseButton = kCGMouseButtonLeft;

    mouseEventLeftDragged = CGEventCreateMouseEvent (  CGEventSourceCreate(NULL),
                                                     eventTypeLeftDragged,
                                                     mouseCursorPosition,
                                                     kCGMouseButtonLeft );
    CGEventSetType(mouseEventLeftDragged, kCGEventLeftMouseDragged); // Fix Apple Bug
    CGEventPost( kCGSessionEventTap, mouseEventLeftDragged );
     #endif
    draggingLeftButton = true;
}

void mouseControl::rightMouseDragged(ofPoint myMouse){

    mouseCursorPosition.x = myMouse.x;
    mouseCursorPosition.y = myMouse.y;
     #ifdef TARGET_OSX
    CGMouseButton mouseButton = kCGMouseButtonRight;

    mouseEventRightDragged = CGEventCreateMouseEvent (  CGEventSourceCreate(NULL),
                                                      eventTypeRightDragged,
                                                      mouseCursorPosition,
                                                      kCGMouseButtonRight );
    CGEventSetType(mouseEventRightDragged, kCGEventRightMouseDragged); // Fix Apple Bug
    CGEventPost( kCGSessionEventTap, mouseEventRightDragged );
    #endif
    draggingRightButton = true;

}
