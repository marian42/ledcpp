#ifndef APP_H
#define APP_H

#include "../screen/Screen.h"
#include <exception>

class InterruptException : public std::exception { };

class App {
private:
	static const int FPS_AVERAGE_COUNT = 10;
	
	int lastDeltaT[FPS_AVERAGE_COUNT];
	long lastUpdate;
	long startTimeMillis;
	
	bool stopped;
	
	static long getMillis();
	
	void updateTime();

protected:
	Frame frame;
	
	long millis;
	float time;
	long deltaT;
	long frameCount;
	
	void update();

public:
	App();

	virtual void run() = 0;
	
	void stop();
	
	long getDeltaT();
	
	int getFPS();
	
	Frame& getFrame();
};

#endif