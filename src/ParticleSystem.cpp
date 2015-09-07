#include "particleSystem.h"

ParticleSystem::ParticleSystem(){

}

void ParticleSystem::setup(ofVec3f _pos, int _nParticles){
    pos = _pos;
    nParticles = _nParticles;
    
    for (int i = 0; i < nParticles; i++) {
        Particle particle(pos);
        particle.setup();
        particle.age = ofRandom(particle.maxAge);
        particles.push_back(particle);
    }
}
void ParticleSystem::setupSnow(){
    int height = ofGetHeight();
    int width = ofGetWidth();
    for(unsigned int i = 0; i < particles.size(); i++){
        Particle* p = &particles.at(i);
        p->tail.clear();
        p->pos.x = ofRandom(-(width / 2), (width / 2));
        p->pos.y = ofRandom(-(height / 2), (height / 2));
    }
}


//--------------------------------------------------------------
void ParticleSystem::updateNoise(ofVec3f _force,
                            float noiseRandomOffset,
                            float spaceFrequency,
                            float timeFrequency,
                            float noiseMagnitude,
                            float oldVelAmount){
    //time stuff
    float time = ofGetElapsedTimef();
    float noiseReadTime = time * timeFrequency;
    float timeDelta = 1.0 / 60.0;

    for (unsigned int i = 0; i < particles.size(); i++) {
        Particle* p = &particles.at(i);
        if (p->age > p->maxAge) {
            p->setup();
        }
        p->updateNoise(noiseRandomOffset, spaceFrequency,
                  noiseReadTime, timeDelta, timeFrequency,
                  noiseMagnitude, oldVelAmount);
    }
}

void ParticleSystem::updateSnow(){
    float time = ofGetElapsedTimef();
    for (unsigned int i = 0; i < particles.size(); i++) {
        Particle* p = &particles.at(i);
        p->tailLength = 2;
        p->updateSnow(time);
    }
}

void ParticleSystem::updateTrigo(){
    float time = ofGetElapsedTimef();
    for (unsigned int i = 0; i < particles.size(); i++) {
        Particle* p = &particles.at(i);
        p->updateTrigo(time);
    }
}

void ParticleSystem::draw(){
    float time = ofGetElapsedTimef() * 0.1;
    ofMesh mesh;
    mesh.setMode( OF_PRIMITIVE_LINES );
    ofMesh* pointer_mesh = &mesh;

    for (int i=0; i<particles.size(); i++) {
        Particle* p = &particles.at(i);
        addParticleToMesh(p, pointer_mesh);
    }
    mesh.draw();
}

void ParticleSystem::addParticleToMesh(Particle *p, ofMesh *mesh){
    if( p->tail.size() > 1 ){
        for( int j = 1; j < p->tail.size(); j++ ){
            mesh->addVertex( p->tail.at(j-1) );
            // if you comment out this, the each vertex will be connected to the begining of the next one
            // and not to the end of the tail
            mesh->addVertex( p->tail.at(j) );
        }
    }
    
}

