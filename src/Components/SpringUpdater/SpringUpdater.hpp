#include "../Spring/Spring.hpp"

class SpringUpdater{
	public:
		virtual void update(float deltaTime, Spring& spring) = 0;
};

class GroundCollision: public SpringUpdater{
	private:
		float groundLevel;

	public:
		GroundCollision(float groundLevel);

		void update(float deltaTime, Spring& spring) override;
};