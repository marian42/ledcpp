#include "Color.cpp"

class Frame {
private:
	Color** pixel;
	
	void initialize() {
		for (int i = 0; i < this->WIDTH * this->HEIGHT; i++) {
			this->pixel[i] = new Color();
		}
	}
public:
	static const int WIDTH = 16;
	static const int HEIGHT = 16;
	
	Frame() {
		this->pixel = new Color*[this->WIDTH * this->HEIGHT];
	}
};