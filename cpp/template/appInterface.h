#include "<AppName>.h"
#include <thread>

<AppName>* app = 0;
thread* appThread = 0;

void runAppTask();

extern "C" void start();

extern "C" void stop();

extern "C" void deleteApp();

extern "C" int getFPS();

extern "C" char* getFrame();

long getTime();

void crtAnimation();

extern "C" void fadeout();