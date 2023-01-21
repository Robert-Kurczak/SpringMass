#include "Particle.hpp"

Particle::Particle(){}

void Particle::draw(){
	ofSetColor(color);
	ofDrawSphere(position, radius);
}