#include "Color.h"

Color::Color(unsigned char r, unsigned char g, unsigned char b) {
	this->set(r, g, b);
}

Color::Color() {
	this->set(0);
}

Color::Color(unsigned char brightness) {
	this->set(brightness);
}

void Color::set(unsigned char r, unsigned char g, unsigned char b) {
	this->rgb(r,g,b);
}

void Color::rgb(unsigned char r, unsigned char g, unsigned char b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

void Color::set(unsigned char brightness) {
	this->rgb(brightness, brightness, brightness);
}

void Color::gray(unsigned char brightness) {
	this->rgb(brightness, brightness, brightness);
}

void Color::set(Color& color) {
	this->rgb(color.r, color.g, color.b);
}

unsigned int Color::toInt() {
	return (r << 16) + (g << 8) + b;
}

void Color::hsv(char hue, char saturation, char value) {
	unsigned char region, remainder, p, q, t;

	if (saturation == 0) {
		this->set(value);
		return;
	}

	region = hue / 43;
	remainder = (hue - (region * 43)) * 6; 

	p = (value * (255 - saturation)) >> 8;
	q = (value * (255 - ((saturation * remainder) >> 8))) >> 8;
	t = (value * (255 - ((saturation * (255 - remainder)) >> 8))) >> 8;

	switch (region) {
		case 0:
			r = value; g = t; b = p;
			break;
		case 1:
			r = q; g = value; b = p;
			break;
		case 2:
			r = p; g = value; b = t;
			break;
		case 3:
			r = p; g = q; b = value;
			break;
		case 4:
			r = t; g = p; b = value;
			break;
		default:
			r = value; g = p; b = q;
			break;
	}
}

void Color::hue(int hue) {
	hsv(hue, 255, 255);
}

void Color::blend(Color& c1, Color& c2, float progress) {
	set(c1.r * (1.0 - progress) + c2.r * progress,
		c1.g * (1.0 - progress) + c2.g * progress,
		c1.b * (1.0 - progress) + c2.b * progress);
}