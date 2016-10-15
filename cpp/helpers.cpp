extern const float pi = 3.14149;

float getRadius(int x, int y) {
	return sqrt(pow((x - 7.5) / 8, 2) + pow((y - 7.5) / 8, 2));
}
	
static float getAngle(int x, int y) {
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