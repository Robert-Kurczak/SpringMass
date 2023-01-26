#pragma once

#include <vector>
#include "../Particle/Particle.hpp"
#include "../Spring/Spring.hpp"

//---Base---
class SpringSystem{
	protected:
		std::vector<Particle> particlesVector;
		std::vector<Spring> springsVector;
	
	public:
		SpringSystem(std::vector<Particle> particlesVector);

		void draw();
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
		struct Edge{
			Particle* pointA;
			Particle* pointB;

			Edge(Particle* _pointA, Particle* _pointB)
			: pointA(_pointA), pointB(_pointB)
			{}

			bool operator==(const Edge& edge){
				return(
					(
						edge.pointA -> position == pointA -> position && 
						edge.pointB -> position == pointB -> position
					)||
					(
						edge.pointA -> position == pointB -> position &&
						edge.pointB -> position == pointA -> position
					)
				);
			}
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

	public:
		TriangulationSystem(std::vector<Particle> particlesVector);
};
//------()