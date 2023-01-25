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

		struct Triangle{
			Particle* pointA;
			Particle* pointB;
			Particle* pointC;

			ofVec2f circumcenter;

			Triangle(Particle* _pointA, Particle* _pointB, Particle* _pointC)
			: pointA(_pointA), pointB(_pointB), pointC(_pointC)
			{}

			bool operator==(const Triangle& triangle){
				return(
					triangle.pointA -> position == pointA -> position &&
					triangle.pointB -> position == pointB -> position &&
					triangle.pointC -> position == pointC -> position
				);
			}

			bool inCircumcircle(ofVec2f point){
				float Ax = pointA -> position.x;
				float Ay = pointA -> position.y;

				float Bx = pointB -> position.x;
				float By = pointB -> position.y;

				float Cx = pointC -> position.x;
				float Cy = pointC -> position.y;

				float D = 2 * (Ax*(By-Cy) + Bx*(Cy-Ay) + Cx*(Ay-By));

				float Ux = (
					(((Ax*Ax) + (Ay*Ay)) * (By - Cy)) + 
					(((Bx*Bx) + (By*By)) * (Cy - Ay)) +
					(((Cx*Cx) + (Cy*Cy)) * (Ay - By))
				) / D;

				float Uy = (
					(((Ax*Ax) + (Ay*Ay)) * (Cx - Bx)) + 
					(((Bx*Bx) + (By*By)) * (Ax - Cx)) +
					(((Cx*Cx) + (Cy*Cy)) * (Bx - Ax))
				) / D;

				ofVec2f circumcenter(Ux, Uy);

				float radius = circumcenter.distance(pointA->position);

				return circumcenter.distance(point) < radius;
			}
		};

	public:
		TriangulationSystem(std::vector<Particle> particlesVector);
};
//------()