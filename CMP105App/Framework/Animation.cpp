#include "Animation.h"
#include "GameObject.h"

AnimatedSprite::AnimatedSprite() {
	call_back_function = &GameObject::animationCallback;
}

void AnimatedSprite::draw(sf::RenderWindow* w) {
	w->draw(sprite);
}

void AnimatedSprite::animate(float dt) {
	if (playing) {
		elapsedTime += dt;
		if (elapsedTime >= animations[current_animation].speed) {
			current_frame++;
			if (current_frame >= (int)animations[current_animation].frames.size()) {
				if (callbackobject != nullptr) {
					if (call_back_function(*callbackobject, current_animation)) return;
				}
				if (animations[current_animation].looping) {
					current_frame = 0;
				}
				else {
					current_frame--;
					playing = false;
				}
			}
			sprite.setTextureRect(animations[current_animation].frames[current_frame]);
			elapsedTime = 0;
		}
	}
}

void AnimatedSprite::setCurrentAnimation(std::string c) {
	if (current_animation != c) {
		current_animation = c;
		reset();
	}
}

void AnimatedSprite::addAnimation(std::string name, std::vector<int> frames, float speed, bool looping) {
	Anim a;
	a.speed = speed;
	a.looping = looping;
	for (size_t i = 0; i < frames.size(); i++) {
		int x = frames[i] % columns * width;
		int y = frames[i] / columns * height;
		a.frames.push_back(sf::IntRect(x, y, width, height));
	}
	animations[name] = a;
}

void AnimatedSprite::reset() {
	current_frame = 0;
	elapsedTime = 0;
	playing = true;
	sprite.setTextureRect(animations[current_animation].frames[current_frame]);
}

///////////////////////

void AnimatedTile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = m_tilemap;
	target.draw(tiles, states);
}

void AnimatedTile::animate(float dt) {
	if (playing) {
		for (size_t i = 0; i < elapsedTimes.size(); i++) {
			elapsedTimes[i] += dt;
			if (elapsedTimes[i] >= speeds[i]) {
				current_frames[i] ++;
				if (current_frames[i] >= frames[i].size()) {
					current_frames[i] = 0;
				}
				int j = i * 4;
				sf::Vector2f pos = sf::Vector2f(frames[i][current_frames[i]].left, frames[i][current_frames[i]].top);
				sf::Vector2f size = sf::Vector2f(frames[i][current_frames[i]].width, frames[i][current_frames[i]].height);
				tiles[j].texCoords = pos;
				tiles[j + 1].texCoords = sf::Vector2f(size.x, pos.y);
				tiles[j + 2].texCoords = size;
				tiles[j + 3].texCoords = sf::Vector2f(pos.x, size.y);
				elapsedTimes[i] = 0;
			}
		}
	}
}

void AnimatedTile::reset() {
	for (size_t i = 0; i < elapsedTimes.size(); i++) {
		elapsedTimes[i] = 0.f;
		current_frames[i] = 0;
		int j = i * 4;
		sf::Vector2f pos = sf::Vector2f(frames[i][current_frames[i]].left, frames[i][current_frames[i]].top);
		sf::Vector2f size = sf::Vector2f(frames[i][current_frames[i]].width, frames[i][current_frames[i]].height);
		tiles[j].texCoords = pos;
		tiles[j + 1].texCoords = sf::Vector2f(size.x, pos.y);
		tiles[j + 2].texCoords = size;
		tiles[j + 3].texCoords = sf::Vector2f(pos.x, size.y);
	}
}


