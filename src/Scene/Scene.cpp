#include "Scene.hpp"
#include "../Components/Particle/Particle.hpp"

//---Base---
Scene::Scene(ofVec3f dimensions): dimensions(dimensions){}

void Scene::load(){}
void Scene::draw(){
	mainCamera.begin();

	for(std::shared_ptr<SpringSystem> system: springSystems){
		system -> draw();
	}

	mainCamera.end();
}
//------

//---Closest Neighbour Scene---
ClosestNeighbourScene::ClosestNeighbourScene(ofVec3f dimensions): Scene(dimensions){
	std::vector<Particle> particlesVector;

	for(int i = 0; i < 10; i++){
		Particle newParticle;
		newParticle.position = ofVec3f(dimensions.x / 10 * i, dimensions.y / 2, 0);
		particlesVector.push_back(newParticle);
	}

	springSystems = {
		std::make_shared<ClosestNeighbourSystem>(particlesVector)
	};
}
//------