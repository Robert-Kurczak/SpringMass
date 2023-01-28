#pragma once

#include "ofMain.h"

class Particle{
	public:
		bool updated = false;

		float radius = 5;
		float mass = 1;
		ofColor color;
		
		ofVec3f lastPosition;
		ofVec3f position;
		ofVec3f force;

		Particle(ofVec3f position);

		void draw();
};