#pragma once

class Room;

struct MapData {
	bool loaded = false;
	std::vector<int> layers;
	Tilemap::tilemap_data tilemap_data;
	Tilemap tilemap;
	sf::Shader shader;
};