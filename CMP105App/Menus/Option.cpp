#include "Option.h"
#include "../Framework/RoomManager.h"

OptionMenu::OptionMenu(sf::RenderWindow* window, InputHandler* input, RoomManager* rm) : Room("MainScreen", window, input, rm), GUImanager(window, input, rm) {
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
	texturestoload.push_back({ "slider", "GUI/slider.png" });

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
	// fullscreen checkbox //
	// ################### //

	GUIhorizontalalign fullscreenhoralign;
	fullscreenhoralign.setParent(&verticalalign);
	fullscreenhoralign.setRect(sf::FloatRect(0, 0, 100, 10));
	fullscreenhoralign.load();

	GUItext fullscreenlabel;
	fullscreenlabel.setParent(&fullscreenhoralign);
	fullscreenlabel.setFont(&roommanager->fonts["font"]);
	fullscreenlabel.setText("Set fullscreen");
	fullscreenlabel.setCharacterSize(8);
	fullscreenlabel.setOffset(sf::Vector2f(0, -0.5));
	fullscreenlabel.load();
	
	GUIcheckbox fullscreen;
	fullscreen.setParent(&fullscreenhoralign);
	fullscreen.setId("fullscreen");
	fullscreen.setCheckedTexture(&roommanager->textures["checkboxyes"], &roommanager->textures["checkboxyeshover"]);
	fullscreen.setUncheckedTexture(&roommanager->textures["checkboxno"], &roommanager->textures["checkboxnohover"]);
	fullscreen.setPosition(sf::Vector2f(0, 0));
	fullscreen.setCallback(this);
	fullscreen.load();

	fullscreenhoralign.addElement(&fullscreenlabel);
	fullscreenhoralign.addElement(&fullscreen);
	fullscreenhoralign.alignElements();

	// ############### //
	// volume checkbox //
	// ############### //

	GUIhorizontalalign mutehoralign;
	mutehoralign.setParent(&verticalalign);
	mutehoralign.setRect(sf::FloatRect(0, 0, 80, 10));
	mutehoralign.load();

	GUItext mutelabel;
	mutelabel.setParent(&mutehoralign);
	mutelabel.setFont(&roommanager->fonts["font"]);
	mutelabel.setText("Mute volume");
	mutelabel.setCharacterSize(8);
	mutelabel.setOffset(sf::Vector2f(0, -0.5));
	mutelabel.load();

	GUIcheckbox mute;
	mute.setParent(&mutehoralign);
	mute.setId("mute");
	mute.setCheckedTexture(&roommanager->textures["checkboxyes"], &roommanager->textures["checkboxyeshover"]);
	mute.setUncheckedTexture(&roommanager->textures["checkboxno"], &roommanager->textures["checkboxnohover"]);
	mute.setPosition(sf::Vector2f(0, 0));
	mute.setCallback(this);
	mute.load();

	mutehoralign.addElement(&mutelabel);
	mutehoralign.addElement(&mute);
	mutehoralign.alignElements();

	// ############ //
	// volume slider//
	// ############ //

	GUIhorizontalalign volumehoralign;
	volumehoralign.setParent(&verticalalign);
	volumehoralign.setRect(sf::FloatRect(0, 0, 120, 10));
	volumehoralign.load();

	GUItext volumelabel;
	volumelabel.setParent(&volumehoralign);
	volumelabel.setFont(&roommanager->fonts["font"]);
	volumelabel.setText("Volume");
	volumelabel.setCharacterSize(8);
	volumelabel.setOffset(sf::Vector2f(0, -0.5));
	volumelabel.load();

	GUIslider volume;
	volume.setId("volume");
	volume.setParent(&volumehoralign);
	volume.setMinMaxValue(0, 100);
	volume.setTexture(&roommanager->textures["slider"]);
	volume.setRect(sf::FloatRect(0, 0, 50, 8));
	volume.setInput(in);
	volume.setValue(100.f);
	volume.setCallback(this);
	volume.load();

	volumehoralign.addElement(&volumelabel);
	volumehoralign.addElement(&volume);
	volumehoralign.alignElements();

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

	verticalalign.addElement(&fullscreenhoralign);
	verticalalign.addElement(&mutehoralign);
	verticalalign.addElement(&volumehoralign);
	verticalalign.addElement(&backbutton);
	verticalalign.alignElements();

	//////////////////////////////////////////

	elements.push_back(new GUIbox(background));

	elements.push_back(new GUItext(fullscreenlabel));
	elements.push_back(new GUIcheckbox(fullscreen));

	elements.push_back(new GUItext(mutelabel));
	elements.push_back(new GUIcheckbox(mute));

	elements.push_back(new GUItext(volumelabel));
	elements.push_back(new GUIslider(volume));
	volumepointer = (GUIslider*)elements.back();

	elements.push_back(new GUIbutton(backbutton));

	//////////////////////////////////////////
}

void OptionMenu::start() {
	roommanager->playSong("menu");
	volumepointer->setValue(roommanager->getCurrentSong()->getVolume());
}

void OptionMenu::update(float dt) {
	main_camera.setViewport(Room::in->getView().getViewport());
	Room::w->setView(main_camera);
}

void OptionMenu::callback(std::string id, RESPONSE value) {
	if (id == "fullscreen") {
		if (value.b) {
			w->create(sf::VideoMode::getFullscreenModes()[0], "Game Project", sf::Style::Fullscreen);
			in->resizeView(w->getSize());
			w->setView(in->getView());
			in->isfullscreen = true;
		}
		else {
			w->create(sf::VideoMode(in->getScreenSize().x * 5, in->getScreenSize().y * 5), "Game Project");
			in->resizeView(w->getSize());
			w->setView(in->getView());
			in->isfullscreen = false;
		}

		w->setMouseCursorVisible(false);
	}

	if (id == "mute") {
		if (value.b == true) {
			roommanager->getCurrentSong()->pause();
			roommanager->ismusicplaying = false;
		}
		else {
			roommanager->getCurrentSong()->play();
			roommanager->ismusicplaying = true;
		}
	}

	if (id == "volume") {
		roommanager->setVolume(value.f);
	}

	if (id == "back") {
		roommanager->moveMenu(roommanager->getLastMenu());
	}
}