#include "EVENTgetpiece.h"
#include "..\RoomManager.h"

void EVENTgetpiece::start() {
	oldanim = roommanager->getPlayer()->getAnimation()->getCurrentAnimation();
	roommanager->getPlayer()->getAnimation()->setCurrentAnimation("get puzzle piece");
	roommanager->findPiece();
}

void EVENTgetpiece::update(float dt) {
	roommanager->getPlayer()->getAnimation()->animate(dt);
	finished = !roommanager->getPlayer()->getAnimation()->getPlaying();
	roommanager->getPlayer()->setDodging(!finished);
	if (finished) roommanager->getPlayer()->getAnimation()->setCurrentAnimation(oldanim);
}