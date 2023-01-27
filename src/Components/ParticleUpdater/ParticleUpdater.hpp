#include "../Particle/Particle.hpp"

//---Base---
class ParticleUpdater{
	public:
		virtual void update(float deltaTime, Particle& particle) = 0;
};
//------

class ParticleGravityUpdater: public ParticleUpdater{
	private:
		float acceleration;

	public:
		ParticleGravityUpdater(float acceleration = 9.81);

		void update(float deltaTime, Particle& particle);
};