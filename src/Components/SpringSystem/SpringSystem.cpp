#include "SpringSystem.hpp"
#include <cmath>

//---Base---
SpringSystem::SpringSystem(std::vector<Particle> particlesVector):
particlesVector(particlesVector)
{}

void SpringSystem::updateAndDraw(){
	float deltaTime = ofGetLastFrameTime();

	//Updating particles
	for(auto& particle: particlesVector){
		for(auto& particleUpdater: particleUpdatersVector){
			particleUpdater->update(deltaTime, particle);
		}
	}

	//Updating springs
	for(auto& spring: springsVector){
		for(auto& springUpdater: springUpdatersVector){
			springUpdater->update(deltaTime, spring);
		}
	}

	for(Spring spring: springsVector) spring.draw();
	for(auto& particle: particlesVector) particle.draw();
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

//------------------------Triangulaton System------------------------
void TriangulationSystem::setUpdaters(){
	particleUpdatersVector = {
		std::make_shared<ParticleGravity>(9.81),
		std::make_shared<ParticleFloorCollision>(500)
	};
}

//---nested Edge class---
TriangulationSystem::Edge::Edge(
	Particle* _pointA,
	Particle* _pointB
):
	pointA(_pointA),
	pointB(_pointB)
{}

//for filtering out edges object that describes same edge
bool TriangulationSystem::Edge::operator==(const Edge& edge){
	return(
		(
			edge.pointA -> position == pointA -> position && 
			edge.pointB -> position == pointB -> position
		)
		||
		(
			edge.pointA -> position == pointB -> position &&
			edge.pointB -> position == pointA -> position
		)
	);
}
//---

//---nested Triangle class---
TriangulationSystem::Triangle::Triangle(
	Particle* _pointA,
	Particle* _pointB,
	Particle* _pointC
):
	pointA(_pointA),
	pointB(_pointB),
	pointC(_pointC)
{
	//Costly calculations of circumcircle of given 3 points
	//theres probably a better way to do it

	float Ax = pointA -> position.x;
	float Ay = pointA -> position.y;

	float Bx = pointB -> position.x;
	float By = pointB -> position.y;

	float Cx = pointC -> position.x;
	float Cy = pointC -> position.y;

	float D = 2 * (Ax*(By-Cy) + Bx*(Cy-Ay) + Cx*(Ay-By));

	circumcenter.x = (
		(((Ax*Ax) + (Ay*Ay)) * (By - Cy)) + 
		(((Bx*Bx) + (By*By)) * (Cy - Ay)) +
		(((Cx*Cx) + (Cy*Cy)) * (Ay - By))
	) / D;

	circumcenter.y = (
		(((Ax*Ax) + (Ay*Ay)) * (Cx - Bx)) + 
		(((Bx*Bx) + (By*By)) * (Ax - Cx)) +
		(((Cx*Cx) + (Cy*Cy)) * (Bx - Ax))
	) / D;

	circumradiusSqr = circumcenter.squareDistance(pointA -> position);
}

//for filtering out copies of the same triangles in vectors
bool TriangulationSystem::Triangle::operator==(const Triangle& triangle){
	return(
		triangle.pointA -> position == pointA -> position &&
		triangle.pointB -> position == pointB -> position &&
		triangle.pointC -> position == pointC -> position
	);
}

bool TriangulationSystem::Triangle::inCircumcircle(ofVec2f point){
	return circumcenter.squareDistance(point) < circumradiusSqr;
}
//------

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

	Particle stParticleA(ofVec2f(minX - margin, minY - margin));
	Particle stParticleB(ofVec2f(maxX + margin, minY - margin));
	Particle stParticleC(ofVec2f(maxX / 2.f, maxY + margin));

	Triangle superTriangle(&stParticleA, &stParticleB, &stParticleC);
	//------

	std::vector<Triangle> triangles = {superTriangle};

	for(auto& particle: particlesVector){
		std::vector<Triangle> invalidTriangles;

		for(auto& triangle: triangles){
			if(triangle.inCircumcircle(particle.position))
				invalidTriangles.push_back(triangle);
		}

		//looking for edges not shared between invalidTriangles
		//---Edges of invalidTriangles---
		std::vector<Edge> edges;
		for(auto& triangle: invalidTriangles){
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
		for(auto& edge: uniqueEdges){
			Triangle newTriangle(
				edge.pointA,
				edge.pointB,
				&particle
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
	//------

	//---Creating springs from triangles---
	std::vector<Edge> validEdges;
	for(auto& triangle: triangles){
		validEdges.push_back(Edge(triangle.pointA, triangle.pointB));
		validEdges.push_back(Edge(triangle.pointB, triangle.pointC));
		validEdges.push_back(Edge(triangle.pointC, triangle.pointA));
	}

	//---Leaving only unique edges---
	std::vector<Edge> uniqueEdges;
	for(size_t i = 0; i < validEdges.size(); i++){
		bool isUnique = true;

		for(size_t j = i; j < validEdges.size(); j++){
			if(i != j && validEdges[i] == validEdges[j]){
				isUnique = false;
				break;
			}
		}

		if(isUnique) uniqueEdges.push_back(validEdges[i]);
	}
	//------

	for(auto& edge: uniqueEdges){
		springsVector.emplace_back(1, 1, *edge.pointA, *edge.pointB);
	}

	setUpdaters();
}
//------
//------------------------------------------------