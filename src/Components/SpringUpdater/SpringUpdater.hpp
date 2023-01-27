#include "../Spring/Spring.hpp"

//---Base---
class SpringUpdater{
	public:
		virtual void update(float deltaTime, Spring& spring) = 0;
};
//------