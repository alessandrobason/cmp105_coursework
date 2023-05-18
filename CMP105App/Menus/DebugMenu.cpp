#include "DebugMenu.h"
#include "../Framework/RoomManager.h"


DebugMenu::DebugMenu(sf::RenderWindow* window, InputHandler* input, RoomManager* rm) : Room("", window, input, rm), GUImanager(window, input, rm) {
	main_camera.setCenter(Room::in->getScreenSize() / 2.f);
	Room::w->setView(main_camera);

	std::vector<textureload> texturestoload;
	std::vector<fontload> fontstoload;

	texturestoload.push_back({ "guiboxwbg", "GUI/boxWithBackground.png" });
	texturestoload.push_back({ "checkboxno", "GUI/checkbox_no.png" });
	texturestoload.push_back({ "checkboxnohover", "GUI/checkbox_no_hover.png" });
	texturestoload.push_back({ "checkboxyes", "GUI/checkbox_yes.png" });
	texturestoload.push_back({ "checkboxyeshover", "GUI/checkbox_yes_hover.png" });
	texturestoload.push_back({ "guibutton", "GUI/button.png" });
	texturestoload.push_back({ "guibuttonhover", "GUI/buttonhover.png" });
	texturestoload.push_back({ "guibuttonpressed", "GUI/buttonpressed.png" });

	fontstoload.push_back({ "font", "TLOZ-Links-Awakening.ttf" });

	loadTextures(texturestoload);
	loadFonts(fontstoload);

	GUIbox background;
	background.setTexture(&roommanager->textures["guiboxwbg"]);
	background.setRect(sf::FloatRect(0, 0, in->getScreenSize().x, in->getScreenSize().y));
	background.setTileSize(16);
	background.load();

	GUIverticalalign verticalalign;
	verticalalign.setParent(&background);
	verticalalign.setRect(sf::FloatRect(0, 0, 100, 100));
	verticalalign.setAlign(GUIelement::ALIGN::CENTER, GUIelement::ALIGN::CENTER);
	verticalalign.load();

	// ################### //
	// show debug checkbox //
	// ################### //

	GUIhorizontalalign showdebughoralign;
	showdebughoralign.setParent(&verticalalign);
	showdebughoralign.setRect(sf::FloatRect(0, 0, 100, 10));
	showdebughoralign.load();

	GUItext showdebuglabel;
	showdebuglabel.setParent(&showdebughoralign);
	showdebuglabel.setFont(&roommanager->fonts["font"]);
	showdebuglabel.setText("Show debug");
	showdebuglabel.setCharacterSize(8);
	showdebuglabel.setOffset(sf::Vector2f(0, -0.5));
	showdebuglabel.load();

	GUIcheckbox showdebug = loadCheckBox("showdebug");
	showdebug.setParent(&showdebughoralign);
	showdebug.load();

	showdebughoralign.addElement(&showdebuglabel);
	showdebughoralign.addElement(&showdebug);
	showdebughoralign.alignElements();


	// ################ //
	// godmode checkbox //
	// ################ //


	GUIhorizontalalign godmodehoralign;
	godmodehoralign.setParent(&verticalalign);
	godmodehoralign.setRect(sf::FloatRect(0, 0, 100, 10));
	godmodehoralign.load();

	GUItext godmodelabel;
	godmodelabel.setParent(&godmodehoralign);
	godmodelabel.setFont(&roommanager->fonts["font"]);
	godmodelabel.setText("Godmode");
	godmodelabel.setCharacterSize(8);
	godmodelabel.setOffset(sf::Vector2f(0, -0.5));
	godmodelabel.load();

	GUIcheckbox godmode = loadCheckBox("godmode");
	godmode.setParent(&godmodehoralign);
	godmode.load();

	godmodehoralign.addElement(&godmodelabel);
	godmodehoralign.addElement(&godmode);
	godmodehoralign.alignElements();

	// ########################### //
	// walk through walls checkbox //
	// ########################### //


	GUIhorizontalalign wallshoralign;
	wallshoralign.setParent(&verticalalign);
	wallshoralign.setRect(sf::FloatRect(0, 0, 100, 10));
	wallshoralign.load();

	GUItext wallslabel;
	wallslabel.setParent(&wallshoralign);
	wallslabel.setFont(&roommanager->fonts["font"]);
	wallslabel.setText("Walk through walls ");
	wallslabel.setCharacterSize(8);
	wallslabel.setOffset(sf::Vector2f(0, -0.5));
	wallslabel.load();

	GUIcheckbox walls = loadCheckBox("walls");
	walls.setParent(&wallshoralign);
	walls.load();

	wallshoralign.addElement(&wallslabel);
	wallshoralign.addElement(&walls);
	wallshoralign.alignElements();

	// ########### //
	// back button //
	// ########### //

	GUIbutton getpuzzlepieces;
	getpuzzlepieces.setId("puzzle");
	getpuzzlepieces.setParent(&verticalalign);
	getpuzzlepieces.setTexture(&roommanager->textures["guibutton"]);
	getpuzzlepieces.setRect(sf::FloatRect(0, 0, 110, 24));
	getpuzzlepieces.setText(&roommanager->fonts["font"], "get all puzzle pieces");
	getpuzzlepieces.setNormalTexture(&roommanager->textures["guibutton"]);
	getpuzzlepieces.setHoverTexture(&roommanager->textures["guibuttonhover"]);
	getpuzzlepieces.setPressedTexture(&roommanager->textures["guibuttonpressed"]);
	getpuzzlepieces.setTileSize(8);
	getpuzzlepieces.setCallback(this);
	getpuzzlepieces.load();

	// ########### //
	// back button //
	// ########### //

	GUIbutton backbutton;
	backbutton.setId("back");
	backbutton.setParent(&verticalalign);
	backbutton.setTexture(&roommanager->textures["guibutton"]);
	backbutton.setRect(sf::FloatRect(0, 0, 64, 24));
	backbutton.setText(&roommanager->fonts["font"], "go back");
	backbutton.setNormalTexture(&roommanager->textures["guibutton"]);
	backbutton.setHoverTexture(&roommanager->textures["guibuttonhover"]);
	backbutton.setPressedTexture(&roommanager->textures["guibuttonpressed"]);
	backbutton.setTileSize(8);
	backbutton.setCallback(this);
	backbutton.load();

	// ########################### //
	// align everything vertically //
	// ########################### //

	verticalalign.addElement(&showdebughoralign);
	verticalalign.addElement(&godmodehoralign);
	verticalalign.addElement(&wallshoralign);
	verticalalign.addElement(&getpuzzlepieces);
	verticalalign.addElement(&backbutton);
	verticalalign.alignElements();

	///////////////////////////////////////////////

	elements.push_back(new GUIbox(background));

	elements.push_back(new GUItext(showdebuglabel));
	elements.push_back(new GUIcheckbox(showdebug));

	elements.push_back(new GUItext(godmodelabel));
	elements.push_back(new GUIcheckbox(godmode));

	elements.push_back(new GUItext(wallslabel));
	elements.push_back(new GUIcheckbox(walls));

	elements.push_back(new GUIbutton(getpuzzlepieces));

	elements.push_back(new GUIbutton(backbutton));
}

