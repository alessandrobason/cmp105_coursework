#include "EVENTmenu.h"
#include "..\RoomManager.h"

void EVENTmenu::start() {
	roommanager->setCurrentState(RoomManager::STATES::MENU);
	roommanager->setCurrentMenu(input.menu);
	roommanager->startCurrentMenu();
}