#include "../app/ShaderApp.cpp"

class Swirl : public ShaderApp {
protected:
	void mainImage(Color& color, int x, int y) {
		float angle = atan2(x - 8.0, y - 8.0);
		float radius = sqrt(pow(x - 8, 2) + pow(y - 8, 2));
		float stretch = 2.0 + sin(time * 0.0001);
		radius += angle * stretch;
		
		color.hsv(
			int(time * 0.02 + radius * 0.5) % 255,
			255,
			char(255.0 * (0.5 + 0.5 * sin(2.0 * radius / stretch - time * 0.006))));
	}
};