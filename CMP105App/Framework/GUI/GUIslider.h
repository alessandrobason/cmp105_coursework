#pragma once
#include "GUIelement.h"
#include "../InputHandler.h"

class GUIslider : public GUIelement {
	std::string id = "null";
	sf::Sprite slider;
	sf::RectangleShape line;
	float maxvalue = 0;
	float minvalue = 0;
	InputHandler* in = nullptr;
	float value = 0;

	GUIcallback* callbackobject = nullptr;
	std::function<void(GUIcallback&, std::string id, GUIcallback::RESPONSE value)> callback = &GUIcallback::callback;


	bool mouseisdown = false;

public:
	GUIslider() {}
	GUIslider(const GUIslider& copy) : GUIelement(copy) {
		id = copy.id;
		slider = copy.slider;
		line = copy.line;
		maxvalue = copy.maxvalue;
		minvalue = copy.minvalue;
		in = copy.in;
		callback = copy.callback;
		callbackobject = copy.callbackobject;
	}

	void setMinMaxValue(float min, float max) { minvalue = min; maxvalue = max; }
	void setInput(InputHandler* i) { in = i; }
	void setTexture(sf::Texture* t) override { slider.setTexture(*t); }

	void setId(std::string i) { id = i; }
	void setCallback(GUIcallback* o) { callbackobject = o; }

	virtual void trigger() {
		GUIcallback::RESPONSE r = {};
		r.f = value;
		callback(*callbackobject, id, r);
	}

	void setPosition(sf::Vector2f pos) override {
		GUIelement::setPosition(pos);
		line.setPosition(sf::Vector2f(boxrect.left, boxrect.top + 3));
		slider.setPosition(sf::Vector2f(boxrect.left, boxrect.top));
	}

	void moveSlider(float x){
		if (x < boxrect.left) x = boxrect.left;
		if (x > boxrect.left + boxrect.width) x = boxrect.left + boxrect.width;
		slider.setPosition(sf::Vector2f(x - 3.5, boxrect.top));
		x -= boxrect.left;
		value = x * (maxvalue - minvalue) / boxrect.width;
		value += minvalue;
		std::cout << value << "\n";
	}

	void setValue(float v) {
		if (v < minvalue) v = minvalue;
		if (v > maxvalue) v = maxvalue;
		// x : boxrect.width = v : maxvalue - minvalue)
		float x = v * boxrect.width / (maxvalue - minvalue);
		x += boxrect.left;
		moveSlider(x);
	}

	void load() {
		GUIelement::load();
		if (in == nullptr) {
			std::cout << "InputHandler pointer not passed\n";
			abort();
		}
		if (!slider.getTexture()) {
			std::cout << "Slider texture not loaded\n";
			abort();
		}
		if(maxvalue <= minvalue) {
			std::cout << "Min/Max values are not valid\n";
			abort();
		}

		value = minvalue;
		line.setSize(sf::Vector2f(boxrect.width, 1));
		line.setFillColor(sf::Color::Black);

		alignElement();
	}

	void draw(sf::RenderWindow* w) override {
		w->draw(line);
		w->draw(slider);
	}
	
	void changeControlState(CONTROL_STATES newcontrol) override {

		if (!in->isMouseLDown()) mouseisdown = false;

		if (mouseisdown) {
			moveSlider(in->getMouseRelative().x);
		}

		switch (newcontrol) {
		case CONTROL_STATES::NONE:
			break;
		case CONTROL_STATES::HOVER:
			break;
		case CONTROL_STATES::CLICKDOWN:
			mouseisdown = true;
			trigger();
			break;
		case CONTROL_STATES::CLICKUP:
			break;
		default:
			break;
		}
	}
};
