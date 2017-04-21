#ifndef FRAME_H
#define FRAME_H

#include "Color.h"

class Frame;

class FrameColumn {
private:
	Frame *frame;
	unsigned int x;
public:
	FrameColumn(Frame *frame, unsigned int x);
	
	Color& operator[] (unsigned int y);
};

class Frame {
private:	
	Color** pixel;
	
	FrameColumn** columns;
	
	void initialize();
	
public:
	static const int WIDTH = 16;
	static const int HEIGHT = 16;
	
	Frame();
	
	~Frame();
	
	FrameColumn operator[] (unsigned int x);
	
	Color* get(unsigned int x, unsigned int y);
	
	char* getPixelArray();
	
	void clear(Color color);
	
	void clear();
};

#endif