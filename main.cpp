#include <iostream>
#include "screen/Screen.cpp"
#include <math.h>
#include <chrono>

using namespace std;

long getTime() {
	auto time = std::chrono::system_clock::now();
	auto since_epoch = time.time_since_epoch();
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch);
	return millis.count();
}

int main( int argc, const char* argv[]) {
	Screen* screen = new Screen();
	
	while (true) {
		long t = getTime();
		for (int x = 0; x < 16; x++) {
			for (int y = 0; y < 16; y++) {
				float angle = atan2(x - 8.0, y - 8.0);
				float radius = sqrt(pow(x - 8, 2) + pow(y - 8, 2));
				float stretch = 2.0 + sin(t * 0.0001);
				radius += angle * stretch;
				
				screen->frame[x][y].hsv(
					int(t * 0.02 + radius * 0.5) % 255,
					255,
					char(255.0 * pow(sin(radius / stretch - t * 0.003), 4.0)));
			}
		}
		screen->update();
	}
}