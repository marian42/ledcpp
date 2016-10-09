#include "LoopApp.cpp"

class ShaderApp : public LoopApp {
protected:
	virtual void mainImage(Color& color, int x, int y) = 0;

	void loop() {
		for (int x = 0; x < Frame::WIDTH; x++) {
			for (int y = 0; y < Frame::HEIGHT; y++) {
				mainImage(this->frame[x][y], x, y);
			}
		}
	}
};