#pragma once

#include "../Particle/Particle.hpp"
#include "ofMain.h"

class Spring{
	private:
		float constant;
		float restLength;
		float currentLength;

		Particle& startPoint;
		Particle& endPoint;

		ofColor color;

	public:
		Spring(
			float constant,
			float restLength,
			Particle& startPoint,
			Particle& endPoint
		);

		void draw();
};