#pragma once
#include "../Framework/Room.h"
#include "../Framework/GUI/GUImanager.h"

class MainMenu : public Room, public GUImanager, public GUIcallback {
public:
	MainMenu() {}
	MainMenu(sf::RenderWindow* window, InputHandler* input, RoomManager* rm);

	void handleInput(float dt) {
		GUImanager::handleInput(dt);
	}

	void start() override;

	void update(float dt) override;

	void draw() override {
		GUImanager::draw();
	}

	void callback(std::string id, RESPONSE value) override;

	GUIbutton loadButton(std::string id);
};