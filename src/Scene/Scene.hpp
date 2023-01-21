#pragma once

#include <vector>
#include <memory>
#include "ofMain.h"
#include "../Components/SpringSystem/SpringSystem.hpp"

class Scene{
	protected:
		ofEasyCam mainCamera;
		ofVec3f dimensions;
		std::vector<std::shared_ptr<SpringSystem>> springSystems;

	public:
		Scene(ofVec3f dimensions);
		
		void load();
		void draw();
};

class ClosestNeighbourScene: public Scene{
	public:
		ClosestNeighbourScene(ofVec3f dimensions);
};