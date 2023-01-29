#include "Scene.hpp"

#include "../Components/Particle/Particle.hpp"
#include "../Components/ParticlesGenerator/ParticlesGenerator.hpp"

//---Base---
Scene::Scene(ofVec3f dimensions): dimensions(dimensions){}

void Scene::load(){}

void Scene::draw(){
	mainCamera.begin();

	for(std::shared_ptr<SpringSystem> system: springSystems){
		system -> updateAndDraw();
	}

	mainCamera.end();
}
//------

//---Closest Neighbour Scene---
ClosestNeighbourScene::ClosestNeighbourScene(ofVec3f dimensions)
: Scene(dimensions)
{
	//---Generating initial points---
	std::vector<Particle> particlesVector;

	BoxPositionGenerator boxGenerator(
		ofVec3f(0, 0, 0),
		dimensions
	);

	boxGenerator.generate(particlesVector, 5000);
	//------

	springSystems = {
		std::make_shared<ClosestNeighbourSystem>(particlesVector)
	};
}

void ClosestNeighbourScene::load(){
	mainCamera.setTarget(dimensions / 2);
}
//------

//---Triangulation Scene---
TriangulationScene::TriangulationScene(ofVec3f dimensions)
: Scene(dimensions)
{
	std::vector<Particle> particlesVector = {
		//TODO check why triangulation not working
		// Particle({3 * dimensions.x / 8, dimensions.y / 4}),
		// Particle({dimensions.x / 2, dimensions.y / 5}),
		// Particle({6 * dimensions.x / 8, dimensions.y / 4})

		Particle({dimensions.x / 2, dimensions.y / 20}),
		Particle({dimensions.x / 2.3, dimensions.y / 8}),
		Particle({dimensions.x - dimensions.x / 2.3, dimensions.y / 8})
	};
	//------

	particlesVector[0].staticPosition = true;

	springSystems = {
		std::make_shared<TriangulationSystem>(particlesVector)
	};
}

void TriangulationScene::load(){
	mainCamera.setTarget(dimensions / 2);
	mainCamera.panDeg(270);
	mainCamera.rollDeg(225);
}
//------