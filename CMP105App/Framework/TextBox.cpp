#include "TextBox.h"
#include "RoomManager.h"

TextBox::TextBox(RoomManager* rm, InputHandler* input) {
	roommanager = rm;
	in = input;

	if (!roommanager->textures["textbox"].loadFromFile("Assets/textbox.png")) {
		std::cout << "Couldn't load textbox.png\n";
		abort();
	}
	state.texture = &roommanager->textures["textbox"];
	
	if (!roommanager->fonts["boxfont"].loadFromFile("Assets/zelda.ttf")) {
		std::cout << "Couldn't load font in textbox\n";
		abort();
	}
	text.setFont(roommanager->fonts["boxfont"]);
	text.setCharacterSize(16);
	sf::Texture& t = const_cast<sf::Texture&>(roommanager->fonts["boxfont"].getTexture(text.getCharacterSize()));
	t.setSmooth(false);

	tilesize = 8;
	boxrect = sf::FloatRect(0, 104, 160, 40);
	nineslice();

	text.setPosition(boxrect.left + 8, boxrect.top);
	text.setFillColor(sf::Color::Black);
}

void TextBox::setText(std::vector<std::string> t) {
	fulldialog = t;
	fulltext = fulldialog[0];
	showntext = fulltext[0];
	visiblecharacters = 1;
	currentdialog = 0;
	finished = false;
	next_dialog = false;

	// reset position
	state.transform.translate(-elementoffset);
	text.move(-elementoffset);
	// get new offset
	elementoffset = roommanager->getWindow()->getView().getCenter() - (roommanager->getWindow()->getView().getSize() / 2.f);
	// set correct position
	state.transform.translate(elementoffset);
	text.move(elementoffset);
}

void TextBox::update(float dt) {
	if (!finished) {
		if (in->isMouseLPressed() && next_dialog) {
			if (currentdialog >= fulldialog.size()) {
				finished = true;
				//roommanager->eventmanager.nextEvent();
				return;
			}
			fulltext = fulldialog[currentdialog];
			visiblecharacters = 1;
			showntext = fulltext[0];
			next_dialog = false;
		}

		if (textclock.getElapsedTime().asSeconds() > textupdatetime && !next_dialog) {
			textclock.restart();
			showntext += fulltext[visiblecharacters];
			if (fulltext[visiblecharacters] == ' ') {
				visiblecharacters++;
				showntext += fulltext[visiblecharacters];
			}
			visiblecharacters++;
			if (visiblecharacters >= fulltext.size()) {
				currentdialog++;
				visiblecharacters = 0;
				next_dialog = true;
			}
			text.setString(showntext);
		}
	}
}

void TextBox::draw(sf::RenderWindow* w) {
	if (!finished) {
		w->draw(vertexs.data(), vertexs.size(), sf::Quads, state);
		w->draw(text);
	}
}