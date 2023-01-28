#pragma once

#include "ofMain.h"
#include "../Particle/Particle.hpp"

//---Bases---
class ForceGenerator{
	public:
		virtual ofVec3f getForce(const Particle& particle) = 0;
};
//------

class GravityForce: public ForceGenerator{
	private:
		ofVec3f acceleration;

	public:
		GravityForce(ofVec3f acceleration = ofVec3f(0, 9.81, 0));

		ofVec3f getForce(const Particle& particle) override;
};

class FloorCollisionForce: public ForceGenerator{
	private:
		float floorLevel;

	public:
		FloorCollisionForce(float floorLevel);

		ofVec3f getForce(const Particle& particle) override;
};