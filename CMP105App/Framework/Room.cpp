#include "Room.h"
#include "RoomManager.h"

Room::Room(std::string fold, sf::RenderWindow* window, InputHandler* input, RoomManager* rm){
	FILE = fold;
	std::cout << FILE + ".json" << "\n";

	in = input;
	w = window;
	roommanager = rm;

	main_camera = in->getView();
	w->setView(main_camera);

	isloaded = &roommanager->tilemapData[fold].loaded;
}

Room::~Room() {}