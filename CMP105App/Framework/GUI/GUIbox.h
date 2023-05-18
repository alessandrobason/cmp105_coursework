#pragma once
#include "GUItiledelement.h"

class GUIbox : public GUItiledelement {
public:
	GUIbox() : GUItiledelement() {}
	GUIbox(const GUIbox& copy);

	void load();
};