#include "ShaderApp.h"

void ShaderApp::loop() {
	for (int x = 0; x < Frame::WIDTH; x++) {
		for (int y = 0; y < Frame::HEIGHT; y++) {
			mainImage(this->frame[x][y], x, y);
		}
	}
}