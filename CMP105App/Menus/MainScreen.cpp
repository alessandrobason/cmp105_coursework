#include "MainScreen.h"
#include "../Framework/RoomManager.h"

MainScreen::MainScreen(sf::RenderWindow* window, InputHandler* input, RoomManager* rm) : Room("MainScreen", window, input, rm), GUImanager(window, input, rm) {
	main_camera.setCenter(Room::in->getScreenSize() / 2.f);
	Room::w->setView(main_camera);

	std::vector<textureload> texturestoload;
	std::vector<fontload> fontstoload; 

	texturestoload.push_back({ "guibox", "GUI/box.png" });
	texturestoload.push_back({ "guibutton", "GUI/button.png" });
	texturestoload.push_back({ "guibuttonhover", "GUI/buttonhover.png" });
	texturestoload.push_back({ "guibuttonpressed", "GUI/buttonpressed.png" });
	texturestoload.push_back({ "titlescreen", "GUI/titlescreen.png" });

	fontstoload.push_back({ "font", "TLOZ-Links-Awakening.ttf" });
	
	loadTextures(texturestoload);
	loadFonts(fontstoload);

	GUIpanel mainbackground;
	mainbackground.setTexture(&roommanager->textures["titlescreen"]);
	mainbackground.setRect(sf::FloatRect(0, 0, in->getScreenSize().x, in->getScreenSize().y));
	mainbackground.load();

	GUIbutton button;
	button.setParent(&mainbackground);
	button.setId("start");
	button.setAlign(GUIelement::ALIGN::CENTER, GUIelement::ALIGN::BOTTOM);
	button.setOffset(sf::Vector2f(0, -5));
	button.setTexture(&roommanager->textures["guibutton"]);
	button.setNormalTexture(&roommanager->textures["guibutton"]);
	button.setHoverTexture(&roommanager->textures["guibuttonhover"]);
	button.setPressedTexture(&roommanager->textures["guibuttonpressed"]);
	button.setRect(sf::FloatRect(0, 0, 64, 24));
	button.setTileSize(8);
	button.setText(&roommanager->fonts["font"], "start");
	button.setCallback(this);
	button.load();

	elements.push_back(new GUIpanel(mainbackground));
	elements.push_back(new GUIbutton(button));
}

void MainScreen::start() {
	roommanager->playSong("menu");
	roommanager->setVolume(100.f);
}

void MainScreen::update(float dt) {
	main_camera.setViewport(Room::in->getView().getViewport());
	Room::w->setView(main_camera);
}

void MainScreen::callback(std::string id, RESPONSE value) {
	if (id == "start") {
		roommanager->moveMenu("mainmenu");
	}
}