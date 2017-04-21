#include "LoopApp.h"

void LoopApp::run() {
	this->setup();
	while (true) {
		this->loop();
		this->update();
	}
}