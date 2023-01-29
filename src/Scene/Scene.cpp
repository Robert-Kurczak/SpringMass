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
	std::vector<Particle> particlesVector;
	BoxPositionGenerator boxGenerator(
		ofVec3f(0, 0, 0),
		ofVec3f(dimensions.x, dimensions.y, 0)
	);

	// boxGenerator.generate(particlesVector, 50);
	
	particlesVector = {
		Particle({0, 0}),
		Particle({100, -200}),
		Particle({200, 0})
	};
	//------

	springSystems = {
		std::make_shared<TriangulationSystem>(particlesVector)
	};
}

void TriangulationScene::load(){
	mainCamera.setTarget(dimensions / 2);
	mainCamera.panDeg(90);
	mainCamera.rollDeg(135);
}
//------