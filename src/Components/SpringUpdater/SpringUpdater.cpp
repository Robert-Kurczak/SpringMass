#include "SpringUpdater.hpp"

//---Ground Collision---
GroundCollision::GroundCollision(float groundLevel)
: groundLevel(groundLevel)
{}

void GroundCollision::update(float deltaTime, Spring& spring){
	if(spring.startPoint.position.y >= groundLevel){
		spring.startPoint.position.y = groundLevel;
		spring.startPoint.lastPosition = spring.startPoint.position;
	}
	
	if(spring.endPoint.position.y >= groundLevel){
		spring.endPoint.position.y = groundLevel;
		spring.endPoint.lastPosition = spring.endPoint.position;
	}
	
}
//------