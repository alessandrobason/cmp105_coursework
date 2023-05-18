#pragma once
#include "../Framework/Room.h"
#include "../Framework/GUI/GUImanager.h"

class ControlsMenu : public Room, public GUImanager, public GUIcallback {
	sf::Texture backgroundtexture;

public:
	ControlsMenu() {}
	ControlsMenu(sf::RenderWindow* window, InputHandler* input, RoomManager* rm);

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
	GUItext loadLabel(std::string text, sf::Vector2f position);
};