#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "../JSONparser/JSONparser.h"
#include "InputHandler.h"
#include "GameObject.h"
#include "Tilemap.h"
#include "Room.fwd.h"
#include "RoomManager.fwd.h"

class Room {
public:
	Room() {}
	Room(std::string fold, sf::RenderWindow* window, InputHandler* input, RoomManager* rm);
	~Room();

	virtual void handleInput(float dt) {}
	virtual void update(float dt) {}
	virtual void draw() {}
	virtual void load(sf::Vector2f offset) {}
	virtual void start() {}

	sf::View getMainCamera() { return main_camera; }
	std::string getFile() { return FILE; }

	void setMainCamera(sf::View c) { main_camera = c; }

	virtual void resetRoom() {}

	bool* isloaded = nullptr;

	struct gameobjectsorting {
		inline bool operator() (GameObject* g1, GameObject* g2) {
			return g1->getY() < g2->getY();
		}
	};

protected:
	// input handler
	InputHandler* in = nullptr;
	// render window
	sf::RenderWindow* w = nullptr;

	// room manager
	RoomManager* roommanager = nullptr;

	// useful information
	std::string FILE;
	const std::string ASSETS = "Assets/";

	// main camera
	sf::View main_camera;

	// vectors with scene objects/colliders
	std::vector<GameObject*> sceneObjects;
	std::vector<GameObject*> destroyedSceneObjects;
	std::vector<GameObject*> invisibleSceneObjects;
	std::vector<Collision*> sceneColliders;
	std::vector<Collision*> invisibleSceneColliders;
};
