#include "App.h"
#include <chrono>
#include <math.h>

long App::getMillis() {
	auto time = std::chrono::system_clock::now();
	auto since_epoch = time.time_since_epoch();
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch);
	return millis.count();
}

void App::updateTime() {
	this->millis = getMillis() - this->startTimeMillis;
	this->time = this->millis * 0.001;
	this->deltaT = this->millis - this->lastUpdate;
	this->lastDeltaT[this->frameCount % this->FPS_AVERAGE_COUNT] = this->deltaT;
	this->lastUpdate = this->millis;
}

void App::update() {
	Screen::getInstance().update(this->frame);
	this->updateTime();
	this->frameCount++;
	
	if (this->stopped) {
		throw InterruptException();
	}
}

App::App() {
	this->frameCount = 0;
	this->lastUpdate = 0;
	this->stopped = false;
	this->startTimeMillis = getMillis();
}

void App::stop() {
	this->stopped = true;
}

long App::getDeltaT() {
	return this->deltaT;
}

int App::getFPS() {
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

Frame& App::getFrame() {
	while (this->frameCount == 0);
	return this->frame;
}