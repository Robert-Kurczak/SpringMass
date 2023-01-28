#include "ForceGenerator.hpp"

//---Gravity Force---
GravityForce::GravityForce(ofVec3f acceleration)
: acceleration(acceleration)
{}

ofVec3f GravityForce::getForce(const Particle& particle){
	return particle.mass * acceleration;
}
//------

//---Floor Collision Force---
FloorCollisionForce::FloorCollisionForce(float floorLevel)
: floorLevel(floorLevel)
{}

ofVec3f FloorCollisionForce::getForce(const Particle& particle){
	ofVec3f result(0, 0, 0);

	if(particle.position.y >= floorLevel){
		result.y = -particle.force.y;
	}

	return result;
}
//------
