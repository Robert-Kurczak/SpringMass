#include "Spring.hpp"

Spring::Spring(
	float constant,
	float restLength,
	Particle& startPoint,
	Particle& endPoint
):
	constant(constant),
	restLength(restLength),
	currentLength(restLength),
	startPoint(startPoint),
	endPoint(endPoint)
{}

void Spring::draw(){
	ofSetColor(color);
	ofDrawLine(startPoint.position, endPoint.position);
}