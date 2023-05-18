#include "ControlsMenu.h"
#include "../Framework/RoomManager.h"


ControlsMenu::ControlsMenu(sf::RenderWindow* window, InputHandler* input, RoomManager* rm) : Room("", window, input, rm), GUImanager(window, input, rm) {
	main_camera.setCenter(Room::in->getScreenSize() / 2.f);
	Room::w->setView(main_camera);

	std::vector<textureload> texturestoload;
	std::vector<fontload> fontstoload;

	texturestoload.push_back({ "guiboxwbg", "GUI/boxWithBackground.png" });
	texturestoload.push_back({ "guibutton", "GUI/button.png" });
	texturestoload.push_back({ "guibuttonhover", "GUI/buttonhover.png" });
	texturestoload.push_back({ "guibuttonpressed", "GUI/buttonpressed.png" });
	texturestoload.push_back({ "controls", "GUI/controls.png" });
	
	fontstoload.push_back({ "font", "TLOZ-Links-Awakening.ttf" });

	loadTextures(texturestoload);
	loadFonts(fontstoload);

	GUIbox background;
	background.setTexture(&roommanager->textures["guiboxwbg"]);
	background.setRect(sf::FloatRect(0, 0, in->getScreenSize().x, in->getScreenSize().y));
	background.setTileSize(16);
	background.load();

	GUIpanel controls;
	controls.setTexture(&roommanager->textures["controls"]);
	controls.setRect(sf::FloatRect(0, 0, in->getScreenSize().x, in->getScreenSize().y));
	controls.load();

	GUItext pause_label = loadLabel("pause", sf::Vector2f(13, 25));
	pause_label.setParent(&controls);
	pause_label.load();

	GUItext move_label = loadLabel("move", sf::Vector2f(43, 25));
	move_label.setParent(&controls);
	move_label.load();

	GUItext interact_label = loadLabel("interact", sf::Vector2f(38, 32.5f));
	interact_label.setParent(&controls);
	interact_label.load();

	GUItext debug_label = loadLabel("debug", sf::Vector2f(42, 40));
	debug_label.setParent(&controls);
	debug_label.load();

	GUItext shoot_label = loadLabel("shoot", sf::Vector2f(5, 40));
	shoot_label.setParent(&controls);
	shoot_label.load();

	GUItext dodge_label = loadLabel("dodge", sf::Vector2f(20.5, 40));
	dodge_label.setParent(&controls);
	dodge_label.load();

	GUIbutton back = loadButton("back");
	back.setParent(&background);
	back.setRect(sf::FloatRect(0, 0, 32, 20));
	back.setText(&roommanager->fonts["font"], "back");
	back.setAlign(GUIelement::ALIGN::RIGHT, GUIelement::ALIGN::BOTTOM);
	back.setOffset(sf::Vector2f(-5, -10));
	back.load();

	elements.push_back(new GUIbox(background));
	elements.push_back(new GUIpanel(controls));
	elements.push_back(new GUItext(pause_label));
	elements.push_back(new GUItext(move_label));
	elements.push_back(new GUItext(interact_label));
	elements.push_back(new GUItext(debug_label));
	elements.push_back(new GUItext(shoot_label));
	elements.push_back(new GUItext(dodge_label));
	elements.push_back(new GUIbutton(back));
}

void ControlsMenu::start() {
	roommanager->playSong("menu");
}

void ControlsMenu::update(float dt) {
	main_camera.setViewport(Room::in->getView().getViewport());
	Room::w->setView(main_camera);
}

void ControlsMenu::callback(std::string id, RESPONSE value) {
	if (id == "back") {
		roommanager->moveMenu(roommanager->getLastMenu());
	}
}

GUItext ControlsMenu::loadLabel(std::string text, sf::Vector2f position) {
	GUItext label;
	label.setFont(&roommanager->fonts["font"]);
	label.setText(text);
	label.setCharacterSize(8);
	label.setOffset(position);
	return label;
}

GUIbutton ControlsMenu::loadButton(std::string id) {
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