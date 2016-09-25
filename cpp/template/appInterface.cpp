#include "../../app/ShaderApp.cpp"
#include <iostream>
#include "<AppName>.cpp"
#include <unistd.h>
#include <thread>

<AppName>* app = 0;
thread* appThread = 0;

void runAppTask() {
	app->run();
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
	if (!appThread != 0) {
		appThread->join();
		delete appThread;
		appThread = 0;
	}
	delete app;
}

extern "C" int getFPS() {
	if (app == 0) {
		return 0;
	}
	return app->getFPS();
}