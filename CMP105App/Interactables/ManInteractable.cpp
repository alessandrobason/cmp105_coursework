#include "ManInteractable.h"
#include "../Framework/RoomManager.h"

void ManInteractable::interact() {
	// look at player
	sf::Vector2f difference = roommanager->getMan()->getCenter() - roommanager->getPlayer()->getCenter();
	ManObject::DIRECTION direction;
	// talking from the sides
	if (std::abs(difference.x) >= std::abs(difference.y)) {
		if (difference.x > 0) direction = ManObject::DIRECTION::LEFT;
		else				  direction = ManObject::DIRECTION::RIGHT;
	}
	// talking from the bottom
	else					  direction = ManObject::DIRECTION::DOWN;
	roommanager->getMan()->setLastDirection(direction);
	Event::EventInput input;
	input.dialog = { "Have you found all\nmy puzzle pieces?" };
	if (roommanager->foundAllPieces()) {
		/////////////////
		input.dialog.push_back("Thank you, bye bitch.");
		roommanager->eventmanager.addEvent(EventManager::EventType::SAY, input);
		/////////////////
		input.cameramovement.push_back({ sf::Vector2f(0, -112), 3.f });
		roommanager->eventmanager.addEvent(EventManager::EventType::MOVETO, input);
		/////////////////
		input.time = 3.f;
		input.fadesong = true;
		roommanager->eventmanager.addEvent(EventManager::EventType::FADE, input);
		/////////////////
		input.menu = "ending";
		roommanager->eventmanager.addEvent(EventManager::EventType::MENU, input);
	}
	else {
		input.dialog.push_back("Then what are you\ndoing here?");
		roommanager->eventmanager.addEvent(EventManager::EventType::SAY, input);
	}
}