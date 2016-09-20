#include <stdint.h>
#include "rpi_ws281x/ws2811.h"

#define TARGET_FREQ		WS2811_TARGET_FREQ
#define GPIO_PIN		18
#define DMA				5
#define STRIP_TYPE		WS2811_STRIP_RGB

ws2811_t createLEDString(int width, int height) {
	ws2811_t ledString = {
			.freq = TARGET_FREQ,
			.dmanum = DMA,
			.channel = {
				[0] = {
					.gpionum = GPIO_PIN,
					.count = width * height,
					.invert = 0,
					.brightness = 255,
					.strip_type = STRIP_TYPE,
				},
				[1] = {
					.gpionum = 0,
					.count = 0,
					.invert = 0,
					.brightness = 0,
				},
			},
		};
	return ledString;
}

void test() {
	ws2811_t x = createLEDString(16, 16);
}