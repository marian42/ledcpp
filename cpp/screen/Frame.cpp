#include "Color.cpp"

class Frame {
private:
	class FrameColumn {
		private:
			Frame *frame;
			unsigned int x;
		public:
			FrameColumn(Frame *frame, unsigned int x) {
				this->frame = frame;
				this->x = x;
			}
			
		Color& operator[] (unsigned int y) {
			return *this->frame->get(this->x, y);
		}
	};
	
	Color** pixel;
	
	FrameColumn** columns;
	
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
		
		this->columns = new FrameColumn*[this->WIDTH];		
		for (int x = 0; x < this->WIDTH; x++) {
			this->columns[x] = new FrameColumn(this, x);
		}
		
		this->initialize();
	}
	
	~Frame() {
		for (int i = 0; i < this->WIDTH * this->HEIGHT; i++) {
			delete this->pixel[i];
		}
		delete this->pixel;
		for (int x = 0; x < this->WIDTH; x++) {
			delete this->columns[x];
		}
		delete this->columns;
	}
	
	FrameColumn operator[] (unsigned int x) {
		return *this->columns[x];
	}
	
	Color* get(unsigned int x, unsigned int y) {
		return this->pixel[y * this->WIDTH + x];
	}
};