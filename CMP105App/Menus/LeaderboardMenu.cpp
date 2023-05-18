#include "LeaderboardMenu.h"
#include "../Framework/RoomManager.h"

LeaderboardMenu::LeaderboardMenu(sf::RenderWindow* window, InputHandler* input, RoomManager* rm) : Room("", window, input, rm), GUImanager(window, input, rm) {
	main_camera.setCenter(Room::in->getScreenSize() / 2.f);
	Room::w->setView(main_camera);

	std::vector<textureload> texturestoload;
	std::vector<fontload> fontstoload;

	texturestoload.push_back({ "guiboxwbg", "GUI/boxWithBackground.png" });
	texturestoload.push_back({ "ending", "GUI/ending.png" });
	fontstoload.push_back({ "boxfont", "zelda.ttf" });

	loadTextures(texturestoload);
	loadFonts(fontstoload);

	GUIpanel background;
	background.setTexture(&roommanager->textures["ending"]);
	background.setRect(sf::FloatRect(0, 0, in->getScreenSize().x, in->getScreenSize().y));
	background.load();

	GUIbox leaderboardbg;
	leaderboardbg.setParent(&background);
	leaderboardbg.setTexture(&roommanager->textures["guiboxwbg"]);
	leaderboardbg.setRect(sf::FloatRect(0, 17, 112, 96));
	leaderboardbg.setTileSize(16);
	leaderboardbg.setAlign(GUIelement::ALIGN::CENTER, GUIelement::ALIGN::NONE);
	leaderboardbg.load();
	leaderboardbg.alignElement();

	verticalalign = new GUIverticalalign();
	verticalalign->setParent(&background);
	verticalalign->setRect(sf::FloatRect(0, 0, 100, 90));
	verticalalign->setOffset(sf::Vector2f(0, 10));
	verticalalign->setAlign(GUIelement::ALIGN::CENTER, GUIelement::ALIGN::TOP);
	verticalalign->load();

	GUItext header;
	header.setParent(&background);
	header.setFont(&roommanager->fonts["boxfont"]);
	header.setCharacterSize(16);
	header.setText("Leaderboard");
	header.getText()->setOutlineColor(sf::Color::Black);
	header.getText()->setOutlineThickness(1.f);
	header.setAlign(GUIelement::ALIGN::CENTER, GUIelement::ALIGN::TOP);
	header.setOffset(sf::Vector2f(0, -4));
	header.load();

	for (size_t i = 0; i < 5; i++) {
		leaderboardpointers[i] = new GUItext();
		leaderboardpointers[i]->setParent(verticalalign);
		leaderboardpointers[i]->setFont(&roommanager->fonts["boxfont"]);
		leaderboardpointers[i]->setCharacterSize(16);
		leaderboardpointers[i]->setText("...");
		leaderboardpointers[i]->getText()->setFillColor(sf::Color::White);
		leaderboardpointers[i]->getText()->setOutlineColor(sf::Color::Black);
		leaderboardpointers[i]->setAlign(GUIelement::ALIGN::CENTER, GUIelement::ALIGN::TOP);
		leaderboardpointers[i]->load();
		verticalalign->addElement(leaderboardpointers[i]);
	}
	verticalalign->alignElements();
	verticalalign->setBackgroundColor(sf::Color::Red);
	verticalalign->load();

	GUIbutton menu = loadButton("menu");
	menu.setParent(&background);
	menu.setAlign(GUIelement::ALIGN::CENTER, GUIelement::ALIGN::BOTTOM);
	menu.setRect(sf::FloatRect(0, 0, 34, 20));
	menu.setText(&roommanager->fonts["font"], "exit");
	menu.setOffset(sf::Vector2f(0, -5));
	menu.load();

	elements.push_back(new GUIpanel(background));
	elements.push_back(new GUIbox(leaderboardbg));
	elements.push_back(new GUItext(header));
	for (size_t i = 0; i < 5; i++) {
		elements.push_back(leaderboardpointers[i]);
	}
	elements.push_back(new GUIbutton(menu));
}

void LeaderboardMenu::start() {
	roommanager->playSong("menu");

	std::vector<Leaderboard::result> result = roommanager->httpleaderboard.getLeadeboard();

	for (size_t i = 0; i < result.size(); i++) {
		GUItext* lp = leaderboardpointers[i];
		if (result[i].name == roommanager->getUsername()) lp->getText()->setOutlineThickness(1.f);
		else lp->getText()->setOutlineThickness(0.f);

		if (result[i].cheated) lp->getText()->setFillColor(sf::Color::Red);
		else lp->getText()->setFillColor(sf::Color::White);

		lp->setText(result[i].name + " " + result[i].score);
		lp->load();
	}
	verticalalign->alignElements();
}

void LeaderboardMenu::update(float dt) {
	main_camera.setViewport(Room::in->getView().getViewport());
	Room::w->setView(main_camera);
}

void LeaderboardMenu::callback(std::string id, RESPONSE value) {
	if (id == "menu") {
		roommanager->moveMenu("mainmenu");
	}
}

GUIbutton LeaderboardMenu::loadButton(std::string id) {
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