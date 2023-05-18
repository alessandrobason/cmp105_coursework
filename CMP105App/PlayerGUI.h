#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Framework/Tweening.h"

class PlayerGUI {
	struct Bar {
		sf::RectangleShape shape;
		Tweening<float> tween;
		sf::Vector2f offset;
		sf::Vector2f size;
	};
	Bar lifebar;
	Bar expbar;
	sf::Sprite bar;
	sf::Vector2f baroffset = sf::Vector2f(88, 1);
	sf::Color colors[10] = {
		sf::Color(32, 180, 74),
		sf::Color(64, 213, 20),
		sf::Color(109, 217, 21),
		sf::Color(172, 229, 14),
		sf::Color(232, 237, 5),
		sf::Color(253, 197, 0),
		sf::Color(255, 128, 0),
		sf::Color(255, 96, 0),
		sf::Color(255, 57, 1),
		sf::Color(255, 0, 41)
	};
	sf::Color expbarcolor = sf::Color(32, 136, 248);
	float remainexp = -1.f;
	float nextlevelexp = 0.f;
	float totallife = 0.f;

public:

	PlayerGUI() {
		lifebar.size = sf::Vector2f(48, 2);
		lifebar.offset = sf::Vector2f(104, 3);
		expbar.size = sf::Vector2f(35, 2);
		expbar.offset = sf::Vector2f(117, 11);

		lifebar.shape.setFillColor(colors[0]);
		lifebar.shape.setSize(lifebar.size);
		expbar.shape.setFillColor(expbarcolor);
		expbar.shape.setSize(sf::Vector2f(0, expbar.size.y));
	}

	void setBarTexture(sf::Texture* t) {
		bar.setTexture(*t);
	}

	void setTotalLife(float tl) { totallife = tl; }
	void setNextLevelExp(float exp) { nextlevelexp = exp; }

	bool isFinished() { return lifebar.tween.isfinished(); }

	void reset() { 
		updateLifeValue(totallife); 
		updateExpValue(0);
	}

	void updateLifeValue(float life) {
		float life_totallife = life / totallife;
		lifebar.tween = Tweening<float>(lifebar.shape.getSize().x, life_totallife * lifebar.size.x, 0.2f);
		sf::Color c = colors[(int)((1.f - life_totallife) * 10)];
		lifebar.shape.setFillColor(c);
		lifebar.shape.setOutlineColor(c);
	}

	void updateExpValue(float exp) {
		float exp_totalexp = exp / nextlevelexp;
		std::cout << "exp: " << exp << " nextlevel: " << nextlevelexp << " // " << exp_totalexp << "\n";
		expbar.tween = Tweening<float>(expbar.shape.getSize().x, exp_totalexp * expbar.size.x, 0.2f);
	}

	void remainExpValue(float exp) {
		remainexp = exp;
	}

	void update(float dt) {
		if (!lifebar.tween.isfinished()) {
			lifebar.tween.update(dt);
			lifebar.shape.setSize(sf::Vector2f(lifebar.tween.getValue(), lifebar.size.y));
		}
		if (!expbar.tween.isfinished()) {
			expbar.tween.update(dt);
			expbar.shape.setSize(sf::Vector2f(expbar.tween.getValue(), expbar.size.y));
			if (expbar.tween.isfinished() && remainexp >= 0.f) {
				expbar.shape.setSize(sf::Vector2f(0, expbar.size.y));
				updateExpValue(remainexp);
				remainexp = -1.f;
			}
		}
	}

	void draw(sf::RenderWindow* w) {
		sf::Vector2f p = w->mapPixelToCoords(sf::Vector2i());

		if (w->getView().getViewport().width != 1.f || w->getView().getViewport().height != 1.f) {
			sf::Vector2f viewsize = w->getView().getSize();
			sf::Vector2f actualviewsize = sf::Vector2f(w->getSize().x * w->getView().getViewport().width, w->getSize().y * w->getView().getViewport().height);
			sf::Vector2f actualcamerasize = (sf::Vector2f)w->getSize();
			sf::Vector2f camerasize = sf::Vector2f(viewsize.x * actualcamerasize.x / actualviewsize.x, viewsize.y * actualcamerasize.y / actualviewsize.y);
			sf::Vector2f cameraoffset = camerasize - viewsize;

			p += (cameraoffset / 2.f);
		}

		bar.setPosition(p + baroffset);
		lifebar.shape.setPosition(p + lifebar.offset);
		expbar.shape.setPosition(p + expbar.offset);
		w->draw(bar);
		w->draw(lifebar.shape);
		w->draw(expbar.shape);
	}
};

