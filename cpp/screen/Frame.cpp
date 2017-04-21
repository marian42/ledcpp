#include "Frame.h"

FrameColumn::FrameColumn(Frame *frame, unsigned int x) {
	this->frame = frame;
	this->x = x;
}
			
Color& FrameColumn::operator[] (unsigned int y) {
	return *this->frame->get(this->x, y);
}
	
	
void Frame::initialize() {
	for (int i = 0; i < this->WIDTH * this->HEIGHT; i++) {
		this->pixel[i] = new Color();
	}
}
	
Frame::Frame() {
	this->pixel = new Color*[this->WIDTH * this->HEIGHT];
	
	this->columns = new FrameColumn*[this->WIDTH];		
	for (int x = 0; x < this->WIDTH; x++) {
		this->columns[x] = new FrameColumn(this, x);
	}
	
	this->initialize();
}

Frame::~Frame() {
	for (int i = 0; i < this->WIDTH * this->HEIGHT; i++) {
		delete this->pixel[i];
	}
	delete this->pixel;
	for (int x = 0; x < this->WIDTH; x++) {
		delete this->columns[x];
	}
	delete this->columns;
}

FrameColumn Frame::operator[] (unsigned int x) {
	return *this->columns[x];
}

Color* Frame::get(unsigned int x, unsigned int y) {
	return this->pixel[y * this->WIDTH + x];
}

char* Frame::getPixelArray() {
	char* result = new char[this->WIDTH * this->HEIGHT * 3];
	for (int i = 0; i < this->WIDTH * this->HEIGHT; i++) {
		result[i * 3 + 0] = this->pixel[i]->r;
		result[i * 3 + 1] = this->pixel[i]->g;
		result[i * 3 + 2] = this->pixel[i]->b;			
	}
	return result;
}

void Frame::clear(Color color) {
	for (int x = 0; x < this->WIDTH; x++) {
		for (int y = 0; y < this->HEIGHT; y++) {
			(*this)[x][y].set(color);
		}
	}
}

void Frame::clear() {
	this->clear(Color(0, 0, 0));
}