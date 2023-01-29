#include "Scene.hpp"

#include "../Components/Particle/Particle.hpp"
#include "../Components/ParticlesGenerator/ParticlesGenerator.hpp"

//---Base---
Scene::Scene(ofVec3f dimensions): dimensions(dimensions){}

void Scene::load(){}

void Scene::draw(){
	mainCamera.begin();

	springSystem -> updateAndDraw();

	mainCamera.end();
}

void Scene::handleClick(int x, int y, int button){}
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

	springSystem = std::make_shared<ClosestNeighbourSystem>(particlesVector);
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
		Particle({dimensions.x / 2, dimensions.y / 20}),
		Particle({dimensions.x / 2.3, dimensions.y / 8}),
		Particle({dimensions.x - dimensions.x / 2.3, dimensions.y / 8})
	};
	//------

	particlesVector[0].staticPosition = true;

	springSystem = std::make_shared<TriangulationSystem>(particlesVector);
}

void TriangulationScene::load(){
	mainCamera.setTarget(dimensions / 2);
	mainCamera.panDeg(270);
	mainCamera.rollDeg(225);

	mainCamera.removeAllInteractions();
}

void TriangulationScene::handleClick(int x, int y, int button){
	if(button == OF_MOUSE_BUTTON_LEFT){
		Particle newParticle({x, y});
		springSystem->addParticle(newParticle);
	}

}
//------