#pragma once
#include "GUIpanel.h"
#include "../Tweening.h"

class GUIsplashscreen : public GUIpanel {
	Tweening<sf::Vector2f> tween1;
	Tweening<sf::Vector2f> tween2;
	Tweening<sf::Vector2f> tween3;
	Tweening<sf::Vector2f> animations[3];
	float finalwait = 2.f;

public:

	void setQuadPosition(int i, sf::Vector2f p) {
		float w = states.texture->getSize().x;
		float h = states.texture->getSize().y;
		vertexs[i].position = p;
		vertexs[i + 1].position = p + sf::Vector2f(w, 0);
		vertexs[i + 2].position = p + sf::Vector2f(w, h);
		vertexs[i + 3].position = p + sf::Vector2f(0, h);
	}

	void load() {
		if (!states.texture) {
			std::cout << "Splash screen texture not loaded\n";
			abort();
		}
		alignElement();

		sf::Vertex v;
		v.position = sf::Vector2f(boxrect.left, boxrect.top);
		v.texCoords = sf::Vector2f();

		// red
		v.color = sf::Color(205, 0, 41);
		appendQuad(v, sf::Vector2f(boxrect.width, boxrect.height));
		// green
		v.color = sf::Color(32, 180, 74);
		appendQuad(v, sf::Vector2f(boxrect.width, boxrect.height));
		// white-ish
		v.color = sf::Color(255, 255, 139);
		appendQuad(v, sf::Vector2f(boxrect.width, boxrect.height));

		float centerx = getPosition().x;
		setPosition(sf::Vector2f(-boxrect.width, getPosition().y));
		sf::Vector2f oldpos = sf::Vector2f(boxrect.width-10 + centerx, 0);
		animations[0] = Tweening<sf::Vector2f>(sf::Vector2f(), sf::Vector2f(boxrect.width-10 + centerx, 0), 3.f);
		for (size_t i = 1; i < 3; i++) {
			sf::Vector2f newpos = oldpos + sf::Vector2f(10, 0);
			animations[i] = Tweening<sf::Vector2f>(oldpos, newpos, 0.3f);
			oldpos = newpos;
		}
	}

	void update(float dt) override {
		if (!animations[0].isfinished()) {
			animations[0].update(dt);
			setQuadPosition(0, animations[0].getValue());
			setQuadPosition(4, animations[0].getValue());
			setQuadPosition(8, animations[0].getValue());
		}
		else if (!animations[1].isfinished()) {
			animations[1].update(dt);
			setQuadPosition(4, animations[1].getValue());
			setQuadPosition(8, animations[1].getValue());
		}
		else if (!animations[2].isfinished()) {
			animations[2].update(dt);
			setQuadPosition(8, animations[2].getValue());
		}
		else if (finalwait > 0){
			finalwait -= dt;
		}
		else {
			dead = true;
		}
	}
};
