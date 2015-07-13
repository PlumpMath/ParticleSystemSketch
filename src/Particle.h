#pragma once

#include "ofMain.h"

class Particle{
public:
    Particle(ofVec3f _starting_pos);
    
    void setup();
    void update(float noiseRandomOffset, float spaceFrequency,
                float noiseReadTime, float timeDelta, float timeFrequency,
                float noiseMagnitude, float oldVelAmount);
    void updateSnow(float time);
    void updatePositionHistory();

    void resetForces();
    
    float drag;
    float uniqueVal;
    float scale;
    
    int dimension;
    float max_age;
    float age;
    bool is_alive;
    
    ofColor color;
    deque<ofVec3f> tail;
    int tail_length;
    ofVec3f starting_pos, pos, vel, acc, force;
    ofVec3f getNoise( ofVec3f _noisePos, float _time );
    
private:
    void applyForce(ofVec3f _force);
    void repositionAtTheTop();

};

