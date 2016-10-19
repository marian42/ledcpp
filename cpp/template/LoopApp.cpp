class <AppName> : public LoopApp {
protected:
	void setup() {
	
	}
	
	void loop() {
		Color color;
		color.hsv(time * 50, 255, 255);
		frame.clear(color);
	}
};