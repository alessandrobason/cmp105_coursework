#include "EVENTfadeinout.h"
#include "..\RoomManager.h"

void EVENTfadeinout::start() {
	sf::Vector2f screensize = roommanager->getInput()->getScreenSize();
	rect.setSize(screensize);
	sf::Uint8 startinga = 0, finala = 255;
	float startingvolume = roommanager->getCurrentSong()->getVolume(), finalvolume = 0.f;
	if (!input.fadeout) {
		startinga = 255;
		finala = 0;
		finalvolume = roommanager->musicvolume;
		startingvolume = 0.f;
	}
	else if(input.fadesong) {
		roommanager->musicvolume = startingvolume;
	}
	rect.setFillColor(sf::Color(input.fadecolor.r, input.fadecolor.g, input.fadecolor.b, startinga));
	fade = Tweening<sf::Uint8>(startinga, finala, input.time);
	if (input.fadesong) {
		fadesong = Tweening<float>(startingvolume, finalvolume, input.time);
	}
}

void EVENTfadeinout::update(float dt) {
	fade.update(dt);
	rect.setFillColor(sf::Color(input.fadecolor.r, input.fadecolor.g, input.fadecolor.b, fade.getValue()));
	if (input.fadesong) {
		fadesong.update(dt);
		roommanager->getCurrentSong()->setVolume(fadesong.getValue());
	}
	finished = fade.isfinished();
}

void EVENTfadeinout::draw(sf::RenderWindow* w) {
	rect.setPosition(w->getView().getCenter() - w->getView().getSize() / 2.f);
	w->draw(rect);
}
