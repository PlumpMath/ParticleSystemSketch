#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "modes.h"

class ParticleSystem{
public:
    ParticleSystem();
    
    void setup(ofVec3f _pos, int n_particle);
    void setupSnow();
    void updateNoise(ofVec3f _force,float noiseRandomOffset, float spaceFrequency,float timeFrequency,float noiseMagnitude,float oldVelAmount);
    void updateSnow();
    void updateTrigo();
    void draw();
    
    int nParticles;
    particleMode mode;
    vector<Particle> particles ;
    ofVec3f pos;
    
private:
    void addParticleToMesh(Particle *p, ofMesh *mesh);
    
};
