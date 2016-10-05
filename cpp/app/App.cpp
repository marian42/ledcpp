#include "../screen/Screen.cpp"
#include <chrono>

class InterruptException: public std::exception { };

class App {
private:
	static const int FPS_AVERAGE_COUNT = 10;
	
	int lastDeltaT[FPS_AVERAGE_COUNT];
	long lastUpdate;
	
	bool stopped;
	
	static long getTime() {
		auto time = std::chrono::system_clock::now();
		auto since_epoch = time.time_since_epoch();
		auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch);
		return millis.count();
	}
	
	void updateTime() {
		this->time = getTime();
		this->deltaT = this->time - this->lastUpdate;
		this->lastDeltaT[this->frameCount % this->FPS_AVERAGE_COUNT] = this->deltaT;
		this->lastUpdate = this->time;
	}

protected:
	Screen screen;
	
	long time;
	long deltaT;
	long frameCount;
	
	void update() {
		this->screen.update();
		this->updateTime();
		this->frameCount++;
		
		if (this->stopped) {
			throw InterruptException();
		}
	}

public:
	App() {
		this->frameCount = 0;
		this->lastUpdate = getTime();
		this->stopped = false;
	}

	virtual void run() = 0;
	
	void stop() {
		this->stopped = true;
	}
	
	long getDeltaT() {
		return this->deltaT;
	}
	
	int getFPS() {
		int deltaTSum = 0;
		for (int i = 0; i < this->FPS_AVERAGE_COUNT; i++) {
			deltaTSum += this->frameCount > i ? this->lastDeltaT[i] : 0;
		}
		if (this->frameCount < this->FPS_AVERAGE_COUNT) {
			return 1000 * this->frameCount / deltaTSum;
		} else {
			return 1000 * this->FPS_AVERAGE_COUNT / deltaTSum;
		}
	}
	
	Screen& getScreen() {
		while (this->frameCount == 0);
		return this->screen;
	}
};