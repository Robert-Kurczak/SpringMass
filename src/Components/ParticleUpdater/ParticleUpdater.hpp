#include "../Particle/Particle.hpp"

//---Base---
class ParticleUpdater{
	public:
		virtual void update(float deltaTime, Particle& particle) = 0;
};
//------

class ParticleGravity: public ParticleUpdater{
	private:
		float acceleration;

	public:
		ParticleGravity(float acceleration = 9.81);

		void update(float deltaTime, Particle& particle);
};

class ParticleFloorCollision: public ParticleUpdater{
	private:
		float floorPosition;

	public:
		ParticleFloorCollision(float floorPosition);

		void update(float deltaTime, Particle& particle);
};
