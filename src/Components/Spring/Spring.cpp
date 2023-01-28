#include "Spring.hpp"

Spring::Spring(
	float constant,
	float restLength,

	Particle& startPoint,
	Particle& endPoint
):
	constant(constant),
	restLength(restLength),
	startPoint(startPoint),
	endPoint(endPoint)
{}

void Spring::draw(){
	ofSetColor(color);
	ofDrawLine(startPoint.position, endPoint.position);
}

float Spring::getCurrentLength(){
	return startPoint.position.distance(endPoint.position);
}