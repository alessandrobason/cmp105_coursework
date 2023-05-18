#pragma once
#include "GUIelement.h"

class GUIpanel : public GUIelement {
public:
	void load() {
		sf::Vertex v;
		v.position = sf::Vector2f(boxrect.left, boxrect.top);
		appendQuad(v, sf::Vector2f(boxrect.width, boxrect.height));
	}

	void updateTexture() {
		float w = (float) states.texture->getSize().x;
		float h = (float) states.texture->getSize().y;

		sf::Vector2f textureoffset[4] = { 
			sf::Vector2f(0, 0), sf::Vector2f(w, 0), sf::Vector2f(w, h), sf::Vector2f(0, h)
		};

		sf::Vector2f coords = sf::Vector2f(boxrect.left, boxrect.top);
		sf::Vector2f positionoffset[4] = {
			sf::Vector2f(0, 0),
			sf::Vector2f(boxrect.width, 0),
			sf::Vector2f(boxrect.width, boxrect.height),
			sf::Vector2f(0, boxrect.height),
		};

		for (size_t i = 0; i < 4; i++) {
			sf::Vertex* v = &vertexs[i];
			v->position = coords + positionoffset[i];
			v->texCoords = textureoffset[i];
			v->color = sf::Color::White;
		}
	}
};