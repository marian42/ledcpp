class Color {
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	
	Color(unsigned char r, unsigned char g, unsigned char b) {
		this->set(r, g, b);
	}
	
	Color() {
		this->set(0);
	}
	
	Color(unsigned char brightness) {
		this->set(brightness);
	}
	
	void set(unsigned char r, unsigned char g, unsigned char b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
	
	void set(unsigned char brightness) {
		this->set(brightness, brightness, brightness);
	}
	
	void copy(Color* color) {
		this->set(color->r, color->g, color->b);
	}
	
	unsigned int toInt() {
		return (r << 16) + (g << 8) + b;
	}
};