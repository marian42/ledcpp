#include "Screen.h"

#include <math.h>
#include <iostream>

void Screen::initializeLEDString() {
	ledString = (ws2811_t) {
		nullptr,
		nullptr,
		TARGET_FREQ,
		DMA, {
			{ GPIO_PIN, 0, Frame::WIDTH * Frame::HEIGHT, WS2811_STRIP_RGB, nullptr, 255 },
			{ 0, 0, 0, 0, nullptr, 0 }
		}
	};
	ws2811_init(&ledString);
}

unsigned char Screen::processColor(unsigned char value) {
	return (int)(255.0 * pow(value / 255.0 * brightness, gamma));
}

int Screen::colorToInt(Color* color) {
	return    (processColor(color->r) << 8)
			+ (processColor(color->g) << 16)
			+ (processColor(color->b) << 0);
}

Screen::Screen() {
	this->brightness = 1.0;
	this->gamma = 2.0;
	this->initializeLEDString();
}

void Screen::update(Frame& frame) {
	for (int x = 0; x < Frame::WIDTH; x++) {
		for (int y = 0; y < Frame::HEIGHT; y++) {
			int address = y * Frame::HEIGHT + (y % 2 == 0 ? x : Frame::WIDTH - 1 - x);
			this->ledString.channel[0].leds[address] = colorToInt(&(frame[x][y]));
		}
	}
	ws2811_render(&ledString);
}

Screen& Screen::getInstance() {
	static Screen instance;	
	return instance;
}
