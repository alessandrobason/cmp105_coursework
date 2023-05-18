#pragma once
#include <vector>
#include "Event.h"
#include "..\Tweening.h"

class EVENTmoveto : public Event {
	sf::RenderWindow* w;
	InputHandler* in;
	size_t currentcameramovement = -1;
	Tweening<sf::Vector2f> cameratween;

public:
	EVENTmoveto(RoomManager* rm, EventInput input);

	void update(float dt) override;
	void nextCamera();
};