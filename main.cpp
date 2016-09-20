#include <iostream>
#include "Screen.cpp"

using namespace std;

int main( int argc, const char* argv[]) {
	Screen* screen = new Screen();
	screen->frame[4][4].set(255);
	screen->update();
	cout << "Hello World" << endl;
}