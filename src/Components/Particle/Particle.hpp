#pragma once

#include "ofMain.h"

class Particle{
	public:
		float radius = 5;
		float mass = 1;
		ofColor color;
		
		ofVec3f lastPosition;
		ofVec3f position;
		ofVec3f velocity;

		Particle();

		void draw();
};