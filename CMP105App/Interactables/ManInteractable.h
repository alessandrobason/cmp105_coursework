#pragma once
#include "../Framework/Interactable.h"

class ManInteractable : public Interactable {
public:
	ManInteractable(RoomManager* rm, sf::FloatRect c) : Interactable(rm, c) {}
	ManInteractable(RoomManager* rm, float x, float y, float w, float h) : Interactable(rm, x, y, w, h) {}

	void interact() override;
};