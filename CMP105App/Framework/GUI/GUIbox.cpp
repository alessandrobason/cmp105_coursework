#include "GUIbox.h"

GUIbox::GUIbox(const GUIbox& copy) : GUItiledelement(copy) {
	tilesize = copy.tilesize;
}

void GUIbox::load() {
	GUItiledelement::load();
	if (states.texture == NULL) {
		std::cout << "Texture not loaded\n";
		abort();
	}
	nineslice();
}