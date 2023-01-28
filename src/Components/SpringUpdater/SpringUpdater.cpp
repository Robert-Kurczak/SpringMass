#include "SpringUpdater.hpp"

void SpringForce::update(float deltaTime, Spring& spring){
	//TODO refractor calculating force fector
	float deltaX = spring.getCurrentLength() - spring.restLength;
	float forceScalar = -spring.constant * deltaX;
	ofVec3f versor = (spring.endPoint.position - spring.endPoint.position).normalize();

	ofVec3f force = versor * forceScalar;

	//---Verlet---
	ofVec3f newStartPosition = (
		2 * spring.startPoint.position - spring.startPoint.lastPosition +
		deltaTime * deltaTime * -force / spring.startPoint.mass
	);

	spring.startPoint.lastPosition = spring.startPoint.position;
	spring.startPoint.position = newStartPosition;

	ofVec3f newEndPosition = (
		2 * spring.endPoint.position - spring.endPoint.lastPosition +
		deltaTime * deltaTime * force / spring.endPoint.mass
	);

	spring.endPoint.lastPosition = spring.endPoint.position;
	spring.endPoint.position = newEndPosition;
	//------
}