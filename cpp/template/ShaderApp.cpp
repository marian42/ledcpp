class <AppName> : public ShaderApp {
protected:
	void mainImage(Color& color, int x, int y) {
		color.hsv((x * 16 - time / 10) % 256, 255, 255);
	}
};