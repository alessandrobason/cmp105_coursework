#pragma once
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

class Collision {
private:
	bool isenabled = true;

	sf::RectangleShape debug;

	void setupDebugBox(sf::FloatRect r);
	
	struct IntCircle {
		sf::Vector2i pos;
		int radius;
	};

public:
	enum class LAYER {
		ALL,
		NONE,
		WATER,
		OBJECT,
		PLAYER,
		ENEMY
	};
	
	Collision();
	Collision(sf::FloatRect r, LAYER type);
	Collision(int x, int y, int w, int h, LAYER type);

	~Collision();

	void setEnabled(bool e) { isenabled = e; }
	void enable() { isenabled = true; }
	void disable() { isenabled = false; }
	bool isEnabled() { return isenabled; }

	void setDebugPosition(sf::Vector2f pos) { debug.setPosition(pos); }
	void setDebugSize(sf::Vector2f size) { debug.setSize(size); }
	void setDebugColor(sf::Color c) { debug.setOutlineColor(c); }

	bool Check_Collision(sf::FloatRect r);

	void setPosition(sf::Vector2f pos);
	void setCenter(sf::Vector2f c);
	void moveCollision(sf::Vector2f mov);
	
	sf::Vector2f getCollisionSide(sf::FloatRect r, sf::Vector2f& oldVel);

	void drawDebug(sf::RenderWindow* w);

	LAYER collisionlayer;
	sf::FloatRect rect;
	sf::Vector2f collision_offset;
	IntCircle circle;
};