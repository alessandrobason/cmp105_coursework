#include "MainMenu.h"
#include "../Framework/RoomManager.h"

MainMenu::MainMenu(sf::RenderWindow* window, InputHandler* input, RoomManager* rm) : Room("MainScreen", window, input, rm), GUImanager(window, input, rm) {
	main_camera.setCenter(Room::in->getScreenSize() / 2.f);
	Room::w->setView(main_camera);

	std::vector<textureload> texturestoload;
	std::vector<fontload> fontstoload;

	texturestoload.push_back({ "background", "GUI/mainmenu.png" });
	texturestoload.push_back({ "guibutton", "GUI/button.png" });
	texturestoload.push_back({ "guibuttonhover", "GUI/buttonhover.png" });
	texturestoload.push_back({ "guibuttonpressed", "GUI/buttonpressed.png" });
	fontstoload.push_back({ "font", "TLOZ-Links-Awakening.ttf" });

	loadTextures(texturestoload);
	loadFonts(fontstoload);

	GUIpanel backgroundpanel;
	backgroundpanel.setRect(sf::FloatRect(0, 0, in->getScreenSize().x, in->getScreenSize().y));
	backgroundpanel.setTexture(&roommanager->textures["background"]);
	backgroundpanel.load();

	GUIverticalalign verticalalign;
	verticalalign.setParent(&backgroundpanel);
	verticalalign.setRect(sf::FloatRect(20, 10, 50, 120));
	verticalalign.setAlign(GUIelement::ALIGN::NONE, GUIelement::ALIGN::CENTER);
	verticalalign.setBackgroundColor(sf::Color(255, 0, 0, 100));
	verticalalign.load();

	GUIbutton startgame = loadButton("start");
	startgame.setParent(&verticalalign);
	startgame.setRect(sf::FloatRect(0, 0, 72, 24));
	startgame.setText(&roommanager->fonts["font"], "start");
	startgame.load();

	GUIbutton options = loadButton("options");
	options.setParent(&verticalalign);
	options.setRect(sf::FloatRect(0, 0, 72, 24));
	options.setText(&roommanager->fonts["font"], "options");
	options.load();

	GUIbutton controls = loadButton("controls");
	controls.setParent(&verticalalign);
	controls.setRect(sf::FloatRect(0, 0, 72, 24));
	controls.setText(&roommanager->fonts["font"], "controls");
	controls.load();

	GUIbutton leaderboard = loadButton("leaderboard");
	leaderboard.setParent(&verticalalign);
	leaderboard.setRect(sf::FloatRect(0, 0, 72, 24));
	leaderboard.setText(&roommanager->fonts["font"], "leaderboard");
	leaderboard.load();

	GUIbutton exit = loadButton("exit");
	exit.setParent(&verticalalign);
	exit.setRect(sf::FloatRect(0, 0, 72, 24));
	exit.setText(&roommanager->fonts["font"], "exit");
	exit.load();

	verticalalign.addElement(&startgame);
	verticalalign.addElement(&options);
	verticalalign.addElement(&controls);
	verticalalign.addElement(&leaderboard);
	verticalalign.addElement(&exit);
	verticalalign.alignElements();

	elements.push_back(new GUIpanel(backgroundpanel));
	//elements.push_back(new GUIverticalalign(verticalalign));
	elements.push_back(new GUIbutton(startgame));
	elements.push_back(new GUIbutton(options));
	elements.push_back(new GUIbutton(controls));
	elements.push_back(new GUIbutton(leaderboard));
	elements.push_back(new GUIbutton(exit));
}

void MainMenu::start() {
	roommanager->playSong("menu");
}

void MainMenu::update(float dt) {
	main_camera.setViewport(Room::in->getView().getViewport());
	Room::w->setView(main_camera);
}

void MainMenu::callback(std::string id, RESPONSE value) {
	if (id == "start") {
		roommanager->moveMenu("game");
	}
	else if (id == "options") {
		roommanager->moveMenu("options");
	}
	else if (id == "controls") {
		roommanager->moveMenu("controls");
	}
	else if (id == "leaderboard") {
		roommanager->moveMenu("leaderboard");
	}
	else if (id == "exit") {
		roommanager->moveMenu("exit");
	}
}

GUIbutton MainMenu::loadButton(std::string id) {
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