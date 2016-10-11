class <AppName> : public LoopApp {
protected:
	void setup() {
	
	}
	
	void loop() {
		Color color;
		color.hsv(time / 20, 255, 255);
		frame.clear(color);
	}
};