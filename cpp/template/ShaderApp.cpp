class <AppName> : public ShaderApp {
protected:
	void mainImage(Color& color, int x, int y) {
		color.hsv((x * 16 - int(time * 100)) % 256, 255, 255);
	}
};