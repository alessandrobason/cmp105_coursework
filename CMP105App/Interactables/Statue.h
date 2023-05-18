#pragma once
#include "../Framework/Interactable.h"

class Statue : public Interactable {
	bool alreadyfound = false;

public:
	Statue(RoomManager* rm, sf::FloatRect c) : Interactable(rm, c) {}
	Statue(RoomManager* rm, float x, float y, float w, float h) : Interactable(rm, x, y, w, h) {}

	void interact() override;
	void reset() override { alreadyfound = false; }
};