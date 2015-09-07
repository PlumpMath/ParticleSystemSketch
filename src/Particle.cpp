#include "Particle.h"

Particle::Particle(ofVec3f _startingPos) {
    maxTailLength = 8;
    maxAge = 55;
    age = ofRandom(maxAge);
    tailLength = maxTailLength;
    is_alive = true;
}

void Particle::setup(){
    //the unique val allows us to set properties slightly differently for each particle
    tailLength = maxTailLength;
    uniqueVal = ofRandom(-10000, 10000);
    
    pos.x = ofRandom(-400, 400);
    pos.y = ofRandom(-400, 400);
    pos.z = ofRandom(0, 800);
    
    vel.x = ofRandom(-3.9, 3.9);
    vel.y = ofRandom(-3.9, 3.9);
    vel.z = ofRandom(-3.9, 3.9);
    
    force   = ofVec3f(0,0,0);
    scale = ofRandom(0.5, 1.0);
    drag  = ofRandom(0.97, 0.99);
    age = 0;
    tail.clear();
    angle = ofMap(uniqueVal, -10000.0, 10000.0, 0.0, 360.0);

}

void Particle::updateNoise(float noiseRandomOffset, float spaceFrequency,
                      float noiseReadTime, float timeDelta, float timeFrequency,
                      float noiseMagnitude,float oldVelAmount){
    ofVec3f noiseReadPos = (pos + noiseRandomOffset ) * spaceFrequency;
    vel = (getNoise( noiseReadPos, noiseReadTime ) * noiseMagnitude).getInterpolated( vel, oldVelAmount );
    
    pos += vel;
    vel *= drag;
    
    age += timeDelta;
    updatePositionHistory();
    
}

void Particle::updateSnow(float time){
    vel.z = 0;
    //vel x give a little bit of windy effect
    vel.x = ofSignedNoise(uniqueVal) * 2;
    age += time;
    resetForces();
    force = ofVec3f(0.0, -0.1, 0.0);
    applyForce(force);
    updatePositionHistory();
    repositionAtTheTop();
}

void Particle::updateTrigo(float time){
    age += time;
    resetForces();

    angularAccelleration = ofSignedNoise(uniqueVal);
    angle += angularVelocity;
    angularVelocity += angularAccelleration;
    pos.x += cos(angle);
    pos.y += sin(angle);
    pos.z += sin(angle);
    updatePositionHistory();
}

void Particle::resetForces() {
    angularAccelleration *= 0;
    acc *= 0;
}

void Particle::applyForce(ofVec3f _force) {
    acc += _force;
    vel += acc;
    pos += vel;
}

void Particle::repositionAtTheTop(){
    if( pos.y < -(ofGetHeight() / 2) ){
        pos.y = ofGetHeight() / 2;
        age = ofRandom(maxAge);
        tail.clear();
        vel.y = ofRandom(-3.9, 3.9);
    }
}

void Particle::updatePositionHistory() {
    //cout << tail.size()<< endl;
    tail.push_front(pos);
    //cout << tail.size()<< endl;
    while( tail.size() > tailLength ) { tail.pop_back(); }
}


ofVec3f Particle::getNoise( ofVec3f _noisePos, float _time ){
    ofVec3f p(0,0,0);
    p.x += ofSignedNoise( _noisePos.x, _noisePos.y, _noisePos.z, _time );
    p.y += ofSignedNoise( _noisePos.y, _noisePos.z, _noisePos.x, _time );
    p.z += ofSignedNoise( _noisePos.z, _noisePos.x, _noisePos.y, _time );
    
    return p;
}




