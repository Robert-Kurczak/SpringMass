#include "SpringUpdater.hpp"

//---Ground Collision---
GroundCollision::GroundCollision(float groundLevel)
: groundLevel(groundLevel)
{}

void GroundCollision::update(float deltaTime, Spring& spring){
	if(spring.startPoint.position.y > groundLevel){
		spring.startPoint.position.y = groundLevel;
	}
	
	if(spring.endPoint.position.y > groundLevel){
		spring.endPoint.position.y = groundLevel;
	}
	
}
//------