#pragma once
#include <SFML/Network.hpp>
#include "../Framework/Room.h"
#include "../Framework/GUI/GUImanager.h"

class LeaderboardMenu : public Room, public GUImanager, public GUIcallback {
	sf::Http http;
	sf::Http::Request request;

	GUIverticalalign* verticalalign = nullptr;
	GUItext* leaderboardpointers[5] = { nullptr };

public:
	LeaderboardMenu() {}
	LeaderboardMenu(sf::RenderWindow* window, InputHandler* input, RoomManager* rm);

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