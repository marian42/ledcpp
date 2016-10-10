float getRadius(unsigned int x, unsigned int y) {
	return sqrt(pow(x - 8, 2) + pow(y - 8, 2));
}
	
static float getAngle(unsigned int x, unsigned int y) {
	return atan2(x - 8.0, y - 8.0);
}

float clamp(float value, float min, float max) {
	if (value < min) return min;
	if (value > max) return max;
	return value;
}