#pragma once
#include "../Framework/Room.h"
#include "../Framework/GUI/GUImanager.h"

class DebugMenu : public Room, public GUImanager, public GUIcallback {

public:
	DebugMenu() {}
	DebugMenu(sf::RenderWindow* window, InputHandler* input, RoomManager* rm);

	void handleInput(float dt) {
		GUImanager::handleInput(dt);
	}

	void start() override;

	void update(float dt);

	void draw() {
		GUImanager::draw();
	}

	void callback(std::string id, RESPONSE value) override;
	GUIcheckbox loadCheckBox(std::string id);
};
