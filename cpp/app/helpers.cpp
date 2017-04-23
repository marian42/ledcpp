#include "helpers.h"
#include <cmath>

float getRadius(int x, int y) {
	return sqrt(pow((x - 7.5) / 8, 2) + pow((y - 7.5) / 8, 2));
}
	
float getAngle(int x, int y) {
	return atan2(x - 7.5, y - 7.5) + pi;
}

float clamp(float value, float min, float max) {
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

float clamp(float value) {
	return clamp(value, 0.0, 1.0);
}	

float fract(float value) {
	return value - floor(value);
}

float modulo(float value, float divisor) {
	return value - divisor * floor(value / divisor);
}

float map(float value, float oldLow, float oldHigh, float newLow, float newHigh) {
	return newLow + (newHigh - newLow) * (value - oldLow) / (oldHigh - oldLow);
}

float noise(float x, float y) {
	static bool initialized = false;
	if (!initialized) {
		initialized = true;
		Simplex::init();
	}
	return Simplex::noise(x, y);
}

int getRing(int x, int y) {
	return 7 - (x + y > 15 ? min(15 - x, 15 - y) : min(x, y));
}

int getRingPosition(int x, int y) {
	int ring = getRing(x, y);
	if (x + y < 15) {
		if (x >= y) { // up
			return x - y + 0 * 2 * (ring + 1);
		} else { // left
			return -2 + 2 * ring - y + x + 3 * 2 * (ring + 1);
		}
	} else {
		if (x >= y) { // right
			return -1 + y - (15 - x) + 1 * 2 * (ring + 1);
		} else { // down
			return -2 + y - x + 2 * 2 * (ring + 1);
		}	
	}
}

float max(float a, float b) {
	return a > b ? a : b;
}

float min(float a, float b) {
	return a < b ? a : b;
}

int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b) {
	return a < b ? a : b;
}