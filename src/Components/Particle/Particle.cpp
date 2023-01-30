#include "Particle.hpp"

Particle::Particle(ofVec3f position)
: lastPosition(position), position(position)
{}

void Particle::draw(){
	ofSetColor(color);
	ofDrawSphere(position, radius);
}