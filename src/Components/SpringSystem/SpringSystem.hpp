#pragma once

#include <vector>

#include "../Particle/Particle.hpp"
#include "../Spring/Spring.hpp"
#include "../ForceGenerator/ForceGenerator.hpp"
#include "../SpringUpdater/SpringUpdater.hpp"

//---Base---
class SpringSystem{
	protected:
		std::vector<Particle> particlesVector;
		std::vector<Spring> springsVector;

		std::vector<std::shared_ptr<ForceGenerator>> forceGeneratorsVector;
		std::vector<std::shared_ptr<SpringUpdater>> updatersVector;

	public:
		SpringSystem(std::vector<Particle> particlesVector);

		virtual void addParticle(Particle particle);
		virtual void disableStatic();
		virtual void removeClosestParticle(ofVec3f position);

		void updateAndDraw();
};
//------

//---Closest Neighbour System---
class ClosestNeighbourSystem: public SpringSystem{
	public:
		ClosestNeighbourSystem(std::vector<Particle> particlesVector);
};
//------

//---Triangulation System---
class TriangulationSystem: public SpringSystem{
private:
	//Those classes holds pointers to particles as their vertices.
	//It needs to be particles, because at the end of the algorithm
	//we need to create springs between particles, not points.
	
	class Edge{
	public:
		Particle* pointA;
		Particle* pointB;

		Edge(Particle* _pointA, Particle* _pointB);

		bool operator==(const Edge& edge);
	};

	class Triangle{
	private:
		ofVec2f circumcenter;
		float circumradiusSqr;

	public:
		Particle* pointA;
		Particle* pointB;
		Particle* pointC;

		Triangle(Particle* _pointA, Particle* _pointB, Particle* _pointC);

		bool operator==(const Triangle& triangle);

		bool inCircumcircle(ofVec2f point);
	};

	void triangulate();

	void setForceGenerators();
	void setUpdaters();

public:
	TriangulationSystem(std::vector<Particle> particlesVector);

	void addParticle(Particle particle) override;
	void removeClosestParticle(ofVec3f position) override;
};
//------