#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Collision.h"
#include "Animation.h"

class Tilemap {
public:
	struct tilemap_data {
		int numb_layers;
		sf::Vector2u tileSize;
		int w;
		int h;
	};

	struct animated_tiles_data {
		std::string name;
		struct data {
			int duration;
			int tileid;
		};
		std::vector<data> frames;
	};

	void setWindow(sf::RenderWindow* w);

	void setTexture(sf::Texture* t);
	sf::Texture* getTexture() { return m_tileset; }

	bool load(bool* d, sf::Image* t, std::vector <animated_tiles_data> animData, std::vector<int>& tiles, tilemap_data tilemapdata, sf::Vector2f offset);
	bool loadCollisions(std::vector<Collision> collisions);

	void draw();
	void animate(float dt);
	void drawDebug();
	void setShader(sf::Shader s);

	tilemap_data getData() { return data; }
	sf::RenderStates getStates() { return states; }
	sf::Vector2f getPosition() { return sf::Vector2f(states.transform.getMatrix()[12], states.transform.getMatrix()[1]); }

	void setStates(sf::RenderStates s) { states = s; }

	void resetAnimation() { animatedTiles.reset(); }

	std::vector<Collision> collisions;
	//std::vector<sf::RectangleShape> collisionShapes;

	~Tilemap() {
		m_tileset = nullptr;
		window = nullptr;
	}

private:
	//sf::VertexArray vertexs;
	std::vector<sf::Vertex> vertexs;
	AnimatedTile animatedTiles;
	sf::Texture* m_tileset;

	sf::RenderWindow* window;
	sf::RenderStates states;

	tilemap_data data;

	bool* isdebug = nullptr;
};

