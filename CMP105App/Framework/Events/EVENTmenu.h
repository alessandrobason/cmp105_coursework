#pragma once
#include <vector>
#include "Event.h"

class EVENTmenu : public Event {
	std::string oldanim = "";

public:
	EVENTmenu(RoomManager* rm, EventInput input) : Event(rm, input) {}

	void start();
};