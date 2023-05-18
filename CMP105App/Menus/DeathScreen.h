#pragma once
#include "../Framework/Room.h"
#include "../Framework/GUI/GUImanager.h"

class DeathScreen : public Room, public GUImanager, public GUIcallback {
public:
	DeathScreen() {}
	DeathScreen(sf::RenderWindow* window, InputHandler* input, RoomManager* rm);

	void handleInput(float dt) {
		GUImanager::handleInput(dt);
	}

	void start() override;

	void update(float dt);

	void draw() {
		GUImanager::draw();
	}

	void callback(std::string id, RESPONSE value) override;
	GUIbutton loadButton(std::string id);
};