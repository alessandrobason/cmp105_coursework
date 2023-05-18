#include "Statue.h"
#include "../Framework/RoomManager.h"

void Statue::interact() {
	if (alreadyfound) return;
	alreadyfound = true;
	roommanager->getCurrentRoom()->setPause(true);

	Event::EventInput dialogue;
	dialogue.dialog = { "You have proven yourself\nworthy.", "Take this." };
	roommanager->eventmanager.addEvent(EventManager::EventType::SAY, dialogue);

	roommanager->eventmanager.addEvent(EventManager::EventType::GETPIECE, {});

	int found = roommanager->getNumberOfPiecesFound() + 1;
	if (found == 1) dialogue.dialog = { "Great!, I've found\n1 piece!" };
	else if (found == 7) dialogue.dialog = { "Great!, I've finally found\nall the pieces!", "Time to go back to the\ncreepy old man." };
	else dialogue.dialog = { "Great!, I've found\n" + std::to_string(found) + " pieces!" };
	roommanager->eventmanager.addEvent(EventManager::EventType::SAY, dialogue);
}