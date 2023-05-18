#pragma once
#include <vector>
#include "Event.h"
#include "../Tweening.h"

class EVENTwait : public Event {

public:
	EVENTwait(RoomManager* rm, EventInput input) : Event(rm, input) {}

	void update(float dt) override {
		input.time -= dt;
		finished = input.time <= 0;
	}
};