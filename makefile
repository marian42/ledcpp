all:
	gcc main.cpp -std=c++11 -lstdc++ -L rpi_ws281x/ -lws2811 -lm -o main.o
