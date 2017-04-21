#include "appInterface.h"

void runAppTask() {
	try {
		app->run();
	}
	catch(InterruptException exception) { }
}

void start() {
	if (app != 0) {
		return;
	}
	
	app = new <AppName>();
	appThread = new thread(runAppTask);
}

void stop() {
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

void deleteApp() {
	if (app != 0) {		
		delete app;
	}
}

int getFPS() {
	if (app == 0) {
		return 0;
	}
	return app->getFPS();
}

char* getFrame() {
	return app->getFrame().getPixelArray();
}

long getTime() {
	auto time = std::chrono::system_clock::now();
	auto since_epoch = time.time_since_epoch();
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch);
	return millis.count();
}

void crtAnimation() {
	Frame frame;
	const int duration = 500;
	long start = getTime();
	while (true) {
		float progress = (float)(getTime() - start) / duration;
		Color white = Color(255, 255, 255);
		frame.clear();
		if (progress < 0.5) {
			float progress1 = progress * 2.0;
			for (int x = 0; x < 16; x++) {
				for (int y = 0; y < 16; y++) {
					int ySource = 8 + (int)((y - 8.0) / (1.0 - progress1));
					if (ySource >= 0 && ySource < 16) {
						frame[x][y].blend(app->getFrame()[x][ySource], white, pow(progress1, 2.0));
					}
				}
			}
		} else {
			float progress2 = (progress - 0.5) * 2.0;
			for (int x = 0; x < 16; x++) {
				frame[x][8].set(clamp((7 - abs(x - 8)) - progress2 * 8.0, 0.0, 1.0) * 255.0);
			}
		}
		Screen::getInstance().update(frame);
		if (progress >= 1.0) {
			frame.clear();
			Screen::getInstance().update(frame);
			return;
		}
	}
}

void fadeout() {
	stop();
	
	if (app == 0) {
		Frame frame;
		Screen::getInstance().update(frame);
		return;
	}
	
	crtAnimation();
}