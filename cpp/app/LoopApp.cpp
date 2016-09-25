#include "App.cpp"

class LoopApp : public App {
private:
	bool running;	
protected:
	virtual void setup() {}
	
	virtual void loop() = 0;
public:
	LoopApp() {
		this->running = false;
	}

	void run() {
		this->running = true;
		
		this->setup();
		while (this->running) {
			this->loop();
			this->update();
		}
	}
	
	void stop() {
		this->running = false;
	}
};