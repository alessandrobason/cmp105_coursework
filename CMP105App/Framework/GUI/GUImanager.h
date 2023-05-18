#pragma once
#include "../InputHandler.h"
#include "../RoomManager.fwd.h"
#include "GUIpanel.h"
#include "GUIbox.h"
#include "GUIbutton.h"
#include "GUIverticalalign.h"
#include "GUIhorizontalalign.h"
#include "GUIcheckbox.h"
#include "GUIslider.h"

class GUImanager {
	InputHandler* GUIin = nullptr;
	sf::RenderWindow* GUIw = nullptr;
	bool wasmousedown = false;

protected:
	RoomManager* GUIroommanager = nullptr;
	std::vector<GUIelement*> elements;

	struct textureload {
		std::string n;
		std::string f;
	};
	struct fontload {
		std::string n;
		std::string f;
	};

public:
	GUImanager() {}
	GUImanager(sf::RenderWindow* window, InputHandler* input, RoomManager* rm);

	void loadTextures(std::vector<textureload> texturenames);
	void loadFonts(std::vector<fontload> fontnames);

	virtual void handleInput(float dt);
	virtual void draw();
};