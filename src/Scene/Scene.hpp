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

		std::shared_ptr<SpringSystem> springSystem;
		
	public:
		Scene(ofVec3f dimensions);
		
		virtual void load();
		virtual void draw();

		virtual void handleClick(int x, int y, int button);
};
//------

//---Closest Neighbour Scene---
class ClosestNeighbourScene: public Scene{
public:
	ClosestNeighbourScene(ofVec3f dimensions);

	void load() override;
};
//------

//---Triangulation Scene---
class TriangulationScene: public Scene{
public:
	TriangulationScene(ofVec3f dimensions);

	void load() override;
	void handleClick(int x, int y, int button) override;
};
//------