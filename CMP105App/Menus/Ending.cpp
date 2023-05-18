#include "Ending.h"
#include "../Framework/RoomManager.h"

Ending::Ending(sf::RenderWindow* window, InputHandler* input, RoomManager* rm) : Room("", window, input, rm), GUImanager(window, input, rm) {
	main_camera.setCenter(Room::in->getScreenSize() / 2.f);
	Room::w->setView(main_camera);

	finalcredits = {
		"A game by",
		"Alessandro Bason",
		"Music by",
		"                         Bill Evans\nSomeday My Prince Will Come",
		"        Art Blakey\nSolo de batterie",
		"Art assets from",
		"The Legend of Zelda\nLink s Awakening dx",
		"Pokemon crystal",
		"Special thanks to",
		"Valeria Chiarini",
		"The End"
	};

	std::vector<textureload> texturestoload;
	std::vector<fontload> fontstoload;

	texturestoload.push_back({ "ending", "GUI/ending.png" });
	fontstoload.push_back({ "font", "TLOZ-Links-Awakening.ttf" });

	loadTextures(texturestoload);
	loadFonts(fontstoload);

	GUIpanel background;
	background.setTexture(&roommanager->textures["ending"]);
	background.setRect(sf::FloatRect(0, 0, in->getScreenSize().x, in->getScreenSize().y));
	background.load();

	backgroundpointer = new GUIpanel(background);

	GUIbutton leaderboard = loadButton("leaderboard");
	leaderboard.setParent(backgroundpointer);
	leaderboard.setAlign(GUIelement::ALIGN::CENTER, GUIelement::ALIGN::BOTTOM);
	leaderboard.setRect(sf::FloatRect(0, 0, 72, 24));
	leaderboard.setText(&roommanager->fonts["font"], "leaderboard");
	leaderboard.setOffset(sf::Vector2f(0, -5));
	leaderboard.load();

	GUItext credits;
	credits.setFont(&roommanager->fonts["font"]);
	credits.setText(finalcredits[0]);
	credits.setCharacterSize(8);
	credits.setParent(backgroundpointer);
	credits.setAlign(GUIelement::ALIGN::CENTER, GUIelement::ALIGN::CENTER);
	credits.getText()->setFillColor(textcolor);
	credits.getText()->setOutlineColor(sf::Color(0, 0, 0, 0));
	credits.getText()->setOutlineThickness(1.f);
	credits.getText()->setLineSpacing(2.f);
	credits.load();

	creditspointer = new GUItext(credits);

	elements.push_back(new GUIpanel(background));
	elements.push_back(new GUIbutton(leaderboard));
	elements.push_back(creditspointer);

	fade = Tweening<float>(0, 255, 1.f);
}

void Ending::resetRoom() {
	textcolor.a = 0;
	fade = Tweening<float>(0, 255, 1.f);
	fadingout = false;
	positionincredits = 0;
	timeleft = fadetime;
	creditspointer->getText()->setFillColor(textcolor);
	creditspointer->getText()->setOutlineColor(sf::Color(0, 0, 0, textcolor.a));
	creditspointer->setText(finalcredits[positionincredits]);
	roommanager->getSong("ending")->setPlayingOffset(sf::Time::Zero);
}

void Ending::start() {
	roommanager->playSong("ending");
	roommanager->restartGame();

	// convert the time taken by the player (in seconds) to h/m/s
	int hours = 0, minutes = 0, seconds = 0;
	seconds = ((int)roommanager->scoreclock) % 60;
	minutes = roommanager->scoreclock / 60;
	hours = minutes / 60;
	if (minutes >= 60) minutes = minutes % 60;
	std::string finaltime = "";
	if (hours != 0) finaltime = std::to_string(hours);
	if (minutes < 10) finaltime += "0" + std::to_string(minutes);
	else finaltime += std::to_string(minutes);
	if (seconds < 10) finaltime += "0" + std::to_string(seconds);
	else finaltime += std::to_string(seconds);

	//send the score to the leaderboard
	roommanager->httpleaderboard.sendScore(roommanager->getUsername(), finaltime, roommanager->getPlayer()->hasCheated());

	Event::EventInput fade;
	fade.time = 2.f;
	fade.fadeout = false;
	fade.fadesong = true;
	roommanager->eventmanager.addEvent(EventManager::EventType::FADE, fade);
}

void Ending::update(float dt) {
	main_camera.setViewport(Room::in->getView().getViewport());
	Room::w->setView(main_camera);
	roommanager->eventmanager.update(dt);
	if (roommanager->eventmanager.getNumberOfEvents() == 0 && positionincredits != -1) {
		if (fade.isfinished()) {
			timeleft -= dt;
			if (timeleft <= 0) {
				timeleft = fadetime;
				fadingout = !fadingout;
				if (fadingout) {
					fade = Tweening<float>(255, 0, 1.f);
				}
				else {
					fade = Tweening<float>(0, 255, 1.f);
					positionincredits++;
					if (positionincredits >= finalcredits.size()) {
						positionincredits = -1;
						return;
					}
					creditspointer->setText(finalcredits[positionincredits]);
					creditspointer->load();
				}
			}
		}
		else {
			fade.update(dt);
			textcolor.a = fade.getValue();
			creditspointer->getText()->setFillColor(textcolor);
			creditspointer->getText()->setOutlineColor(sf::Color(0, 0, 0, textcolor.a));
		}
	}
	else if (positionincredits == -1) {
		roommanager->moveMenu("leaderboard");
	}
}

void Ending::draw() {
	GUImanager::draw();
	roommanager->eventmanager.draw(w);
}

void Ending::callback(std::string id, RESPONSE value) {
	if (id == "leaderboard") {
		roommanager->moveMenu("leaderboard");
	}
}

GUIbutton Ending::loadButton(std::string id) {
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