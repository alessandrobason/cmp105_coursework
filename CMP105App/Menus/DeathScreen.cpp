#include "DeathScreen.h"
#include "../Framework/RoomManager.h"


DeathScreen::DeathScreen(sf::RenderWindow* window, InputHandler* input, RoomManager* rm) : Room("", window, input, rm), GUImanager(window, input, rm) {
	main_camera.setCenter(Room::in->getScreenSize() / 2.f);
	Room::w->setView(main_camera);

	std::vector<textureload> texturestoload;
	std::vector<fontload> fontstoload;

	texturestoload.push_back({ "deathbackground", "GUI/dead.png" });
	texturestoload.push_back({ "guibutton", "GUI/button.png" });
	texturestoload.push_back({ "guibuttonhover", "GUI/buttonhover.png" });
	texturestoload.push_back({ "guibuttonpressed", "GUI/buttonpressed.png" });
	fontstoload.push_back({ "font", "TLOZ-Links-Awakening.ttf" });
	
	loadTextures(texturestoload);
	loadFonts(fontstoload); 

	GUIpanel background;
	background.setTexture(&roommanager->textures["deathbackground"]);
	background.setRect(sf::FloatRect(0, 0, in->getScreenSize().x, in->getScreenSize().y));
	background.load();

	GUIverticalalign verticalalign;
	verticalalign.setParent(&background);
	verticalalign.setRect(sf::FloatRect(79, 75, 48, 40));
	verticalalign.setAlign(GUIelement::ALIGN::NONE, GUIelement::ALIGN::NONE);
	verticalalign.load();

	GUIbutton restart = loadButton("restart");
	restart.setParent(&verticalalign);
	restart.setRect(sf::FloatRect(0, 0, 48, 18));
	restart.setText(&roommanager->fonts["font"], "restart");
	restart.load();

	GUIbutton menu = loadButton("menu");
	menu.setParent(&verticalalign);
	menu.setRect(sf::FloatRect(0, 0, 48, 18));
	menu.setText(&roommanager->fonts["font"], "menu");
	menu.load();

	verticalalign.addElement(&restart);
	verticalalign.addElement(&menu);
	verticalalign.alignElements();

	elements.push_back(new GUIpanel(background));
	elements.push_back(new GUIbutton(restart));
	elements.push_back(new GUIbutton(menu));
}

void DeathScreen::start() {
	roommanager->playSong("menu");
	roommanager->restartGame();
}

void DeathScreen::update(float dt) {
	main_camera.setViewport(Room::in->getView().getViewport());
	Room::w->setView(main_camera);
}

void DeathScreen::callback(std::string id, RESPONSE value) {
	if (id == "menu") {
		roommanager->moveMenu("mainmenu");
	}
	else if (id == "restart") {
		roommanager->moveMenu("game");
	}
}

GUIbutton DeathScreen::loadButton(std::string id) {
	GUIbutton button;
	button.setId(id);
	button.setTexture(&roommanager->textures["guibutton"]);
	button.setNormalTexture(&roommanager->textures["guibutton"]);
	button.setHoverTexture(&roommanager->textures["guibuttonhover"]);
	button.setPressedTexture(&roommanager->textures["guibuttonpressed"]);
	button.setTileSize(8);
	button.setCallback(this);
	return button;
}