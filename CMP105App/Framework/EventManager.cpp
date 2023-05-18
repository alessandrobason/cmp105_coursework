#include "EventManager.h"
#include "RoomManager.h"

EventManager::EventManager(RoomManager* rm) {
	roommanager = rm;
}

void EventManager::addEvent(EventType type, Event::EventInput input) {
	switch (type) {
	case EventType::SAY:
		events.push_back(new EVENTsay(roommanager, input));
		break;
	case EventType::MOVETO:
		events.push_back(new EVENTmoveto(roommanager, input));
		break;
	case EventType::GETPIECE:
		events.push_back(new EVENTgetpiece(roommanager, input));
		break;
	case EventType::FADE:
		events.push_back(new EVENTfadeinout(roommanager, input));
		break;
	case EventType::WAIT:
		events.push_back(new EVENTwait(roommanager, input));
		break;
	case EventType::MENU:
		events.push_back(new EVENTmenu(roommanager, input));
		break;
	}
}

void EventManager::nextEvent() {
	events.erase(events.begin());
}

void EventManager::update(float dt) {
	//std::cout << "Number of events right now: " << events.size() << "\n";

	if (events.size() > 0) {
		roommanager->getCurrentRoom()->setPause(true);
		if (firsttime) {
			events[currentevent]->start();
			firsttime = false;
		}
		events[currentevent]->update(dt);
		if (events[currentevent]->isfinished()) {
			delete events[currentevent];
			currentevent++;
			if (currentevent >= events.size()) {
				currentevent = 0;
				events.clear();
				roommanager->getCurrentRoom()->setPause(false);
				firsttime = true;
				return;
			}
			events[currentevent]->start();
		}
	}
}

void EventManager::draw(sf::RenderWindow* w) {
	if (events.size() > 0) {
		events[currentevent]->draw(w);
	}
}