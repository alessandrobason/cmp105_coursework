#pragma once
#include <iostream>
#include "Framework/Room.h"
#include "Framework/TextBox.h"
#include "Interactables/Statue.h"
#include "Interactables/ManInteractable.h"
#include "Player.h"
#include "GameObjects/Octorock.h"
#include "GameObjects/ManObject.h"

class Map_room : public Room {
public:
	Map_room(RoomManager* rm, sf::RenderWindow* window, InputHandler* input, std::string fold);
	~Map_room();

	void updateCamera();

	void load(sf::Vector2f offset) override;
	void setPlayer(Player* pl);
	void removePlayer();
	void setPlayerPosition(sf::Vector2f pos);
	sf::Vector2f getPlayerPosition() { return sf::Vector2f(p->collider.rect.left, p->collider.rect.top); };
	Player* getPlayer() { return p; }
	sf::FloatRect getBound(int i) { return bounds[i]; }
	sf::Vector2f getCameraTopLeft() { return camera_top_left; }
	void setCameraPosition(sf::Vector2f position) {
		main_camera.setCenter(position);
		camera_top_left = main_camera.getCenter() - main_camera.getSize() / 2.f;
		w->setView(main_camera);
	}

	void sortGameObjects();

	std::vector<GameObject*>* getGameObjects() { return &sceneObjects; }
	std::vector<Collision*>* getColliders() { return &sceneColliders; }

	void removeObject(GameObject* g);
	void freeMemory();

	void handleInput(float dt) override;
	void update(float dt) override;
	void draw() override;

	void start() override;

	void loadData();
	void resetRoom() override;

	void setPause(bool p) { paused = p; }
	bool getPause() { return paused; }

	Tilemap* getTilemap() { return tilemap; }

	sf::Vector2f moveRoom(sf::Transform t);
	void setBounds(sf::Vector2f offset);
	sf::Vector2f getOffset() { return offset; }
	
private:
	sf::FloatRect bounds[4];

	sf::Vector2f camera_top_left;
	sf::Vector2f camera_bottom_right;

	bool paused = false;

	TextBox* textbox = nullptr;

	// tilemap data
	Tilemap* tilemap = nullptr;
	JSONparser* tilemap_json = nullptr;
	sf::Vector2f offset;
	std::vector<int>* layers = nullptr;
	Tilemap::tilemap_data* tilemap_data = nullptr;
	sf::Shader* shader = nullptr;

	std::vector<Interactable*> interactables;

	// enemies data, used to reset the scene
	std::vector<JSONparser::datatypes> enemiesData;

	// player pointer
	Player* p = nullptr;
};
