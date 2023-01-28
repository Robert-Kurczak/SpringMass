#pragma once

#include "../Particle/Particle.hpp"
#include "ofMain.h"

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
};