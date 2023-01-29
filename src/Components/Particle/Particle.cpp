#include "Particle.hpp"

Particle::Particle(ofVec3f position)
: lastPosition(position), position(position), newPosition(position)
{}

void Particle::draw(){
	ofSetColor(color);
	ofDrawSphere(position, radius);
}