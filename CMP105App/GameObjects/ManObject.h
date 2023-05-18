#pragma once
#include <stdlib.h>
#include "../Framework/GameObject.h"
#include "../Framework/Animation.h"

class ManObject : public GameObject {
public:
	ManObject() {}
	ManObject(InputHandler* input, RoomManager* rm, sf::RenderWindow* win);

	enum DIRECTION {
		UP, DOWN, LEFT, RIGHT
	};

	void update(float dt) override;
	void draw() override;

	void hit(float damage) override;

	void setAnimatedSprite(AnimatedSprite a) { animation = a; }
	void updateAnimation(float dt) override;

	void setLastDirection(DIRECTION d) { last_direction = d; }

	sf::Sprite* getSprite() override { return animation.getSprite(); }

protected:

	struct a {
		std::string name;
		std::vector<int> frames;
	};

	std::string directionnames[4] = { "up", "down", "left", "right" };
	AnimatedSprite animation;
	DIRECTION last_direction = DIRECTION::DOWN;
};

