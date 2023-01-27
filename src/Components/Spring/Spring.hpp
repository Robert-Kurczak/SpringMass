#pragma once

#include "../Particle/Particle.hpp"
#include "ofMain.h"

class Spring{
	private:
		float constant;
		float restLength;
		float currentLength;

		ofColor color;

	public:
		Particle& startPoint;
		Particle& endPoint;
		
		Spring(
			float constant,
			float restLength,
			Particle& startPoint,
			Particle& endPoint
		);

		void draw();
};