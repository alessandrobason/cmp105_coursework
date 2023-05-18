#include "GUIbutton.h"

GUIbutton::GUIbutton(const GUIbutton& copy) : GUItiledelement(copy) {
	id = copy.id;
	tilesize = copy.tilesize;
	normal = copy.normal;
	hover = copy.hover;
	pressed = copy.pressed;
	insidetext = copy.insidetext;
	callback = copy.callback;
	callbackobject = copy.callbackobject;
	hastext = copy.hastext;
}

void GUIbutton::setText(sf::Font* f, std::string text) {
	insidetext.setFont(f);
	insidetext.setText(text);
	insidetext.setCharacterSize(8);
	insidetext.setAlign(ALIGN::CENTER, ALIGN::CENTER);
	hastext = true;
}

void GUIbutton::setPosition(sf::Vector2f pos) {
	GUIelement::setPosition(pos);
}

void GUIbutton::alignElement() {
	GUIelement::alignElement();
	if (hastext) {
		insidetext.alignElement();
		insidetext.update();
	}
}

void GUIbutton::draw(sf::RenderWindow* w) {
	GUIelement::draw(w);
	insidetext.draw(w);
}

void GUIbutton::trigger() {
	callback(*callbackobject, id, {});
}

void GUIbutton::load() {
	GUItiledelement::load();
	if (states.texture == NULL) {
		std::cout << "Button texture not loaded\n";
		abort();
	}
	if (hastext) {
		insidetext.setParent(this);
		insidetext.setOffset(sf::Vector2f(0, -4));
		insidetext.load();
	}
	nineslice();
	alignElement();
	
}

void GUIbutton::changeControlState(CONTROL_STATES newcontrol) {

	switch (newcontrol)	{
	case CONTROL_STATES::NONE:
		if (newcontrol != currentcontrol) {
			//std::cout << "Nothing the button\r";
			states.texture = normal;
			if (newcontrol != currentcontrol && currentcontrol == CONTROL_STATES::CLICKDOWN) {
				insidetext.updatePosition(sf::Vector2f(0, -2));
				insidetext.update();
			}
		}
		break;
	case CONTROL_STATES::HOVER:
		if (newcontrol != currentcontrol) {
			//std::cout << "Hovering the button\r";
			states.texture = hover;
			if (newcontrol != currentcontrol && currentcontrol == CONTROL_STATES::CLICKDOWN) {
				insidetext.updatePosition(sf::Vector2f(0, -2));
				insidetext.update();
			}
		}
		break;
	case CONTROL_STATES::CLICKDOWN:
		if (newcontrol != currentcontrol) {
			states.texture = pressed;
			insidetext.updatePosition(sf::Vector2f(0, 2));
			insidetext.update();
		}
		break;
	case CONTROL_STATES::CLICKUP:
		if (newcontrol != currentcontrol) {
			insidetext.updatePosition(sf::Vector2f(0, -2));
			insidetext.update();
			states.texture = hover;
			trigger();
		}
		break;
	}

	currentcontrol = newcontrol;
}
