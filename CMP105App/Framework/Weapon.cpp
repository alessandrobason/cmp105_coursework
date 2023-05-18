#include "Weapon.h"

Weapon::Weapon(sf::Texture* txt, sf::Vector2i tex_coords, InputHandler* i, Collision::LAYER l, RoomManager* rm) {
	in = i;
	setTexture(*txt);
	setTextureRect(sf::IntRect(tex_coords.x, tex_coords.y, 16, 16));
	setOrigin(12, 12);
	projectiles = Projectiles(txt, sf::Vector2i(16, 0), l, rm);
	projectiles.setOrientation(sf::Vector2f(-1, -1));
}

void Weapon::handleInput(float dt) {
	if (in->isMouseLPressed()) {
		shoot();
	}
	angle_to_mouse -= 45;
}

void Weapon::update(float dt) {
	projectiles.update(dt);
	setRotation(angle_to_mouse);
}

void Weapon::drawArrows(sf::RenderWindow* w) {
	projectiles.draw(w);
}

void Weapon::drawDebug(sf::RenderWindow* w) {
	projectiles.drawDebug(w);
}

void Weapon::shoot() {
	projectiles.shoot(getTransform());
}

void Weapon::move(sf::Vector2f offset) {
	sf::Sprite::move(offset);
}