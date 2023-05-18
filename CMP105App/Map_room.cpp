#include "Map_room.h"
#include "Framework/RoomManager.h"

Map_room::Map_room(RoomManager* rm, sf::RenderWindow* window, InputHandler* input, std::string fold) : Room(fold, window, input, rm) {
	layers = &roommanager->tilemapData[fold].layers;
	tilemap_data = &roommanager->tilemapData[fold].tilemap_data;
	tilemap = &roommanager->tilemapData[fold].tilemap;
	shader = &roommanager->tilemapData[fold].shader;
	textbox = roommanager->getTextBoxPointer();
}

Map_room::~Map_room() {
	delete layers;
	delete tilemap_data;
	delete tilemap;
	delete shader;
	layers = nullptr;
	tilemap_data = nullptr;
	tilemap = nullptr;
	shader = nullptr;
}

void Map_room::load(sf::Vector2f off) {
	if (roommanager->tilemapData[FILE].loaded) return;
	offset = off;
	std::cout << "Loading: " << FILE << "\n";
	
	std::string tileset_json;
	std::string tileset_file;

	const std::string ASSETS = "Assets/";

	std::cout << "Loading json file\n";
	// load the json file for the map
	tilemap_json = new JSONparser("Rooms/" + FILE + ".json");

	// load tileset json
	tileset_json = tilemap_json->doc["tilesets"].arr[0].obj["source"].str;
	//////////////////////
	size_t firstalph = tileset_json.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPWRSTUVWXYZ");
	if (firstalph == std::string::npos) {
		std::cout << "There's been a problem with the tileset filename: " << tileset_json << "\n";
		abort();
	}
	tileset_json.replace(0, firstalph, "");
	if (tileset_json[0] != 'A') {
		tileset_json = "Assets/" + tileset_json;
	}
	
	JSONparser* ts_json = new JSONparser(tileset_json);

	std::vector<Tilemap::animated_tiles_data> animatedTilesData;

	// load tilemap data
	tilemap_data->numb_layers = (int)tilemap_json->doc["layers"].arr.size();
	tilemap_data->tileSize.x = tilemap_json->doc["tilewidth"].i;
	tilemap_data->tileSize.y = tilemap_json->doc["tileheight"].i;
	tilemap_data->h = tilemap_json->doc["height"].i;
	tilemap_data->w = tilemap_json->doc["width"].i;

	std::cout << "Map json file: " << FILE << ".json\n";
	std::cout << "Map height: " << tilemap_data->h << "\n";
	std::cout << "Map width: " << tilemap_data->w << "\n";
	std::cout << "Number of layers: " << tilemap_data->numb_layers << "\n";

	int numb_layers = tilemap_data->numb_layers;
	std::vector<Collision> collisions;

	// LOAD LAYERS DATA //
	for (int i = 0; i < numb_layers; i++) {
		std::cout << "Layer " << i + 1 << ": \n";
		std::cout << "\tName: " << tilemap_json->doc["layers"].arr[i].obj["name"].str << "\n";

		// load collisions
		if (tilemap_json->doc["layers"].arr[i].obj["type"].str == "objectgroup") {
			tilemap_data->numb_layers--;
			if (tilemap_json->doc["layers"].arr[i].obj["name"].str == "collisions") {
				for (size_t k = 0; k < tilemap_json->doc["layers"].arr[i].obj["objects"].arr.size(); k++) {
					JSONparser::datatypes* current = &tilemap_json->doc["layers"].arr[i].obj["objects"].arr[k];
					int x = offset.x + current->obj["x"].i;
					int y = offset.y + current->obj["y"].i;
					int width = current->obj["width"].i;
					int height = current->obj["height"].i;
					Collision::LAYER layer = Collision::LAYER::ALL;
					if (current->obj["type"].str == "water") {
						layer = Collision::LAYER::WATER;
					}
					else if (current->obj["type"].str == "interactable") {
						if (current->obj["name"].str == "puzzle_piece") {
							interactables.push_back(new Statue(roommanager, x, y, width, height));
						}
						else if (current->obj["name"].str == "man") {
							interactables.push_back(new ManInteractable(roommanager, x, y, width, height));
						}
					}
					collisions.push_back(Collision(x, y, width, height, layer));
				}
			}
			else if (tilemap_json->doc["layers"].arr[i].obj["name"].str == "spawnpoints") {
				enemiesData = tilemap_json->doc["layers"].arr[i].obj["objects"].arr;
			}
		}
		else {

			// load tileset
			for (int j = 0; j < tilemap_json->doc["layers"].arr[i].obj["data"].arr.size(); j++) {
				int t = tilemap_json->doc["layers"].arr[i].obj["data"].arr[j].i;
				t--; // tiled starts at 1 instead of 0
				layers->push_back(t);
			}
		}
	}

	// load tileset data

	tileset_file = ts_json->doc["image"].str;

	std::cout << "Tileset json file: " << tileset_json << "\n";
	std::cout << "Tileset image file: " << tileset_file << "\n";
	if (!roommanager->images["tiles"].loadFromFile(tileset_file)) {
		std::cout << "Couldn't load tileset from " << tileset_file << "\n";
		abort();
	}

	std::cout << "number of tiles: " << ts_json->doc["tiles"].size << "\n";

	// loading animated tiles
	std::unordered_map<std::string, JSONparser::datatypes>::const_iterator it;
	for (auto const& x : ts_json->doc["tiles"].obj) {
		it = x.second.obj.find("animation");
		if (it != x.second.obj.end()) {
			std::vector<Tilemap::animated_tiles_data::data> temp;
			for (size_t i = 0; i < it->second.arr.size(); i++) {
				temp.push_back({ it->second.arr[i].obj.at("duration").i , it->second.arr[i].obj.at("tileid").i });
			}
			animatedTilesData.push_back({ x.first, temp });
		}
	}

	std::cout << "animatedTilesData: " << animatedTilesData.size() << "\n";

	tilemap->load(roommanager->getDebug(), &roommanager->images["tiles"], animatedTilesData, *layers, *tilemap_data, offset);
	tilemap->loadCollisions(collisions);

	loadData();

	delete ts_json;
	ts_json = nullptr;

	*isloaded = true;

	setBounds(offset);

	tilemap->setWindow(w);
}

