#include "App.cpp"

class LoopApp : public App {
protected:
	virtual void setup() {}
	
	virtual void loop() = 0;
public:
	void run() {
		this->setup();
		while (true) {
			this->loop();
			this->update();
		}
	}
};