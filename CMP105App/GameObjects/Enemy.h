#pragma once
#include <stdlib.h>
#include "../Framework/GameObject.h"
#include "../Framework/Animation.h"

class Enemy : public GameObject {
public:
	Enemy();
	Enemy(const Enemy& e);

	void update(float dt) override;
	void draw() override;
	void drawDebug() override;
	void hit(float damage) override;
	void move(sf::Vector2f mov) override;
	void setPosition(sf::Vector2f position) override;
	void setDamage(float d) { damage = d; }

	void checkDistanceWithGameObjects();

	void die();

	void setAnimatedSprite(AnimatedSprite a) { animation = a; }
	void setLife(float l) { life = l; }
	float getLife() { return life; }
	void setProjectile(bool p) { isprojectile = p; }

	void isPlayerInside(bool p) { isplayerinside = p; }

	sf::Sprite* getSprite() override { return animation.getSprite(); }

protected:
	enum DIRECTION {
		UP, DOWN, LEFT, RIGHT
	};
	
	std::string directionnames[4] = { "up", "down", "left", "right" };
	AnimatedSprite animation;
	DIRECTION last_direction = DIRECTION::DOWN;
	float life = 0.f;
	float damage = 0.f;
	bool isprojectile = false;
	sf::Vector2f target;

	float angletoplayer = 0.f;
	bool isplayerinside = false;
	bool moving = false;

	//FINITE STATE MACHINE (AI)
	enum class states {
		IDLE,
		ATTACK,
		MOVING
	} currentstate;
};

