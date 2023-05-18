#include "Interactable.h"
#include "RoomManager.h"

Interactable::Interactable(RoomManager* rm, sf::FloatRect c) : Collision(c, LAYER::ALL) {
	roommanager = rm;
}

Interactable::Interactable(RoomManager* rm, float x, float y, float w, float h) : Collision(x, y, w, h, LAYER::ALL) {
	roommanager = rm;
}

void Interactable::interact() {
	std::cout << "interacted\n";
}