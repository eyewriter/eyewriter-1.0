
#include "testApp.h"
#include "stdio.h"


//--------------------------------------------------------------
testApp::testApp(){

}                                                  

//--------------------------------------------------------------
void testApp::setup(){

	
	//---- setup standard application settings
	
	ofSetVerticalSync(true);  
	
	mode = MODE_TRACKING;
	TM.setup();
	CM.setup();
    eyeApp.setup();
	typeScene.setup();
    ponger.setup();
	
	eyeSmoothed.set(0,0,0);
	
	
	BTrig.setup("catch me!", 50,50,180,180);
    BTrig.setMaxCounter(1.0); //button sensitivity
    //BT.setMaxCounter(TM.getButtonPressTime());
    
    BTog.setup("on","off",false,250,250,180,180);
    
    bMouseSimulation = false;
}



//--------------------------------------------------------------
void testApp::update(){

	ofBackground(70,70,70);
	
	// update the tracking manager (and internally, its input manager)
	TM.update();
	
	// update the calibration manager
	CM.update();
    
    
    if (CM.bAutomatic == true && CM.bAmInAutodrive == true && CM.bInAutoRecording){
		
		if (TM.bGotAnEyeThisFrame()){	
			ofPoint trackedEye = TM.getEyePoint();
			CM.fitter.registerCalibrationInput(trackedEye.x,trackedEye.y);
			CM.inputEnergy = 1;
		}
	}
    
    
    // smooth eye data in...
    if (!bMouseSimulation){
        if (CM.fitter.bBeenFit){
            ofPoint trackedEye;
			
			if (bMouseEyeInputSimulation) {
				trackedEye.x = mouseX;
				trackedEye.y = mouseY;
			} else {
				trackedEye = TM.getEyePoint();
			}
            
            //cout << CM.smoothing << endl;
            CM.smoothing = 0.7;
			ofPoint screenPoint = CM.fitter.getCalibratedPoint(trackedEye.x, trackedEye.y);
			eyeSmoothed.x = CM.smoothing * eyeSmoothed.x + (1-CM.smoothing) * screenPoint.x;
			eyeSmoothed.y = CM.smoothing * eyeSmoothed.y + (1-CM.smoothing) * screenPoint.y;
        }
    }
    else{
        eyeSmoothed.x = mouseX;
		eyeSmoothed.y = mouseY;
    }
    
    
	if( mode == MODE_DRAW ){
		ofPoint pt = eyeSmoothed;
        if(bMouseSimulation) eyeApp.update( mouseX, mouseY );
        else eyeApp.update( pt.x, pt.y);
	}
	
	if (mode == MODE_TYPING){
		ofPoint pt = eyeSmoothed;
		typeScene.update(pt.x, pt.y);
	}
	
	if (mode == MODE_PONG){
		ofPoint pt = eyeSmoothed;
		ponger.update(pt.x, pt.y);
	}

	
	if (mode == MODE_TEST){
		ofPoint pt = eyeSmoothed;
		if (BTrig.update(pt.x, pt.y)){
			BTrig.x = ofRandom(100,ofGetWidth()-100);
			BTrig.y = ofRandom(100,ofGetHeight()-100);
		}
        else if (BTog.update(pt.x, pt.y)){
            BTog.x = ofRandom(100,ofGetWidth()-100);
			BTog.y = ofRandom(100,ofGetHeight()-100);
        }
	}
}


//--------------------------------------------------------------
void testApp::draw(){

	
	ofSetColor(255, 255, 255);

	
	if (mode == MODE_TRACKING)			TM.draw();
	if (mode == MODE_CALIBRATING)		CM.draw();
	if (mode == MODE_TEST){				BTrig.draw(); BTog.draw();}
    if (mode == MODE_DRAW )				eyeApp.draw();
	if (mode == MODE_TYPING)			typeScene.draw();
	if (mode == MODE_PONG)				ponger.draw();
	
		
	// draw a green dot to see how good the tracking is:
	if (CM.fitter.bBeenFit || bMouseSimulation){
		if( mode != MODE_DRAW ){	
			ofSetColor(0,255,0,120);
			ofFill();
			ofCircle(eyeSmoothed.x, eyeSmoothed.y, 20);
		}
	}	
}



//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	
	switch (key){
			
		case	OF_KEY_RETURN:
			mode ++;
			mode %= 6; // number of modes;
			break;
	
		case	'f':
		case	'F':
			ofToggleFullscreen();
			break;
            
        case	'm':
		case	'M':
			bMouseSimulation = !bMouseSimulation;
			break;
	}
	
	if (mode == MODE_CALIBRATING){
		CM.keyPressed(key);
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
	if (mode == MODE_TRACKING)			TM.mouseDragged(x, y, button);
	if (mode == MODE_CALIBRATING)		CM.mouseDragged(x, y, button);

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

	
	if (mode == MODE_TRACKING)			TM.mousePressed(x, y, button);
	if (mode == MODE_CALIBRATING)		CM.mousePressed(x, y, button);


}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
	if (mode == MODE_TRACKING)			TM.mouseReleased();
	if (mode == MODE_CALIBRATING)		CM.mouseReleased(x,y,button);

}


//--------------------------------------------------------------
void testApp::resized(int w, int h){

}


