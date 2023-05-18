#pragma once
#include <vector>
#include "Event.h"

class EVENTgetpiece : public Event {
	std::string oldanim = "";

public:
	EVENTgetpiece(RoomManager* rm, EventInput input) : Event(rm, input) {}

	void start();
	void update(float dt) override;
};