#include "GUImanager.h"
#include "../Tweening.h"
#include "../RoomManager.h"

GUImanager::GUImanager(sf::RenderWindow* window, InputHandler* input, RoomManager* rm) {
	GUIin = input;
	GUIw = window;
	GUIroommanager = rm;
}

void GUImanager::loadTextures(std::vector<textureload> texturenames) {
	std::unordered_map<std::string, sf::Texture>::iterator it;
	for (size_t i = 0; i < texturenames.size(); i++) {
		it = GUIroommanager->textures.find(texturenames[i].n);
		if (it != GUIroommanager->textures.end()) {
			std::cout << "texture " << texturenames[i].n << " already loaded\n";
			continue;
		}
		// as long as the texture is not already loaded
		if (!GUIroommanager->textures[texturenames[i].n].loadFromFile("Assets/" + texturenames[i].f)) {
			std::cout << "couldn't load " << texturenames[i].n << " texture\n";
			abort();
		}
		std::cout << "Loading " << texturenames[i].n << "\n";
	}
}

void GUImanager::loadFonts(std::vector<fontload> fontnames) {
	std::unordered_map<std::string, sf::Font>::iterator it;
	for (size_t i = 0; i < fontnames.size(); i++) {
		it = GUIroommanager->fonts.find(fontnames[i].n);
		if (it != GUIroommanager->fonts.end()) {
			std::cout << "texture " << fontnames[i].n << " already loaded\n";
			continue;
		}
		// as long as the texture is not already loaded
		if (!GUIroommanager->fonts[fontnames[i].n].loadFromFile("Assets/" + fontnames[i].f)) {
			std::cout << "couldn't load " << fontnames[i].n << " texture\n";
			abort();
		}
		std::cout << "Loading " << fontnames[i].n << "\n";
	}
}

void GUImanager::handleInput(float dt) {
	sf::Vector2f mousepos = GUIin->getMouseRelative();
	bool clicked = GUIin->isMouseLDown();

	for (size_t i = 0; i < elements.size(); i++) {
		if (elements[i]->getRect().contains(mousepos) && clicked) {
			elements[i]->changeControlState(GUIelement::CONTROL_STATES::CLICKDOWN);
		}
		else if (elements[i]->getRect().contains(mousepos) && !clicked && wasmousedown) {
			elements[i]->changeControlState(GUIelement::CONTROL_STATES::CLICKUP);
		}
		else if (elements[i]->getRect().contains(mousepos) && !clicked && !wasmousedown) {
			elements[i]->changeControlState(GUIelement::CONTROL_STATES::HOVER);
		}
		else {
			elements[i]->changeControlState(GUIelement::CONTROL_STATES::NONE);
		}
	}

	wasmousedown = clicked;
}

void GUImanager::draw() {
	for (size_t i = 0; i < elements.size(); i++) {
		elements[i]->draw(GUIw);
	}
}
