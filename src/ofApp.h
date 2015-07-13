#pragma once

#include "ofMain.h"
#include "ParticleSystem.h"
#include "ofxUI.h"
#include "modes.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void resetForcesParticleSystems();

    void screenshot();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    ofColor bg_color;
    ofShader shader;
    
    //Camera
    ofEasyCam camera;
    float zoom;
    
    //----GUI variables-------
    ofxUISuperCanvas *gui;
    void guiEvent(ofxUIEventArgs &e);
    bool draw_padding;
    ofVec3f emitter;
    //bool isResetPos;
    
    //da sostituire con i modes
    char selected_force;
    particleMode currentMode;
    string currentModeStr;
    ParticleSystem system;
    ofVec3f force;
    
    //noise
    float		randomOffset;
    float		noiseMagnitude;
    float		spaceFrequency;
    float		timeFrequency;
    float		oldVelAmount;
    float       maxVel;
		
};
