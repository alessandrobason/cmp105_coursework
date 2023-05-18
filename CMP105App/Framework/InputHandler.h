#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class InputHandler
{
public:
	InputHandler(sf::RenderWindow* win) { w = win; }

	void setKeyDown(int key) { if(key == -1) return; keys[key] = true; };
	void setKeyUp(int key) { if (key == -1) return; keys[key] = false; pressed_keys[key] = false; };
	bool isKeyDown(int key) { if (key == -1) return false; return keys[key]; };
	bool isKeyPressed(int key) {
		if (key == -1) return false;
		if (keys[key] && !pressed_keys[key]) {
			pressed_keys[key] = true;
			return true;
		}
		return false;
	}

	void setMouseX(int lx) { mouse.position.x = lx; };
	void setMouseY(int ly) { mouse.position.y = ly; };
	void setMousePosition(sf::Vector2i pos) { mouse.position = pos; };
	int getMouseX() { return mouse.position.x; };
	int getMouseY() { return mouse.position.y; };
	sf::Vector2i getMousePosition() { return mouse.position; };
	sf::Vector2f getMouseRelative() { return w->mapPixelToCoords(sf::Mouse::getPosition(*w)); }
	void setMouseLDown() { mouse.left = true; };
	void setMouseRDown() { mouse.right = true; };
	void setMouseLUp() { mouse.left = false;  mouse.pressedleft = false; };
	void setMouseRUp() { mouse.right = false; mouse.pressedright = false; };
	bool isMouseLDown() { return mouse.left; };
	bool isMouseRDown() { return mouse.right; };
	bool isMouseLPressed() {
		if (mouse.left && !mouse.pressedleft) {
			mouse.pressedleft = true;
			return true;
		}
		return false;
	}
	bool isMouseRPressed() {
		if (mouse.right && !mouse.pressedright) {
			mouse.pressedright = true;
			return true;
		}
		return false;
	}


	void resizeView(sf::Vector2u windowsize) {
		sf::FloatRect viewport(0.f, 0.f, 1.f, 1.f);

		float screenwidth = static_cast<float>(windowsize.x) / screensize.x;
		float screenheight = static_cast<float>(windowsize.y) / screensize.y;

		if (screenwidth > screenheight) {
			viewport.width = screenheight / screenwidth;
			viewport.left = (1.f - viewport.width) / 2.f;
		}
		else if (screenwidth < screenheight) {
			viewport.height = screenwidth / screenheight;
			viewport.top = (1.f - viewport.height) / 2.f;
		}

		sf::View view(sf::FloatRect(0, 0, static_cast<float>(screensize.x), static_cast<float>(screensize.y)));
		view.setViewport(viewport);
		windowview = view;
	}

	sf::View getView() { return windowview; }
	void setScreenSize(sf::Vector2f s) { const_cast<sf::Vector2f&>(screensize) = s; windowview.setSize(s); }
	const sf::Vector2f getScreenSize() { return screensize; }

	enum KEY_ENUM {
		KEY_UP = sf::Keyboard::W,
		KEY_LEFT = sf::Keyboard::A,
		KEY_RIGHT = sf::Keyboard::D,
		KEY_DOWN = sf::Keyboard::S,
		KEY_INTERACT = sf::Keyboard::E,
		KEY_DEBUG = sf::Keyboard::F1
	};

	bool isfullscreen = false;

private:
	sf::RenderWindow* w = nullptr;
	// gameboy screen size
	const sf::Vector2f screensize = sf::Vector2f(0, 0);

	struct Mouse {
		sf::Vector2i position;
		bool left = false;
		bool right = false;
		bool pressedleft = false;
		bool pressedright = false;
	};

	bool keys[sf::Keyboard::KeyCount]{ false };
	bool pressed_keys[sf::Keyboard::KeyCount]{ false };
	Mouse mouse;

	sf::View windowview = sf::View(sf::FloatRect(0, 0, screensize.x, screensize.y));
};

