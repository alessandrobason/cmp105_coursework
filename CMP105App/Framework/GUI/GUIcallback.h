#pragma once

class GUIcallback {
public:
	struct RESPONSE {
		bool b = false;
		int i = NULL;
		float f = NULL;
	};

	virtual void callback(std::string id, RESPONSE value) {}
};