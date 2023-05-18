#pragma once
#include "GUIelement.h"
#include "GUIcallback.h"
#include <functional>

class GUIcheckbox : public GUIelement {
	sf::Texture* unchecked = nullptr;
	sf::Texture* unchecked_hover = nullptr;
	sf::Texture* checked = nullptr;
	sf::Texture* checked_hover = nullptr;

	std::string id = "null";

	GUIcallback* callbackobject = nullptr;
	std::function<void(GUIcallback&, std::string id, GUIcallback::RESPONSE value)> callback = &GUIcallback::callback;

	bool ischecked = false;

public:
	GUIcheckbox() {}
	GUIcheckbox(const GUIcheckbox& copy);

	void setId(std::string i) { id = i; }
	void setCheckedTexture(sf::Texture* c, sf::Texture* ch) { checked = c; checked_hover = ch; }
	void setUncheckedTexture(sf::Texture* u, sf::Texture* uh) { unchecked = u; unchecked_hover = uh; }

	void setCallback(GUIcallback* o) { callbackobject = o; }

	virtual void trigger();

	void changeControlState(CONTROL_STATES newcontrol) override;

	void load();
};