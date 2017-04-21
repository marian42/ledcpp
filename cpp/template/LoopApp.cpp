#include "<AppName>.h"

void <AppName>::loop() {
	Color color;
	color.hsv(time * 50, 255, 255);
	frame.clear(color);
}