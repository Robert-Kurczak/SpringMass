#pragma once

#include "../Particle/Particle.hpp"
#include "ofMain.h"
#include "utility"

class Spring{
	public:
		float constant;
		float restLength;

		Particle& startPoint;
		Particle& endPoint;

		ofColor color;
		
		Spring(
			float constant,
			float restLength,
			Particle& startPoint,
			Particle& endPoint
		);

		void draw();

		float getCurrentLength();

		std::pair<ofVec3f, ofVec3f> getForce();
};