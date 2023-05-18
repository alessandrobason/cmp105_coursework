#pragma once
#include "Enemy.h"
#include "../Framework/Projectiles.h"

class Octorock : public Enemy {
	Projectiles projectiles; 
	float shootingspeed = 0.3f;
	sf::Clock timepassed;
	bool shooting = false;

public:
	Octorock(const Enemy& e);

	void update(float dt) override;
	void draw() override;
	void drawDebug() override;

	void Advance() override;
	void hit(float damage) override;
	bool animationCallback(std::string name) override;
};

