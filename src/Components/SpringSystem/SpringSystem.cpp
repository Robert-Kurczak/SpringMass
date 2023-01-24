#include "SpringSystem.hpp"
#include <cmath>

//---Base---
SpringSystem::SpringSystem(std::vector<Particle> particlesVector):
particlesVector(particlesVector)
{}

void SpringSystem::draw(){
	for(Spring spring: springsVector) spring.draw();
	for(Particle particle: particlesVector) particle.draw();
}
//------

ClosestNeighbourSystem::ClosestNeighbourSystem(std::vector<Particle> _particlesVector): SpringSystem(_particlesVector){
	for(size_t i = 0; i < particlesVector.size() - 1; i++){
		Particle& particle = particlesVector[i];

		Particle* closestParticle = nullptr;
		float closestDistanceSqr = FLT_MAX;

		for(size_t j = i + 1; j < particlesVector.size(); j++){

			Particle& possibleClosest = particlesVector[j];
			float distanceSqr = particle.position.squareDistance(possibleClosest.position);

			if(closestDistanceSqr > distanceSqr){
				closestParticle = &possibleClosest;
				closestDistanceSqr = distanceSqr;
			}
		}

		springsVector.emplace_back(1, std::sqrt(closestDistanceSqr), particle, *closestParticle);
	}
};