void DebugMenu::start() {
	roommanager->playSong("menu");
}

void DebugMenu::update(float dt) {
	main_camera.setViewport(Room::in->getView().getViewport());
	Room::w->setView(main_camera);
}

void DebugMenu::callback(std::string id, RESPONSE value) {
	if (id == "showdebug") {
		roommanager->setDebug(value.b);
	}
	if (id == "godmode") {
		roommanager->getPlayer()->setCheat(Player::CHEATS::GODMODE, value.b);
	}
	if (id == "walls") {
		roommanager->getPlayer()->setCheat(Player::CHEATS::WALKTHROUGHWALLS, value.b);
	}
	if (id == "puzzle") {
		roommanager->getPlayer()->setCheat(Player::CHEATS::FOUNDALLPIECES, true);
		while (!roommanager->foundAllPieces()) {
			roommanager->findPiece();
		}
	}
	if (id == "back") {
		roommanager->moveMenu(roommanager->getLastMenu());
	}
}

GUIcheckbox DebugMenu::loadCheckBox(std::string id) {
	GUIcheckbox checkbox;
	checkbox.setId(id);
	checkbox.setCheckedTexture(&roommanager->textures["checkboxyes"], &roommanager->textures["checkboxyeshover"]);
	checkbox.setUncheckedTexture(&roommanager->textures["checkboxno"], &roommanager->textures["checkboxnohover"]);
	checkbox.setPosition(sf::Vector2f(0, 0));
	checkbox.setCallback(this);
	return checkbox;
}