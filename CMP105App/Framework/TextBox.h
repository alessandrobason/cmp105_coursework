#pragma once
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "RoomManager.fwd.h"
#include "InputHandler.h"
#include "GUI/GUItiledelement.h"

class TextBox : GUItiledelement {
	RoomManager* roommanager = nullptr;
	InputHandler* in = nullptr;
	sf::RenderStates state;
	std::vector<std::string> fulldialog;
	std::string fulltext = "";
	std::string showntext = "";
	sf::Text text;
	sf::Clock textclock;
	float textupdatetime = 0.05f;
	int visiblecharacters = 1;
	int currentdialog = 0;
	bool next_dialog = false;
	bool finished = true;

public:
	TextBox() {}
	TextBox(RoomManager* rm, InputHandler* input);

	bool isfinished() { return finished; }

	void setText(std::vector<std::string> t);

	void update(float dt);

	void draw(sf::RenderWindow* w) override;
};