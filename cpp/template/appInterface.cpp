#include "../../app/ShaderApp.cpp"
#include <iostream>
#include "<AppName>.cpp"
#include <unistd.h>
#include <thread>
#include <chrono>
#include <math.h>

using namespace std;

<AppName>* app = 0;
thread* appThread = 0;

void runAppTask() {
	try {
		app->run();
	}
	catch(InterruptException exception) { }
}

extern "C" void start() {
	if (app != 0) {
		return;
	}
	
	app = new <AppName>();
	appThread = new thread(runAppTask);
}

extern "C" void stop() {
	if (app == 0) {
		return;
	}
	
	app->stop();
	if (appThread != 0) {
		appThread->join();
		delete appThread;
		appThread = 0;
	}
}

extern "C" void deleteApp() {
	if (app != 0) {		
		delete app;
	}
}

extern "C" int getFPS() {
	if (app == 0) {
		return 0;
	}
	return app->getFPS();
}

extern "C" char* getFrame() {
	return app->getFrame().getPixelArray();
}

long getTime() {
	auto time = std::chrono::system_clock::now();
	auto since_epoch = time.time_since_epoch();
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch);
	return millis.count();
}

extern "C" void fadeout() {
	stop();
	Frame frame;
	
	if (app == 0) {
		Screen::getInstance().update(frame);
		return;
	}
	
	const int duration = 500;
	long start = getTime();
	while (true) {
		float progress = (float)(getTime() - start) / duration;
		for (int x = 0; x < 16; x++) {
			for (int y = 0; y < 16; y++) {
				frame[x][y].set(
					max(0, int(float(app->getFrame()[x][y].r) * (1.0 - progress))),
					max(0, int(float(app->getFrame()[x][y].g) * (1.0 - progress))),
					max(0, int(float(app->getFrame()[x][y].b) * (1.0 - progress))));
			}
		}
		Screen::getInstance().update(frame);
		if (progress >= 1.0) {
			return;
		}
	}
}