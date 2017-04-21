#ifndef SCREEN_H
#define SCREEN_H

#include "Frame.h"

#include <cstdint>
#include "rpi_ws281x/ws2811.h"

#define TARGET_FREQ		WS2811_TARGET_FREQ
#define GPIO_PIN		18
#define DMA				5

class Screen {
private:
	ws2811_t ledString;
	
	void initializeLEDString();

	unsigned char processColor(unsigned char value);
	
	int colorToInt(Color* color);
	
	Screen();
	
public:
	float brightness;
	float gamma;
	
	void update(Frame& frame);
	
	static Screen& getInstance();
};

#endif