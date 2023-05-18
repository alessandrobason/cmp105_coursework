#include "EVENTsay.h"
#include "..\RoomManager.h"

void EVENTsay::start() {
	roommanager->getTextBoxPointer()->setText(input.dialog);
}

void EVENTsay::update(float dt) {
	roommanager->getTextBoxPointer()->update(dt);
	finished = roommanager->getTextBoxPointer()->isfinished();
}

void EVENTsay::draw(sf::RenderWindow* w) {
	roommanager->getTextBoxPointer()->draw(w);
}
