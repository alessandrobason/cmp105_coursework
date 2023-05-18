#include "PauseMenu.h"
#include "../Framework/RoomManager.h"

PauseMenu::PauseMenu(sf::RenderWindow* window, InputHandler* input, RoomManager* rm) : Room("", window, input, rm), GUImanager(window, input, rm) {
	main_camera.setCenter(Room::in->getScreenSize() / 2.f);
	Room::w->setView(main_camera);

	std::vector<textureload> texturestoload;
	std::vector<fontload> fontstoload;

	texturestoload.push_back({ "guibutton", "GUI/button.png" });
	texturestoload.push_back({ "guibuttonhover", "GUI/buttonhover.png" });
	texturestoload.push_back({ "guibuttonpressed", "GUI/buttonpressed.png" });

	fontstoload.push_back({ "font", "TLOZ-Links-Awakening.ttf" });

	loadTextures(texturestoload);
	loadFonts(fontstoload);

	GUIpanel background;
	background.setRect(sf::FloatRect(0, 0, in->getScreenSize().x, in->getScreenSize().y));
	background.setShader("Data/grayscale.frag", sf::Shader::Fragment);
	background.load();

	GUIverticalalign verticalalign;
	verticalalign.setParent(&background);
	verticalalign.setRect(sf::FloatRect(0, 0, 100, 100));
	verticalalign.setAlign(GUIelement::ALIGN::CENTER, GUIelement::ALIGN::CENTER);
	verticalalign.load();

	GUIbutton options = loadButton("options");
	options.setParent(&verticalalign);
	options.setRect(sf::FloatRect(0, 0, 64, 24));
	options.setText(&roommanager->fonts["font"], "options");
	options.load();

	GUIbutton controls = loadButton("controls");
	controls.setParent(&verticalalign);
	controls.setRect(sf::FloatRect(0, 0, 64, 24));
	controls.setText(&roommanager->fonts["font"], "controls");
	controls.load();

	GUIbutton mainmenu = loadButton("mainmenu");
	mainmenu.setParent(&verticalalign);
	mainmenu.setRect(sf::FloatRect(0, 0, 64, 24));
	mainmenu.setText(&roommanager->fonts["font"], "main menu");
	mainmenu.load();

	GUIbutton back = loadButton("back");
	back.setParent(&verticalalign);
	back.setRect(sf::FloatRect(0, 0, 64, 24));
	back.setText(&roommanager->fonts["font"], "back");
	back.load();

	verticalalign.addElement(&options);
	verticalalign.addElement(&controls);
	verticalalign.addElement(&mainmenu);
	verticalalign.addElement(&back);
	verticalalign.alignElements();

	elements.push_back(new GUIpanel(background));
	elements.push_back(new GUIbutton(options));
	elements.push_back(new GUIbutton(controls));
	elements.push_back(new GUIbutton(mainmenu));
	elements.push_back(new GUIbutton(back));
}

void PauseMenu::start() {
	roommanager->playSong("menu");
	elements[0]->setTexture(&roommanager->textures["pausescreenshot"]);

	if (roommanager->getLastMenu() == "game") {
		sf::Vector2f viewsize = w->getView().getSize();
		sf::Vector2f actualviewsize = sf::Vector2f(w->getSize().x * w->getView().getViewport().width, w->getSize().y * w->getView().getViewport().height);
		sf::Vector2f actualcamerasize = (sf::Vector2f)w->getSize();
		sf::Vector2f camerasize = sf::Vector2f(viewsize.x * actualcamerasize.x / actualviewsize.x, viewsize.y * actualcamerasize.y / actualviewsize.y);
		sf::Vector2f offset = camerasize - viewsize;
		elements[0]->setRect(sf::FloatRect(-offset.x / 2, -offset.y / 2, in->getScreenSize().x + offset.x, in->getScreenSize().y + offset.y));
	}

	elements[0]->updateTexture(); 
}

void PauseMenu::update(float dt) {
	main_camera.setViewport(Room::in->getView().getViewport());
	Room::w->setView(main_camera);
	if (in->isKeyPressed(sf::Keyboard::Escape)) {
		roommanager->moveMenu("game");
	}
}

void PauseMenu::callback(std::string id, RESPONSE value) {
	if (id == "options") {
		roommanager->moveMenu("options");
	}
	else if (id == "controls") {
		roommanager->moveMenu("controls");
	}
	else if (id == "mainmenu") {
		roommanager->moveMenu("mainmenu");
	}
	else if (id == "back") {
		roommanager->moveMenu("game");
	}
}

GUIbutton PauseMenu::loadButton(std::string id) {
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