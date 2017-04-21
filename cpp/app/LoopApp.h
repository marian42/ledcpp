#ifndef LOOPAPP_H
#define LOOPAPP_H

#include "App.h"

class LoopApp : public App {
protected:
	virtual void setup() {}
	
	virtual void loop() = 0;
public:
	void run();
};

#endif