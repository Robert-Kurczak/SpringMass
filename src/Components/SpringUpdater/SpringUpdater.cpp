#include "SpringUpdater.hpp"

//---Ground Collision---
GroundCollision::GroundCollision(float groundLevel)
: groundLevel(groundLevel)
{}

void GroundCollision::update(float deltaTime, Spring& spring){
	if(spring.startPoint.newPosition.y > groundLevel){
		// spring.startPoint.lastPosition.y = groundLevel;
		// spring.startPoint.position.y = groundLevel;
		spring.startPoint.newPosition.y = groundLevel;
	}
	
	if(spring.endPoint.newPosition.y > groundLevel){
		// spring.endPoint.lastPosition.y = groundLevel;
		// spring.endPoint.position.y = groundLevel;
		spring.endPoint.newPosition.y = groundLevel;
	}
	
}
//------