#include "../screen/Screen.cpp"
#include <chrono>

class App {
private:
	long lastUpdate;
	long lastFPSPrint;
	
	static long getTime() {
		auto time = std::chrono::system_clock::now();
		auto since_epoch = time.time_since_epoch();
		auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch);
		return millis.count();
	}
	
	void updateTime() {
		this->time = getTime();
		this->deltaT = this->time - this->lastUpdate;
		this->lastUpdate = this->time;
		
		if (this->time - this->lastFPSPrint > 1000) {
			float fps = 1000.0 / (float)(this->deltaT);
			cout << fps << endl;
			this->lastFPSPrint = this->time;			
		}
	}

protected:
	Screen screen;
	
	long time;
	long deltaT;
	
	void update() {
		this->screen.update();			
		this->updateTime();
	}

public:
	App() {
		this->lastUpdate = getTime();
		this->lastFPSPrint = this->lastUpdate;
	}

	virtual void run() = 0;
	
	virtual void stop() = 0;
};