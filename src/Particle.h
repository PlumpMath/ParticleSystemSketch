#pragma once

#include "ofMain.h"

class Particle{
public:
    Particle(ofVec3f _startingPos);
    
    void setup();
    void updateNoise(float noiseRandomOffset, float spaceFrequency,
                float noiseReadTime, float timeDelta, float timeFrequency,
                float noiseMagnitude, float oldVelAmount);
    void updateSnow(float time);
    ofVec3f getNoise( ofVec3f _noisePos, float _time );

    
    float drag, uniqueVal, scale, maxAge, age;
    int dimension, tailLength;
    bool is_alive;
    
    deque<ofVec3f> tail;
    ofColor color;
    ofVec3f startingPos, pos, vel, acc, force;

private:
    void applyForce(ofVec3f _force);
    void repositionAtTheTop();
    void updatePositionHistory();
    void resetForces();

};

