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
		Particle({dimensions.x / 2.f, dimensions.y / 20.f}),
		Particle({dimensions.x / 2.3f, dimensions.y / 8.f}),
		Particle({dimensions.x - dimensions.x / 2.3f, dimensions.y / 8.f})
	};
	//------

	particlesVector[0].staticPosition = true;

	springSystem = std::make_shared<TriangulationSystem>(particlesVector);
}

void TriangulationScene::load(){
	mainCamera.enableOrtho();

	mainCamera.setTarget(dimensions / 2);

	mainCamera.setPosition(dimensions.x / 2, dimensions.y / 2, 1);
	mainCamera.lookAt(ofVec3f(dimensions / 2), ofVec3f(0, 1, 0));
	mainCamera.setVFlip(true);

	mainCamera.setNearClip(-1000);

	mainCamera.removeAllInteractions();
}

void TriangulationScene::handleClick(int x, int y, int button){
	ofVec2f worldCoords = mainCamera.screenToWorld(ofVec3f(x, y, 0));
	
	if(button == OF_MOUSE_BUTTON_LEFT){

		Particle newParticle(worldCoords);
		springSystem->addParticle(newParticle);
	}
	else if(button == OF_MOUSE_BUTTON_RIGHT){
		springSystem->removeClosestParticle(worldCoords);
	}
	else if(button == OF_MOUSE_BUTTON_MIDDLE){
		springSystem->disableStatic();
	}

}
//------