#include "GUItiledelement.h"

void GUItiledelement::load() {
	if (tilesize == NULL) {
		std::cout << "tilesize can't be 0\n";
		abort();
	}
}

void GUItiledelement::appendQuad(sf::Vertex v, sf::Vector2f size) {
	sf::Vector2f coords = v.position;
	sf::Vector2f texcoords = v.texCoords;
	sf::Vector2f positionoffset[4] = {
		sf::Vector2f(0, 0),
		sf::Vector2f(size.x, 0),
		sf::Vector2f(size.x, size.y),
		sf::Vector2f(0, size.y),
	};
	sf::Vector2f textureoffset[4] = {
		sf::Vector2f(0, 0),
		sf::Vector2f(tilesize, 0),
		sf::Vector2f(tilesize, tilesize),
		sf::Vector2f(0, tilesize),
	};

	for (size_t i = 0; i < 4; i++) {
		v.position = positionoffset[i] + coords;
		v.texCoords = textureoffset[i] + texcoords;
		vertexs.push_back(v);
	}
}

void GUItiledelement::nineslice() {
	sf::Vertex v;
	if (backgroundcolor != sf::Color::Transparent) v.color = backgroundcolor;
	sf::FloatRect boxrectnine = boxrect;
	boxrectnine.width += boxrect.left;
	boxrectnine.height += boxrect.top;

	// LOAD MIDDLE
	v.position = sf::Vector2f(boxrectnine.left + tilesize, boxrectnine.top + tilesize);
	v.texCoords = sf::Vector2f(tilesize, tilesize);
	appendQuad(v, sf::Vector2f(boxrect.width - (tilesize * 2), boxrect.height - (tilesize * 2)));

	// LOAD CORNERS
	sf::Vector2f corner[4] = {
		sf::Vector2f(boxrectnine.left			 , boxrectnine.top),
		sf::Vector2f(boxrectnine.width - tilesize, boxrectnine.top),
		sf::Vector2f(boxrectnine.left			 , boxrectnine.height - tilesize),
		sf::Vector2f(boxrectnine.width - tilesize, boxrectnine.height - tilesize)
	};
	sf::Vector2f texCorner[4] = {
		sf::Vector2f(0			 , 0),
		sf::Vector2f(tilesize * 2, 0),
		sf::Vector2f(0			 , tilesize * 2),
		sf::Vector2f(tilesize * 2, tilesize * 2)
	};
	sf::Vector2f coords[4] = {
		sf::Vector2f(0		 , 0),
		sf::Vector2f(tilesize, 0),
		sf::Vector2f(tilesize, tilesize),
		sf::Vector2f(0		 , tilesize),
	};

	for (size_t i = 0; i < 4; i++) {
		v.position = corner[i];
		v.texCoords = texCorner[i];
		appendQuad(v, sf::Vector2f(tilesize, tilesize));
	}


	// LOAD INBETWEENS
	int totalwidth = boxrect.width - tilesize * 2;
	int totalheight = boxrect.height - tilesize * 2;
	numberoftiles = sf::Vector2i(totalwidth, totalheight) / tilesize;
	remainingsize = sf::Vector2f(totalwidth % tilesize, totalheight % tilesize);
	std::cout << "###### REMAINING SIZE ######" << remainingsize.x << " " << remainingsize.y << "\n";

	sf::Vector2f sideCoords[4]{
		sf::Vector2f(boxrectnine.left + tilesize , boxrectnine.top),
		sf::Vector2f(boxrectnine.left + tilesize , boxrectnine.height - tilesize),
		sf::Vector2f(boxrectnine.left			 , boxrectnine.top + tilesize),
		sf::Vector2f(boxrectnine.width - tilesize, boxrectnine.top + tilesize)
	};
	sf::Vector2f sideTex[4]{
		sf::Vector2f(tilesize  , 0),
		sf::Vector2f(tilesize  , tilesize * 2),
		sf::Vector2f(0		   , tilesize),
		sf::Vector2f(tilesize * 2, tilesize)
	};

	for (size_t i = 0; i < 2; i++) {
		for (size_t j = 0; j < numberoftiles.x; j++) {
			// HORIZONTAL
			float x = sideCoords[i].x + (tilesize * j);
			v.position = sf::Vector2f(x, sideCoords[i].y);
			v.texCoords = sideTex[i];
			appendQuad(v, sf::Vector2f(tilesize, tilesize));
		}
		v.position = sf::Vector2f(sideCoords[i].x + numberoftiles.x * tilesize, sideCoords[i].y);
		v.texCoords = sideTex[i];
		appendQuad(v, sf::Vector2f(remainingsize.x, tilesize));
		//////////////////////////////////////////////
		for (size_t j = 0; j < numberoftiles.y; j++) {
			// VERTICAL
			float y = sideCoords[i + 2].y + (tilesize * j);
			v.position = sf::Vector2f(sideCoords[i + 2].x, y);
			v.texCoords = sideTex[i + 2];
			appendQuad(v, sf::Vector2f(tilesize, tilesize));
		}
		v.position = sf::Vector2f(sideCoords[i + 2].x, sideCoords[i + 2].y + numberoftiles.y * tilesize);
		v.texCoords = sideTex[i + 2];
		appendQuad(v, sf::Vector2f(tilesize, remainingsize.y));
	}
}
