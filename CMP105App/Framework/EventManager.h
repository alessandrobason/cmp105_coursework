#pragma once
#include "RoomManager.fwd.h"
#include "Events/Event.h"
#include "Events/EVENTsay.h"
#include "Events/EVENTwait.h"
#include "Events/EVENTmenu.h"
#include "Events/EVENTmoveto.h"
#include "Events/EVENTgetpiece.h"
#include "Events/EVENTfadeinout.h"

class EventManager {
public:
	enum class EventType {
		SAY,
		WAIT,
		FADE,
		MENU,
		MOVETO,
		GETPIECE,
	};

private:
	RoomManager* roommanager = nullptr;
	std::vector<Event*> events;
	size_t currentevent = 0;
	bool firsttime = true;

public:

	EventManager() {}
	EventManager(RoomManager* rm);

	void addEvent(EventType type, Event::EventInput input);
	void nextEvent();

	size_t getNumberOfEvents() { return events.size(); }

	void update(float dt);
	void draw(sf::RenderWindow* w);
};