#include "ManObject.h"
#include "..\Framework\RoomManager.h"

ManObject::ManObject(InputHandler* input, RoomManager* rm, sf::RenderWindow* win) : GameObject(input, rm, win) {
	if (roommanager->textures["man"].getSize() == sf::Vector2u()) {
		if (!roommanager->textures["man"].loadFromFile("Assets/man.png")) {
			std::cout << "couldn't load man spritesheet\n";
			abort();
		}
	}
	collider = Collision(0, 0, 16, 16, Collision::LAYER::NONE);
	animation.setSpriteSheet(&roommanager->textures["man"], 5, 2);
	animation.addAnimation("idle down", { 0 }, 0.f);
	animation.addAnimation("idle left", { 3 }, 0.f);
	animation.addAnimation("idle up", { 5 }, 0.f);
	animation.addAnimation("idle right", { 8 }, 0.f);
	animation.addAnimation("walk down", { 1, 0, 2, 0 }, 0.1f);
	animation.addAnimation("walk left", { 4, 3 }, 0.1f);
	animation.addAnimation("walk up", { 6, 5, 7, 5 }, 0.1f);
	animation.addAnimation("walk right", { 9, 8 }, 0.1f);
	animation.setCurrentAnimation("idle up");
	last_direction = DIRECTION::UP;
	setPosition(roommanager->getCurrentRoom()->getOffset() + sf::Vector2f(240, 192));
	setSpeed(50.f);
}

void ManObject::update(float dt) {
	vel = sf::Vector2f();
	updateAnimation(dt);
}

void ManObject::draw() {
	animation.draw(w);
}

void ManObject::hit(float damage) {

}

void ManObject::updateAnimation(float dt) {
	std::string anim = "idle ";
	if (vel != sf::Vector2f()) anim = "walk ";

	if (vel.x < 0) last_direction = DIRECTION::LEFT;
	else if (vel.x > 0) last_direction = DIRECTION::RIGHT;
	if (vel.y < 0) last_direction = DIRECTION::UP;
	else if (vel.y > 0) last_direction = DIRECTION::DOWN;

	anim += directionnames[last_direction];

	animation.setCurrentAnimation(anim);
	animation.animate(dt);
}