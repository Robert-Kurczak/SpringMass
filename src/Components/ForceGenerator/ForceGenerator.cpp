#include "ForceGenerator.hpp"

//---Gravity Force---
GravityForce::GravityForce(ofVec3f acceleration)
: acceleration(acceleration)
{}

ofVec3f GravityForce::getForce(const Particle& particle){
	return particle.mass * acceleration;
}
//------