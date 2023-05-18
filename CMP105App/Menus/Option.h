#pragma once
#include "../Framework/Room.h"
#include "../Framework/GUI/GUImanager.h"

class OptionMenu : public Room, public GUImanager, public GUIcallback {
	GUIslider* volumepointer = nullptr;

public:
	OptionMenu() {}
	~OptionMenu() {
		delete volumepointer;
		volumepointer = nullptr;
	}

	OptionMenu(sf::RenderWindow* window, InputHandler* input, RoomManager* rm);

	void start() override;

	void handleInput(float dt) {
		GUImanager::handleInput(dt);
	}

	void update(float dt);

	void draw() {
		GUImanager::draw();
	}

	void callback(std::string id, RESPONSE value) override;
};