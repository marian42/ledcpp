#include "Frame.cpp"
#include <cstdint>
#include <math.h>
#include "rpi_ws281x/ws2811.h"

#define TARGET_FREQ		WS2811_TARGET_FREQ
#define GPIO_PIN		18
#define DMA				5

#include <iostream>
using namespace std;

class Screen {
private:
	ws2811_t ledString;
	
	void initializeLEDString() {
		ledString = {
			nullptr,
			nullptr,
			TARGET_FREQ,
			DMA, {
				{ GPIO_PIN, 0, Frame::WIDTH * Frame::HEIGHT, 255 },
				{ 0 }
			}
		};
		ws2811_init(&ledString);
	}

	unsigned char processColor(unsigned char value) {
		return (int)(255.0 * pow(value / 255.0 * brightness, gamma));
	}
	
	int colorToInt(Color* color) {
		return    (processColor(color->r) << 8)
				+ (processColor(color->g) << 16)
				+ (processColor(color->b) << 0);
	}
	
public:
	Frame frame;
	float brightness;
	float gamma;
	
	Screen() {
		this->brightness = 1.0;
		this->gamma = 2.0;
		this->frame = Frame();
		this->initializeLEDString();
	}
	
	void update() {
		for (int x = 0; x < Frame::WIDTH; x++) {
			for (int y = 0; y < Frame::HEIGHT; y++) {
				int address = y * Frame::HEIGHT + (y % 2 == 0 ? x : Frame::WIDTH - 1 - x);
				this->ledString.channel[0].leds[address] = colorToInt(&(this->frame[x][y]));
			}
		}
		ws2811_render(&ledString);
	}
};