void Map_room::setPlayer(Player* pl) {
	p = pl;
	sceneObjects.push_back(p);
}

void Map_room::removePlayer() {
	for (size_t i = 0; i < sceneObjects.size(); i++) {
		if (sceneObjects[i] == p){
			sceneObjects.erase(sceneObjects.begin() + i);
		}
	}
	p = nullptr; 
}

void Map_room::setPlayerPosition(sf::Vector2f pos) {
	p->setPosition(pos);
}

void Map_room::loadData() {
	for (size_t i = 0; i < tilemap->collisions.size(); i++) {
		sceneColliders.push_back(&tilemap->collisions[i]);
	}

	std::cout << "\t##### LOADING ENEMIES #####\n";
	for (size_t k = 0; k < enemiesData.size(); k++) {
		JSONparser::datatypes* current = &enemiesData[k];
		std::string name = current->obj["template"].str;
		sf::Vector2f position = offset;
		position.x += current->obj["x"].i;
		position.y += current->obj["y"].i - 16; // tiled starts at 16 for some reason

		size_t firstalph = name.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPWRSTUVWXYZ");

		// removes all character before the enemy name
		name.replace(0, firstalph, "");
		// removes all character after the enemy name
		name.replace(name.end() - 3, name.end(), "");

		if (name == "octorock") {
			sceneObjects.push_back(new Octorock(roommanager->getEnemyCopy(name)));
		}

		sceneObjects.back()->setPosition(position);
		sceneColliders.push_back(&sceneObjects.back()->collider);
		std::cout << "\t\tname: " << name << "\n";
		std::cout << "\t\tposition: " << position.x << " " << position.y << "\n";
	}

	if (FILE == "plateau") {
		sceneObjects.push_back(roommanager->getMan());
	}
}

