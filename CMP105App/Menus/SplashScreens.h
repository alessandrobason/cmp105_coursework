#pragma once
#include "../Framework/Room.h"
#include "../Framework/GUI/GUImanager.h"
#include "../Framework/GUI/GUIsplashscreen.h"

class SplashScreens : public Room, public GUImanager {
	bool finishedanimation = false;

public:
	SplashScreens() {}

	SplashScreens(sf::RenderWindow* window, InputHandler* input, RoomManager* rm);

	void handleInput(float dt) override {
		GUImanager::handleInput(dt);
	}

	void update(float dt) override;

	void draw() {
		GUImanager::draw();
	}
};