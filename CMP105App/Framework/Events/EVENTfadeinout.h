#pragma once
#include <vector>
#include "Event.h"
#include "../Tweening.h"

class EVENTfadeinout : public Event {
	sf::Vertex quad[4];
	sf::RectangleShape rect;
	Tweening<sf::Uint8> fade;
	Tweening<float> fadesong;

public:
	EVENTfadeinout(RoomManager* rm, EventInput input) : Event(rm, input) {}

	void start();
	void update(float dt) override;
	void draw(sf::RenderWindow* w) override;
};