void Map_room::resetRoom() {
	GameObject* player = nullptr;
	for (size_t i = 0; i < sceneObjects.size(); i++) {
		if (sceneObjects[i] == p) continue;
		if (sceneObjects[i] == roommanager->getMan()) continue;
		delete sceneObjects[i];
		sceneObjects[i] = nullptr;
	}
	p = nullptr;

	sceneObjects.clear();
	sceneColliders.clear();

	for (size_t i = 0; i < interactables.size(); i++) {
		interactables[i]->reset();
	}

	loadData();

	paused = false;
}

/*######################*\
||                      ||
||     HANDLE INPUT     ||
||                      ||
\*######################*/
void Map_room::handleInput(float dt) {
	if (!paused) {
		if (in->isKeyPressed(in->KEY_DEBUG)) roommanager->moveMenu("debugmenu");
		
		for (size_t i = 0; i < sceneObjects.size(); i++) {
			sceneObjects[i]->handleInput(dt);
		}

		if (in->isKeyPressed(in->KEY_INTERACT)) {
			sf::FloatRect check_interact = p->collider.rect;

			switch ((int)(p->getAngleToMouse() / 45)) {
			case 1:
			case 2:
				check_interact.top -= 1;
				break;
			case 3:
			case 4:
				check_interact.left += 1;
				break;
			case 5:
			case 6:
				check_interact.top += 1;
				break;
			case 7:
			case 0:
				check_interact.left -= 1;
				break;
			}

			for (size_t i = 0; i < interactables.size(); i++) {
				if (interactables[i]->Check_Collision(check_interact)) {
					interactables[i]->interact();
				}
			}
		}
	}
}

/*######################*\
||                      ||
||        UPDATE        ||
||                      ||
\*######################*/
void Map_room::update(float dt) {
	tilemap->animate(dt);

	if (!paused) {
		roommanager->scoreclock += dt;
		//update every gameobject (player too)
		for (size_t i = 0; i < sceneObjects.size(); i++) {
			if (sceneObjects[i] == p) sceneObjects[i]->update(dt);
			else {
				sceneObjects[i]->Advance();
				//check if player has gone inside gameobject checkbox (used for enemies)
				sf::FloatRect rect = sceneObjects[i]->checkbox.rect;
				if (p->checkbox.Check_Collision(rect))	sceneObjects[i]->isPlayerInside(true);
				else									sceneObjects[i]->isPlayerInside(false);
				sceneObjects[i]->update(dt);
			}
		}

		// check object collisions against tilemap
		for (size_t i = 0; i < sceneColliders.size(); i++) {
			sceneColliders[i]->setDebugColor(sf::Color::Red);
			for (size_t j = 0; j < sceneObjects.size(); j++) {
				if (sceneObjects[j] == p && p->getCheat(Player::CHEATS::WALKTHROUGHWALLS)) continue;
				if (sceneObjects[j]->collider.Check_Collision(sceneColliders[i]->rect)) {
					sf::Vector2f revVel = sceneObjects[j]->collider.getCollisionSide(sceneColliders[i]->rect, sceneObjects[j]->oldVel);
					sceneObjects[j]->move(revVel);
					sceneObjects[j]->collided = true;
					sceneColliders[i]->setDebugColor(sf::Color::Blue);
				}
			}
		}

		// check if player is going in another map //
		for (size_t i = 0; i < 4; i++) {
			if (p->collider.Check_Collision(bounds[i])) {
				roommanager->moveRoom(static_cast<int>(i));
				return;
			}
		}

		updateCamera();
	}
	else {
		textbox->update(dt);
	}

	roommanager->eventmanager.update(dt);
	//freeMemory();
	//cullGameObjects();
	//std::cout << "->" << camera_top_left.x << " " << camera_top_left.y << "\n";
}

