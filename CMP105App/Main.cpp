#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Framework/RoomManager.h"

float min(float a, float b) { return (a < b ? a : b); }
float max(float a, float b) { return (a > b ? a : b); }
bool pressed = false;

void windowProcess(sf::RenderWindow* window, InputHandler *in) {
	sf::Event event;
	while (window->pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::Resized:
			in->resizeView(sf::Vector2u(event.size.width, event.size.height));
			break;
		case sf::Event::KeyPressed:
			in->setKeyDown(event.key.code);
			break;
		case sf::Event::KeyReleased:
			in->setKeyUp(event.key.code);
			break;
		case sf::Event::MouseMoved:
			in->setMousePosition(sf::Mouse::getPosition());
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
				in->setMouseLDown();
			if (event.mouseButton.button == sf::Mouse::Right)
				in->setMouseRDown();
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left)
				in->setMouseLUp();
			if (event.mouseButton.button == sf::Mouse::Right)
				in->setMouseRUp();
			break;
		default:
			break;
		}
	}
}

int main() {
	srand(time(NULL));

	const sf::Vector2f screensize = sf::Vector2f(160, 144);
	sf::RenderWindow window(sf::VideoMode(screensize.x*5, screensize.y*5), "Game Project");
	InputHandler *in = new InputHandler(&window);
	in->setScreenSize(screensize);

	RoomManager roommanager;

	sf::Clock deltaClock;

	roommanager.setData(&window, in);
	// Game Loop
	while (window.isOpen()) {
		// Handle window events.
		windowProcess(&window, in);

		float dt = deltaClock.restart().asSeconds();
		roommanager.handleInput(dt);
		roommanager.update(dt);
		roommanager.draw();
	}
}

