#pragma once
#include <SFML/Graphics.hpp>
#include "JSONparser/JSONparser.h"
#include "Framework/GameObject.h"
#include "Framework/InputHandler.h"
#include "Framework/Collision.h"
#include "Framework/Animation.h"
#include "Framework/Weapon.h"

class Player : public GameObject {
public:
	enum DIRECTIONS {
		UP_RIGHT,
		DOWN_RIGHT,
		DOWN_LEFT,
		UP_LEFT,
	};

	enum CHEATS {
		GODMODE,
		WALKTHROUGHWALLS,
		FOUNDALLPIECES,
		CHEATS_COUNT
	};

	struct PLAYER_DATA {
		float baselife = 0.f;
		float basedamage = 0.f;
		float totallife = 0.f;
		float life = 0.f;
		int level = 1;
		float exp = 0.f;
		float expneeded = 1.f;
	} playerdata;

private:
	JSONparser* config;
	
	bool pressed_keys[256] = { false };

	std::string directionnames[4] = { "up-right", "down-right", "down-left", "up-left" };
	AnimatedSprite animSprite;
	DIRECTIONS last_direction = DOWN_RIGHT;

	sf::Vector2f local_center;
	float angle_to_mouse = 0.f;

	bool draw_weapon_over = false;

	bool canmove = true;
	bool isdodging = false;

	bool hascheated = false;

	bool cheatsarray[CHEATS::CHEATS_COUNT] = { false };

public:
	Player();
	Player(InputHandler* input, RoomManager* rm, sf::RenderWindow* win);

	void handleInput(float dt) override;
	void update(float dt) override;
	void updateAnimation(float dt) override;
	void draw() override;
	void drawDebug() override;
	void setVisible(bool v) override;

	bool animationCallback(std::string name) override;
	
	float getAngleToMouse() { return angle_to_mouse; }

	void move(sf::Vector2f offset);

	void setCanMove(bool c) { canmove = c; }
	bool getCanMove() { return canmove; }

	void hit(float damage) override;

	void setLife(float l) { playerdata.totallife = l; playerdata.life = l; }
	float getLife() { return playerdata.life; }

	void giveExp(float e);
	float nextLevelExp(int level);
	void reset();
	void levelUp();

	void setDodging(bool d) { isdodging = d; }
	bool getDodging() { return isdodging; }

	void setPosition(sf::Vector2f pos);
	DIRECTIONS getDirection() { return last_direction; }
	AnimatedSprite* getAnimation() { return &animSprite; }
	void setCurrentAnimation(std::string anim) { animSprite.setCurrentAnimation(anim); }
	sf::Vector2f getLocalCenter() { return local_center; }

	static std::string getGameObjectString() { return ""; }

	sf::Sprite* getSprite() override { return animSprite.getSprite(); };

	void setCheat(CHEATS c, bool b) { cheatsarray[c] = b; if (b) hascheated = true; }
	bool getCheat(CHEATS c) { return cheatsarray[c]; }
	bool hasCheated() { return hascheated; }

	Weapon bow;
};

