#pragma once

#include <vector>
#include "../Particle/Particle.hpp"
#include "../Spring/Spring.hpp"

class SpringSystem{
	protected:
		std::vector<Particle> particlesVector;
		std::vector<Spring> springsVector;
	
	public:
		SpringSystem(std::vector<Particle> particlesVector);

		void draw();
};

class ClosestNeighbourSystem: public SpringSystem{
	private:
		//

	public:
		ClosestNeighbourSystem(std::vector<Particle> particlesVector);
};