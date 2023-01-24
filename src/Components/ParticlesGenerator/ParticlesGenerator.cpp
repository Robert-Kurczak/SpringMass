#include "ParticlesGenerator.hpp"

//---Base class---
ParticlesGenerator::ParticlesGenerator():
mt(std::mt19937(std::random_device{}()))
{}

float ParticlesGenerator::randomFloat(float start, float end){
	std::uniform_real_distribution<float> dist(start, end);
	return dist(mt);
}
//------

//---------------------------Position generators---------------------------
//---Box Position Generator---
BoxPositionGenerator::BoxPositionGenerator(ofVec3f positionStart, ofVec3f positionEnd):
positionStart(positionStart), positionEnd(positionEnd)
{}

void BoxPositionGenerator::generate(std::vector<Particle>& particlesVector, int amount){
	for(int i = 0; i < amount; i++){
		Particle newParticle;

		newParticle.position = ofVec3f(
			randomFloat(positionStart.x, positionEnd.x),
			randomFloat(positionStart.y, positionEnd.y),
			randomFloat(positionStart.z, positionEnd.z)
		);

		particlesVector.push_back(newParticle);
	}
}
//------
//------------------------------------------------------