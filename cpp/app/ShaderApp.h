#ifndef SHADERAPP_H
#define SHADERAPP_H

#include "LoopApp.h"

class ShaderApp : public LoopApp {
protected:
	virtual void mainImage(Color& color, int x, int y) = 0;

	void loop();
};

#endif