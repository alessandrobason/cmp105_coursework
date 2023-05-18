#include "GUIcheckbox.h"

GUIcheckbox::GUIcheckbox(const GUIcheckbox& copy) : GUIelement(copy) {
	unchecked = copy.unchecked;
	unchecked_hover = copy.unchecked_hover;
	checked = copy.checked;
	checked_hover = copy.checked_hover;
	id = copy.id;
	callback = copy.callback;
	callbackobject = copy.callbackobject;
	ischecked = copy.ischecked;
}

void GUIcheckbox::load() {
	if (checked == nullptr || checked_hover == nullptr || unchecked == nullptr || unchecked_hover == nullptr) {
		std::cout << "Checkbox texture isn't loaded\n";
		abort();
	}
	if (id == "null") {
		std::cout << "Id not set\n";
		abort();
	}

	boxrect.width = 8;
	boxrect.height = 8;

	states.texture = unchecked;

	sf::Vertex v;
	v.position = sf::Vector2f(boxrect.left, boxrect.top);
	v.texCoords = sf::Vector2f(0, 0);
	appendQuad(v, sf::Vector2f(boxrect.width, boxrect.height));
	alignElement();
}

void GUIcheckbox::trigger() {
	GUIcallback::RESPONSE r = {};
	r.b = ischecked;
	callback(*callbackobject, id, r);
}

void GUIcheckbox::changeControlState(CONTROL_STATES newcontrol) {

	switch (newcontrol) {
	case CONTROL_STATES::NONE:
		break;
	case CONTROL_STATES::HOVER:
		break;
	case CONTROL_STATES::CLICKDOWN:
		break;
	case CONTROL_STATES::CLICKUP:
		if (newcontrol != currentcontrol) {
			ischecked = !ischecked;
			trigger();
		}
		break;
	}

	if (ischecked) {
		if (currentcontrol != CONTROL_STATES::NONE) {
			states.texture = checked_hover;
		}
		else {
			states.texture = checked;
		}
	}
	else {
		if (currentcontrol != CONTROL_STATES::NONE) {
			states.texture = unchecked_hover;
		}
		else {
			states.texture = unchecked;
		}
	}


	currentcontrol = newcontrol;
}