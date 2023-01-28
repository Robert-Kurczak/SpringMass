#include "ParticleUpdater.hpp"

//---Gravity Updater---
ParticleGravity::ParticleGravity(float acceleration)
: acceleration(acceleration)
{}

void ParticleGravity::update(float deltaTime, Particle& particle){
	//Initial position, Euler interpolation
	if(particle.position == particle.lastPosition){
		particle.velocity.y += acceleration * deltaTime;
		particle.position.y += particle.velocity.y * deltaTime;
	}
	//Verlet interpolation
	else{
		ofVec3f newPosition = (
			2 * particle.position - particle.lastPosition +
			deltaTime * deltaTime * ofVec3f(0, acceleration, 0)
		);

		particle.lastPosition = particle.position;
		particle.position = newPosition;
	}
}
//---

//---Floor Collision Updater---
ParticleFloorCollision::ParticleFloorCollision(float floorPosition)
: floorPosition(floorPosition)
{}

void ParticleFloorCollision::update(float deltaTime, Particle& particle){
	if(particle.position.y >= floorPosition){
		particle.position.y = floorPosition;
		particle.lastPosition = particle.position;
	}
}
//------