#include "EVENTmoveto.h"
#include "..\RoomManager.h"

EVENTmoveto::EVENTmoveto(RoomManager* rm, EventInput input) : Event(rm, input) {
	w = roommanager->getWindow();
	in = roommanager->getInput();
	if (input.cameramovement.size() > 0) {
		currentcameramovement = -1;
		sf::Vector2f camerapos = w->getView().getCenter();
		nextCamera();
	}
}

void EVENTmoveto::update(float dt) {
	if (currentcameramovement != -1) {
		cameratween.update(dt);
		//sf::View camera = w->getView();
		//camera.setCenter(cameratween.getValue());
		//w->setView(camera);
		roommanager->getCurrentRoom()->setCameraPosition(cameratween.getValue());
		if (cameratween.isfinished()) nextCamera();
	}
	bool finishedmovement = true;
	if (input.character != nullptr) {
		finishedmovement = input.character->moveTo(input.target, dt);
	}
	finished = finishedmovement && currentcameramovement == -1;
}

void EVENTmoveto::nextCamera() {
	currentcameramovement++;
	if (currentcameramovement >= input.cameramovement.size()) {
		currentcameramovement = -1;
	}
	else {
		sf::Vector2f camerapos = w->getView().getCenter();
		if (input.cameramovement[currentcameramovement].time == 0.f) {
			sf::View camera = w->getView();
			camera.setCenter(camerapos + input.cameramovement[currentcameramovement].position);
			w->setView(camera);
			nextCamera();
		} 
		else {
			cameratween = Tweening<sf::Vector2f>(camerapos, camerapos + input.cameramovement[currentcameramovement].position, input.cameramovement[currentcameramovement].time);
		}
	}
}