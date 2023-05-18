#include "GUIelement.h"

GUIelement::GUIelement(const GUIelement& copy) {
	oldpointer = &const_cast<GUIelement&>(copy);
	parent = copy.parent;
	zbuffer = copy.zbuffer;
	enabled = copy.enabled;
	vertexs = copy.vertexs;
	states = copy.states;
	boxrect = copy.boxrect;
	currentcontrol = copy.currentcontrol;
	horizontal_alignment = copy.horizontal_alignment;
	vertical_alignment = copy.vertical_alignment;
}

void GUIelement::draw(sf::RenderWindow* w) {
	w->draw(vertexs.data(), vertexs.size(), sf::Quads, states);
}

void GUIelement::setPosition(sf::Vector2f pos) {
	pos += elementoffset;
	sf::Vector2f offset = pos - getPosition();
	states.transform.translate(offset);
	boxrect.left = pos.x;
	boxrect.top = pos.y;
}

void GUIelement::alignElement() {
	// HORIZONTAL
	switch (horizontal_alignment) {
	case ALIGN::NONE:
		setPosition(sf::Vector2f(parent->getPosition().x + getPosition().x, boxrect.top));
		break;
	case ALIGN::CENTER:
		setCenter(sf::Vector2f(parent->getCenter().x, getCenter().y));
		break;
	case ALIGN::LEFT:
		setPosition(sf::Vector2f(parent->boxrect.left, boxrect.top));
		break;
	case ALIGN::RIGHT:
		setPosition(sf::Vector2f((parent->boxrect.left + parent->boxrect.width) - boxrect.width, boxrect.top));
		break;
	}
	// VERTICAL
	switch (vertical_alignment)	{
	case ALIGN::NONE:
		setPosition(sf::Vector2f(boxrect.left, parent->getPosition().y + getPosition().y));
		break;
	case ALIGN::CENTER:
		setCenter(sf::Vector2f(getCenter().x, parent->getCenter().y));
		break;
	case ALIGN::TOP:
		setPosition(sf::Vector2f(boxrect.left, parent->boxrect.top));
		break;
	case ALIGN::BOTTOM:
		setPosition(sf::Vector2f(boxrect.left, (parent->boxrect.top + parent->boxrect.height) - boxrect.height));
		break;
	}
}

void GUIelement::appendQuad(sf::Vertex v, sf::Vector2f size) {
	sf::Vector2f coords = v.position;
	sf::Vector2f positionoffset[4] = {
		sf::Vector2f(0, 0),
		sf::Vector2f(size.x, 0),
		sf::Vector2f(size.x, size.y),
		sf::Vector2f(0, size.y),
	};

	sf::Vector2f textureoffset[4] = { sf::Vector2f() };

	if (states.texture) {
		int w = states.texture->getSize().x;
		int h = states.texture->getSize().y;
		textureoffset[0] = sf::Vector2f(0, 0);
		textureoffset[1] = sf::Vector2f(w, 0);
		textureoffset[2] = sf::Vector2f(w, h);
		textureoffset[3] = sf::Vector2f(0, h);
	}

	for (size_t i = 0; i < 4; i++) {
		v.position = positionoffset[i] + coords;
		if (states.texture) v.texCoords = textureoffset[i];
		else v.color = backgroundcolor;
		vertexs.push_back(v);
	}
}

void GUIelement::setShader(std::string file, sf::Shader::Type type) {
	if(states.shader == nullptr) states.shader = new sf::Shader();
	sf::Shader* shader = const_cast<sf::Shader*>(states.shader);

	if (!shader->loadFromFile(file, type)) {
		std::cout << "Couldn't load ";
		if (type == sf::Shader::Vertex) std::cout << "vertex";
		else std::cout << "fragment";
		std::cout << " shader: " << file << "\n";
	}
}