#pragma once
#include <vector>
#include "Event.h"

class EVENTsay : public Event{
public:
	EVENTsay(RoomManager* rm, EventInput input) : Event(rm, input) {}

	void start();
	void update(float dt) override;
	void draw(sf::RenderWindow* w) override;
};