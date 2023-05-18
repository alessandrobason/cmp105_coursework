#pragma once
#include "GUItiledelement.h"
#include "GUItext.h"
#include "GUIcallback.h"
#include <functional>

class GUImanager;

class GUIbutton : public GUItiledelement {
	sf::Texture* normal = nullptr;
	sf::Texture* hover = nullptr;
	sf::Texture* pressed = nullptr;

	std::string id = "null";
	
	GUItext insidetext;
	bool hastext = false;

	GUIcallback* callbackobject = nullptr;
	std::function<void(GUIcallback&, std::string id, GUIcallback::RESPONSE value)> callback = &GUIcallback::callback;

public:
	GUIbutton() : GUItiledelement() {}
	GUIbutton(const GUIbutton& copy);

	void setId(std::string i) { id = i; }
	void setText(sf::Font* f, std::string text);
	void setNormalTexture(sf::Texture* n) { normal = n; }
	void setHoverTexture(sf::Texture* h) { hover = h; }
	void setPressedTexture(sf::Texture* p) { pressed = p; }

	void setPosition(sf::Vector2f pos) override;
	void alignElement() override;

	void setCallback(GUIcallback* o) { callbackobject = o; }

	int getCharacterSize() { return insidetext.getCharacterSize(); }
	void setCharacterSize(int s) { insidetext.setCharacterSize(s); }

	void draw(sf::RenderWindow* w) override;

	virtual void trigger();

	void load();

	void changeControlState(CONTROL_STATES newcontrol) override;
};