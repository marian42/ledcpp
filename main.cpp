#include <iostream>
#include "Screen.cpp"

using namespace std;

int main( int argc, const char* argv[]) {
	Screen* screen = new Screen();
	screen->frame[4][4].set(128);
	cout << (int)(screen->frame[4][4].r) << endl;
	screen->update();
	cout << "Hello World" << endl;
}