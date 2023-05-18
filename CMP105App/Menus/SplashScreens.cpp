#include "SplashScreens.h"
#include "../Framework/RoomManager.h"

SplashScreens::SplashScreens(sf::RenderWindow* window, InputHandler* input, RoomManager* rm) : Room("MainScreen", window, input, rm), GUImanager(window, input, rm) {
	main_camera.setCenter(Room::in->getScreenSize() / 2.f);
	Room::w->setView(main_camera);

	std::vector<textureload> texturestoload;
	std::vector<fontload> fontstoload;

	texturestoload.push_back({ "splashscreen", "GUI/splashscreen.png" });
	loadTextures(texturestoload);
	loadFonts(fontstoload);

	GUIpanel mainpanel;
	mainpanel.setRect(sf::FloatRect(0, 0, Room::in->getScreenSize().x, Room::in->getScreenSize().y));
	mainpanel.setBackgroundColor(sf::Color::Black);
	mainpanel.load();

	GUIsplashscreen splashscreen;
	splashscreen.setParent(&mainpanel);
	splashscreen.setTexture(&Room::roommanager->textures["splashscreen"]);
	splashscreen.setRect(sf::FloatRect(0, 0, 64, 64));
	splashscreen.setAlign(GUIelement::ALIGN::CENTER, GUIelement::ALIGN::CENTER);
	splashscreen.load();

	elements.push_back(new GUIpanel(mainpanel));
	elements.push_back(new GUIsplashscreen(splashscreen));
}

void SplashScreens::update(float dt) {
	main_camera.setViewport(Room::in->getView().getViewport());
	Room::w->setView(main_camera);
	for (size_t i = 0; i < elements.size(); i++) {
		elements[i]->update(dt);
		if (elements[i]->isdead()) {
			Room::roommanager->moveMenu("startscreen");
		}
	}
}