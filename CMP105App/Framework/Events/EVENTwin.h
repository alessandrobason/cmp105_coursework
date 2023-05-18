#pragma once
#include <vector>
#include "Event.h"

class EVENTwin : public Event {
public:
	EVENTwin(RoomManager* rm, EventInput input) : Event(rm, input) {}

	void start();
};