#pragma once
#include "../Framework/Room.h"
#include "../Framework/GUI/GUImanager.h"
#include "../Framework/Tweening.h"

class Ending : public Room, public GUImanager, public GUIcallback {
	GUIpanel* backgroundpointer = nullptr;
	GUItext* creditspointer = nullptr;
	sf::Color textcolor = sf::Color(255, 255, 139, 0);
	Tweening<float> fade;
	bool fadingout = false;
	std::vector<std::string> finalcredits;
	size_t positionincredits = 0;
	float fadetime = 1.f;
	float timeleft = fadetime;

public:
	Ending() {}
	Ending(sf::RenderWindow* window, InputHandler* input, RoomManager* rm);

	void handleInput(float dt) {
		GUImanager::handleInput(dt);
	}

	void resetRoom() override;

	void start() override;

	void update(float dt);

	void draw();

	void callback(std::string id, RESPONSE value) override;
	GUIbutton loadButton(std::string id);
};