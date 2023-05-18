#pragma once
#include "../Framework/Room.h"
#include "../Framework/GUI/GUImanager.h"

class PauseMenu : public Room, public GUImanager, public GUIcallback {
	sf::Texture backgroundtexture;

public:
	PauseMenu() {}
	PauseMenu(sf::RenderWindow* window, InputHandler* input, RoomManager* rm);

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