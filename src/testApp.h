#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "testApp.h"
#include "trackingManager.h"	
#include "calibrationManager.h"
#include "testingScene.h"
#include "typingScene.h"
#include "pongScene.h"
#include "eyePlotterTestApp.h"
#include "eyeOsc.h"
//#include "mouseControl.h"


enum{
	
	MODE_TRACKING,  MODE_CALIBRATING,   MODE_TEST,  MODE_DRAW,  
    MODE_TYPING,    MODE_PONG,          MODE_OSC,   MODE_MOUSE

};


class testApp : public ofBaseApp {

	public:

		testApp();
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void resized(int w, int h);
        
        bool bMouseSimulation;
        bool bMouseEyeInputSimulation;
    
        ofPoint eyeSmoothed;
	
        int mode; 

		//----- scenes

		trackingManager			TM;
		calibrationManager		CM;
        testingScene            testScene;
        eyePlotterTestApp       eyeApp;
        typingScene				typeScene;
        pongScene				ponger;
        eyeOsc                  oscScene;
        //mouseControl            mouseScene;
	
		//------ drawing
		void drawHelp();
        
        float buttonSensitivity;     
};

#endif
