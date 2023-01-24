#pragma once

#include <random>
#include <vector>
#include "../Particle/Particle.hpp"

//---Base class---
class ParticlesGenerator{
	protected:
		ParticlesGenerator();

		std::mt19937 mt;

		float randomFloat(float start, float end);

		virtual void generate(std::vector<Particle>& particlesVector, int amount) = 0;
};
//------

class BoxPositionGenerator: public ParticlesGenerator{
	private:
		ofVec3f positionStart;
		ofVec3f positionEnd;

	public:
		BoxPositionGenerator(ofVec3f positionStart, ofVec3f positionEnd);

		void generate(std::vector<Particle>& particlesVector, int amount);
};