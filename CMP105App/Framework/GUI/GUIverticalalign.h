#pragma once
#include "GUIelement.h"

class GUIverticalalign : public GUIelement{
	std::vector<GUIelement*> elements;
	sf::Color backgroundcolor = sf::Color::Transparent;

public:
	void setBackgroundColor(sf::Color bc) { backgroundcolor = bc; }
	
	void addElement(GUIelement* e) { elements.push_back(e); e->setParent(this); }

	void load() {
		sf::Vertex v[4];
		v[0].position = sf::Vector2f(boxrect.left, boxrect.top);
		v[1].position = sf::Vector2f(boxrect.left + boxrect.width, boxrect.top);
		v[2].position = sf::Vector2f(boxrect.left + boxrect.width, boxrect.top + boxrect.height);
		v[3].position = sf::Vector2f(boxrect.left, boxrect.top + boxrect.height);
		v[0].color = backgroundcolor;
		v[1].color = backgroundcolor;
		v[2].color = backgroundcolor;
		v[3].color = backgroundcolor;
		vertexs.push_back(v[0]);
		vertexs.push_back(v[1]);
		vertexs.push_back(v[2]);
		vertexs.push_back(v[3]);
		alignElement();
	}

	void alignElements() {
		float totalheight = 0.f;
		for (size_t i = 0; i < elements.size(); i++) {
			totalheight += elements[i]->getRect().height;
		}
		std::cout << "total height: " << totalheight << "\n";
		float spacebetween = (boxrect.height - totalheight) / (elements.size()+1);
		float y = 0;
		for (size_t i = 0; i < elements.size(); i++) {
			y += spacebetween;
			GUIelement* e = elements[i];
			e->setPosition(sf::Vector2f(e->getPosition().x, y));
			//e->setOffset(sf::Vector2f(0, y));
			std::cout << "Y: " << y << "\n";
			y += e->getRect().height;
			e->setAlign(GUIelement::ALIGN::CENTER, GUIelement::ALIGN::NONE);
			e->alignElement();
		}
	}

	void draw(sf::RenderWindow* w) override {
		w->draw(vertexs.data(), vertexs.size(), sf::Quads);
	}
};