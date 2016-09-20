class Color {
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	
	Color(unsigned char r, unsigned char g, unsigned char b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
	
	Color() {
		Color(0, 0, 0);
	}
};