#pragma once
#include <string>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "..\RoomManager.fwd.h"
#include "..\GameObject.h"

class Event {
protected:
	RoomManager* roommanager = nullptr;
	bool finished = false;

public:
	struct EventInput {
		std::vector<std::string> dialog;
		GameObject* character = nullptr;
		sf::Vector2f target;
		struct CAMERAMOVEMENTSTRUCT {
			sf::Vector2f position;
			float time = 0.f;
		};
		std::vector<CAMERAMOVEMENTSTRUCT> cameramovement;
		sf::Color fadecolor = sf::Color::Black;
		float time = 0.f;
		bool fadeout = true;
		bool fadesong = false;
		std::string menu = "";
	} input;

	Event(RoomManager* rm, EventInput inp) {
		roommanager = rm;
		input = inp;
	}

	virtual void start() {}

	virtual void update(float dt) {
		std::cout << "I'm an event!\n";
		finished = true;
	}
	virtual void draw(sf::RenderWindow* w) {}

	bool isfinished() { return finished; }
};