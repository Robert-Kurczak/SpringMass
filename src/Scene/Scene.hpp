#pragma once

#include <vector>
#include <memory>
#include "ofMain.h"

#include "../Components/SpringSystem/SpringSystem.hpp"

//---Base---
class Scene{
	protected:
		ofEasyCam mainCamera;
		ofVec3f dimensions;

		std::vector<std::shared_ptr<SpringSystem>> springSystems;

	public:
		Scene(ofVec3f dimensions);
		
		virtual void load();
		virtual void draw();
};
//------

//---Closest Neighbour Scene---
class ClosestNeighbourScene: public Scene{
	public:
		ClosestNeighbourScene(ofVec3f dimensions);

		void load();
};
//------