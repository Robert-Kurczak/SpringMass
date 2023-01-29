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

std::pair<ofVec3f, ofVec3f> Spring::getForce(){
	std::pair<ofVec3f, ofVec3f> result;

	ofVec3f displacement = startPoint.position - endPoint.position ;

	float deltaX = getCurrentLength() - restLength;
	ofVec3f versor = displacement.getNormalized();

	result.first = -constant * deltaX * versor;

	//for simplicity for now
	result.second = -result.first;

	return result;
}