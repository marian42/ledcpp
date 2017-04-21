#include "<AppName>.h"

void <AppName>::mainImage(Color& color, int x, int y) {
	color.hsv((x * 16 - int(time * 100)) % 256, 255, 255);
}