//
//  mouseControl.h
//  mouseControlExample
//
//  Created by joseph saavedra on 1/9/12.

#pragma once
#include "ofMain.h"
#ifdef TARGET_OSX
#include <ApplicationServices/ApplicationServices.h>
#include <unistd.h>
#endif


#include "baseScene.h"

class mouseControl : public baseScene{

public:

    mouseControl();
    void setup();
    void draw();
    void update(ofPoint myMouse);
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    void move(ofPoint myMouse);
    void leftButtonUp(ofPoint myMouse);
    void leftButtonDown(ofPoint myMouse);
    void rightButtonUp(ofPoint myMouse);
    void rightButtonDown(ofPoint myMouse);
    void leftMouseDragged(ofPoint myMouse);
    void rightMouseDragged(ofPoint myMouse);

    bool mLeftButton;
    bool getLeftButton();
    bool mRightButton;
    bool getRightButton();

    bool draggingLeftButton;
    bool draggingRightButton;


    #ifdef TARGET_OSX
    CGEventSourceRef source;

    CGPoint mouseCursorPosition;

    //event refs
    CGEventRef mouseEventMove;
    CGEventRef mouseEventLeftDown;     //left click down
    CGEventRef mouseEventLeftUp;       //left click up
    CGEventRef mouseEventLeftDragged; //left dragged
    CGEventRef mouseEventRightDown;     //left click down
    CGEventRef mouseEventRightUp;       //left click up
    CGEventRef mouseEventRightDragged; //left dragged

    //event types
    CGEventType eventTypeMouseMoved;
    CGEventType eventTypeLeftMouseDown;
    CGEventType eventTypeLeftMouseUp;
    CGEventType eventTypeLeftDragged;
    CGEventType eventTypeRightMouseDown;
    CGEventType eventTypeRightMouseUp;
    CGEventType eventTypeRightDragged;
    #else
    ofPoint mouseCursorPosition;
    #endif
    ofPoint myMouse;
    ofPoint prevMyMouse;

    int myMouseX;
    int myMouseY;

    bool    rect1L;
    bool    rect2L;
    bool    rect1R;
    bool    rect2R;

    float   rect_size;
    float   rect1_x, rect1_y;
    float   rect2_x, rect2_y;

    bool    myMouseMoved;

    ofColor on;
    ofColor off;

    string event;
};

