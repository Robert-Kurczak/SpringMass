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
			ofVec2f pointA;
			ofVec2f pointB;

			Edge(ofVec2f pointA, ofVec2f pointB)
			: pointA(pointA), pointB(pointB)
			{}

			bool operator== (const Edge& edge){
				return	(edge.pointA == pointA && edge.pointB == pointB) ||
						(edge.pointA == pointB && edge.pointB == pointA);
			}
		};

		struct Triangle{
			ofVec2f pointA;
			ofVec2f pointB;
			ofVec2f pointC;

			float denominator;

			Triangle(ofVec2f pointA, ofVec2f pointB, ofVec2f pointC)
			: pointA(pointA), pointB(pointB), pointC(pointC)
			{
				denominator = (
					pointA.x * (pointB.y - pointC.y) + 
					pointA.y * (pointC.x - pointB.x) + 
					pointB.x * pointC.y - 
					pointB.y * pointC.x
				);
			}

			bool operator== (const Triangle& triangle){
				return triangle.pointA == pointA && triangle.pointB == pointB && triangle.pointC == pointC;
			}

			bool inCircumcircle(ofVec2f point){
				float t1 = (
					point.x * (pointC.y -  pointA.y) + 
					point.y * (pointA.x - pointC.x) - 
					pointA.x * pointC.y +
					pointA.y * pointC.x
				) / denominator;

				float t2 = (
					point.x * (pointB.y -  pointA.y) +
					point.y * (pointA.x - pointB.x) -
					pointA.x * pointB.y +
					pointA.y * pointB.x
				) / -denominator;
				
				float s = t1 + t2;
				
				return 0 <= t1 && t1 <= 1 && 0 <= t2 && t2 <= 1 && s <= 1;
			}
		};

	public:
		TriangulationSystem(std::vector<Particle> particlesVector);
};
//------()