void Map_room::updateCamera() {
	main_camera.setViewport(in->getView().getViewport());
	main_camera.setCenter(p->getSprite()->getPosition() + p->getLocalCenter());
	camera_top_left = main_camera.getCenter() - main_camera.getSize() / 2.f;
	camera_bottom_right = main_camera.getCenter() + main_camera.getSize() / 2.f;
	// STICK CAMERA //
	// left
	if (camera_top_left.x <= bounds[2].left + bounds[2].width) {
		main_camera.setCenter(sf::Vector2f(bounds[2].left + (main_camera.getSize().x / 2.f), main_camera.getCenter().y));
	}
	// right
	if (camera_bottom_right.x >= bounds[3].left) {
		main_camera.setCenter(sf::Vector2f(bounds[3].left - (main_camera.getSize().x / 2.f), main_camera.getCenter().y));
	}
	// top
	if (camera_top_left.y <= bounds[0].top) {
		main_camera.setCenter(sf::Vector2f(main_camera.getCenter().x, bounds[0].top + main_camera.getSize().y / 2.f));
	}
	// bottom
	if (camera_bottom_right.y >= bounds[1].top + bounds[1].height) {
		main_camera.setCenter(sf::Vector2f(main_camera.getCenter().x, bounds[1].top - (main_camera.getSize().y / 2.f)));
	}
	// update top_left of the camera for player
	camera_top_left = main_camera.getCenter() - main_camera.getSize() / 2.f;
	w->setView(main_camera);
}

/*######################*\
||                      ||
||         DRAW         ||
||                      ||
\*######################*/
void Map_room::draw() {
	sortGameObjects();
	tilemap->draw();
	for (size_t i = 0; i < sceneObjects.size(); i++) {
		sceneObjects[i]->draw();
	}

	// draw debug
	if (roommanager->isDebug()) {
		if(p != nullptr) p->drawDebug();
		tilemap->drawDebug();
		for (size_t i = 0; i < sceneObjects.size(); i++) {
			sceneObjects[i]->drawDebug();
		}
		for (size_t i = 0; i < interactables.size(); i++) {
			interactables[i]->drawDebug(w);
		}
	}

	roommanager->eventmanager.draw(w);
}

void Map_room::start() {
	roommanager->playSong("game");
	if (roommanager->eventmanager.getNumberOfEvents() == 0) setPause(false);
}

void Map_room::removeObject(GameObject* g) {
	for (size_t i = 0; i < sceneObjects.size(); i++) {
		if (sceneObjects[i] == g) {
			//destroyedSceneObjects.push_back(sceneObjects[i]);
			sceneObjects[i] = sceneObjects.back();
			sceneObjects.resize(sceneObjects.size() - 1);
			break;
		}
	}
	for (size_t i = 0; i < sceneColliders.size(); i++) {
		if (sceneColliders[i] == &g->collider) {
			sceneColliders[i] = sceneColliders.back();
			sceneColliders.resize(sceneColliders.size() - 1);
			break;
		}
	}
}

void Map_room::freeMemory() {
	for (size_t i = 0; i < destroyedSceneObjects.size(); i++) {
		delete destroyedSceneObjects[i];
	}
	destroyedSceneObjects.clear();
}

void Map_room::sortGameObjects() {
	std::sort(sceneObjects.begin(), sceneObjects.end(), gameobjectsorting());
}

sf::Vector2f Map_room::moveRoom(sf::Transform t) {
	sf::RenderStates tilemapstate = tilemap->getStates();
	tilemapstate.transform = t;
	tilemap->setStates(tilemapstate);
	return tilemap->getPosition();
}

void Map_room::setBounds(sf::Vector2f offset) {
	this->offset = offset;
	bounds[0] = sf::FloatRect(offset.x						 , offset.y						  , static_cast<float>(roommanager->MAPSIZE), 0.1f); //top
	bounds[1] = sf::FloatRect(offset.x						 , offset.y + roommanager->MAPSIZE, static_cast<float>(roommanager->MAPSIZE), 0.1f); //bottom
	bounds[2] = sf::FloatRect(offset.x						 , offset.y						  , 0.1f									, static_cast<float>(roommanager->MAPSIZE)); //left
	bounds[3] = sf::FloatRect(offset.x + roommanager->MAPSIZE, offset.y						  , 0.1f									, static_cast<float>(roommanager->MAPSIZE)); //right
}