#pragma once
#include "GUIelement.h"

class GUItiledelement : public GUIelement {
public:
	GUItiledelement() : GUIelement() {}
	GUItiledelement(const GUItiledelement& copy) : GUIelement(copy) {}
	void setTileSize(int t) { tilesize = t; }
	void nineslice();

protected:
	int tilesize = NULL;
	sf::Vector2i numberoftiles;
	sf::Vector2f remainingsize;
	void load() override;
	void appendQuad(sf::Vertex v, sf::Vector2f size);
};