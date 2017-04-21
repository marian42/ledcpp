#ifndef COLOR_H
#define COLOR_H

class Color {
	
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	
	Color(unsigned char r, unsigned char g, unsigned char b);
	
	Color();
	
	Color(unsigned char brightness);
	
	void set(unsigned char r, unsigned char g, unsigned char b);
	
	void set(unsigned char brightness);
	
	void set(Color& color);
	
	unsigned int toInt();
	
	void hsv(char hue, char saturation, char value);
	
	void hue(int hue);
	
	void blend(Color& c1, Color& c2, float progress);
};

#endif