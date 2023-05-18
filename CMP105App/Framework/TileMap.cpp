#include "Tilemap.h"

bool Tilemap::load(bool* d, sf::Image* t, std::vector <animated_tiles_data> animData, std::vector<int>& tiles, tilemap_data tilemapdata, sf::Vector2f offset) {
	isdebug = d;

	sf::Transform positionoffset;
	positionoffset.translate(offset);
	states.transform = positionoffset;
	
	data = tilemapdata;
	
	// set the size of the vertex array to be enough for the whole tilemap
	const int layer_dimension = (int) tiles.size() / tilemapdata.numb_layers;
	
	/*
	modified version of the official sfml tutorial for vertex arrays
	*/

	for (size_t nl = 0; nl < tilemapdata.numb_layers; nl++) {
		for (size_t y = 0; y < tilemapdata.h; y++) {
			for (size_t x = 0; x < tilemapdata.w; x++) {
				int position = (nl * layer_dimension) + (y * tilemapdata.w) + (x);
				
				// get tile
				int tileNumber = tiles[position];

				// if tile is empty
				if (tileNumber == -1) continue;

				bool isAnimated = false;
				int positionInAnimData = -1;
				
				std::string tileStr = std::to_string(tileNumber);
				for (size_t i = 0; i < animData.size(); i++) {
					if (animData[i].name == tileStr) {
						isAnimated = true;
						positionInAnimData = i;
						break;
					}
				}
				

				// get position in texture
				int tu = tileNumber % (t->getSize().x / tilemapdata.tileSize.x);
				int tv = tileNumber / (t->getSize().x / tilemapdata.tileSize.x);


				if (isAnimated) {
					sf::Vertex quad[4];

					// set position of 4 vertices (cw order)
					quad[0].position = sf::Vector2f(x * tilemapdata.tileSize.x, y * tilemapdata.tileSize.y);
					quad[1].position = sf::Vector2f((x + 1) * tilemapdata.tileSize.x, y * tilemapdata.tileSize.y);
					quad[2].position = sf::Vector2f((x + 1) * tilemapdata.tileSize.x, (y + 1) * tilemapdata.tileSize.y);
					quad[3].position = sf::Vector2f(x * tilemapdata.tileSize.x, (y + 1) * tilemapdata.tileSize.y);
					// set texture coords (cw order)
					quad[0].texCoords = sf::Vector2f(tu * tilemapdata.tileSize.x, tv * tilemapdata.tileSize.y);
					quad[1].texCoords = sf::Vector2f((tu + 1) * tilemapdata.tileSize.x, tv * tilemapdata.tileSize.y);
					quad[2].texCoords = sf::Vector2f((tu + 1) * tilemapdata.tileSize.x, (tv + 1) * tilemapdata.tileSize.y);
					quad[3].texCoords = sf::Vector2f(tu * tilemapdata.tileSize.x, (tv + 1) * tilemapdata.tileSize.y);
					
					std::vector<sf::IntRect> frames;
					int speed = animData[positionInAnimData].frames[0].duration;

					for (size_t i = 0; i < animData[positionInAnimData].frames.size(); i++) {
						int fu = animData[positionInAnimData].frames[i].tileid % (t->getSize().x / tilemapdata.tileSize.x);
						int fv = animData[positionInAnimData].frames[i].tileid / (t->getSize().x / tilemapdata.tileSize.x);
						int fx = fu * tilemapdata.tileSize.x;
						int fy = fv * tilemapdata.tileSize.y;
						int fw = (fu + 1) * tilemapdata.tileSize.x;
						int fh = (fv + 1) * tilemapdata.tileSize.y;
						frames.push_back(sf::IntRect(fx, fy, fw, fh));
					}

					animatedTiles.appendTile(quad, frames, speed);
				}
				else {
					// pointer to the tile's quad
					sf::Vertex quad[4];// = &vertexs[position * 4];

					// set position of 4 vertices (cw order)
					quad[0].position = sf::Vector2f(x * tilemapdata.tileSize.x, y * tilemapdata.tileSize.y);
					quad[1].position = sf::Vector2f((x + 1) * tilemapdata.tileSize.x, y * tilemapdata.tileSize.y);
					quad[2].position = sf::Vector2f((x + 1) * tilemapdata.tileSize.x, (y + 1) * tilemapdata.tileSize.y);
					quad[3].position = sf::Vector2f(x * tilemapdata.tileSize.x, (y + 1) * tilemapdata.tileSize.y);

					// set texture coords (cw order)
					quad[0].texCoords = sf::Vector2f(tu * tilemapdata.tileSize.x, tv * tilemapdata.tileSize.y);
					quad[1].texCoords = sf::Vector2f((tu + 1) * tilemapdata.tileSize.x, tv * tilemapdata.tileSize.y);
					quad[2].texCoords = sf::Vector2f((tu + 1) * tilemapdata.tileSize.x, (tv + 1) * tilemapdata.tileSize.y);
					quad[3].texCoords = sf::Vector2f(tu * tilemapdata.tileSize.x, (tv + 1) * tilemapdata.tileSize.y);
					
					vertexs.push_back(quad[0]);
					vertexs.push_back(quad[1]);
					vertexs.push_back(quad[2]);
					vertexs.push_back(quad[3]);
				}
			}
		}
	}

	return true;
}

void Tilemap::setTexture(sf::Texture* t) {
	m_tileset = t;
	states.texture = m_tileset;
	animatedTiles.setTilemap(t);
}

bool Tilemap::loadCollisions(std::vector<Collision> c) {
	collisions = c;
	return true;
}

void Tilemap::setWindow(sf::RenderWindow* w){
	window = w;
}

void Tilemap::animate(float dt) {
	animatedTiles.animate(dt);
}

void Tilemap::draw(){
	window->draw(vertexs.data(), vertexs.size(), sf::Quads, states);
	//window->draw(vertexs.data(), states);
	window->draw(animatedTiles, states);
}

void Tilemap::drawDebug() {
	for (size_t i = 0; i < collisions.size(); i++) {
		collisions[i].drawDebug(window);
	}
}

void Tilemap::setShader(sf::Shader s){
	states.shader = &s;
}