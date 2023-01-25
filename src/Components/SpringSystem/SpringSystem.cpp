#include "SpringSystem.hpp"
#include <cmath>

//---Base---
SpringSystem::SpringSystem(std::vector<Particle> particlesVector):
particlesVector(particlesVector)
{}

void SpringSystem::draw(){
	for(Spring spring: springsVector) spring.draw();
	for(Particle particle: particlesVector) particle.draw();
}
//------

//---Closest Neighbour System---
ClosestNeighbourSystem::ClosestNeighbourSystem(std::vector<Particle> _particlesVector)
: SpringSystem(_particlesVector)
{
	for(size_t i = 0; i < particlesVector.size() - 1; i++){
		Particle& particle = particlesVector[i];

		Particle* closestParticle = nullptr;
		float closestDistanceSqr = FLT_MAX;

		for(size_t j = i + 1; j < particlesVector.size(); j++){

			Particle& possibleClosest = particlesVector[j];
			float distanceSqr = particle.position.squareDistance(possibleClosest.position);

			if(closestDistanceSqr > distanceSqr){
				closestParticle = &possibleClosest;
				closestDistanceSqr = distanceSqr;
			}
		}

		springsVector.emplace_back(1, std::sqrt(closestDistanceSqr), particle, *closestParticle);
	}
};
//------

//---Triangulation System---
TriangulationSystem::TriangulationSystem(std::vector<Particle> _particlesVector)
: SpringSystem(_particlesVector)
{
	//---Creating super triangle---
	float minX = FLT_MAX;
	float maxX = FLT_MIN;

	float minY = FLT_MAX;
	float maxY = FLT_MIN;

	for(Particle particle: particlesVector){
		if(particle.position.x < minX) minX = particle.position.x;
		else if(particle.position.x > maxX) maxX = particle.position.x;

		if(particle.position.y < minY) minY = particle.position.y;
		else if(particle.position.y > maxY) maxY = particle.position.y;
	}

	float margin = std::max(maxX - minX, maxY - minY);

	Triangle superTriangle(
		ofVec2f(minX - margin, minY - margin),
		ofVec2f(maxX + margin, minY - margin),
		ofVec2f(maxX / 2.f, maxY + margin)
	);
	//------

	std::vector<Triangle> triangles = {superTriangle};

	for(auto particle: particlesVector){
		std::vector<Triangle> invalidTriangles;

		for(auto triangle: triangles){
			if(triangle.inCircumcircle(particle.position))
				invalidTriangles.push_back(triangle);
		}

		//looking for edges not shared between invalidTriangles
		//---Edges of invalidTriangles---
		std::vector<Edge> edges;
		for(auto triangle: invalidTriangles){
			edges.push_back(Edge(triangle.pointA, triangle.pointB));
			edges.push_back(Edge(triangle.pointB, triangle.pointC));
			edges.push_back(Edge(triangle.pointC, triangle.pointA));
		}
		//------

		//---Leaving only unique edges---
		std::vector<Edge> uniqueEdges;
		for(size_t i = 0; i < edges.size(); i++){
			bool isUnique = true;

			for(size_t j = 0; j < edges.size(); j++){
				if(i != j && edges[i] == edges[j]){
					isUnique = false;
					break;
				}
			}

			if(isUnique) uniqueEdges.push_back(edges[i]);
		}
		//------

		//---Remove invalidTriangles from triangles---
		for(auto& invalidTriangle : invalidTriangles) {
			triangles.erase(
				std::remove(triangles.begin(), triangles.end(), invalidTriangle),
				triangles.end()
			);
		}
		//------

		//---Creating new, proper triangles---
		for(auto edge: uniqueEdges){
			Triangle newTriangle(
				edge.pointA,
				edge.pointB,
				particle.position
			);

			triangles.push_back(newTriangle);
		}
		//------
	}

	//---Delete superTriangle vertices---
	triangles.erase(
		std::remove_if(
			triangles.begin(),
			triangles.end(),
			[superTriangle](Triangle triangle){
				return(
					triangle.pointA == superTriangle.pointA ||
					triangle.pointA == superTriangle.pointB ||
					triangle.pointA == superTriangle.pointC ||

					triangle.pointB == superTriangle.pointA ||
					triangle.pointB == superTriangle.pointB ||
					triangle.pointB == superTriangle.pointC ||

					triangle.pointC == superTriangle.pointA ||
					triangle.pointC == superTriangle.pointB ||
					triangle.pointC == superTriangle.pointC
				);
			}
		),
		triangles.end()
	);

	float a = 0;
	//------
}
//------