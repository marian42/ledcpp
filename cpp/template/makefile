CC=gcc
CFLAGS=-fPIC -std=c++11 -lstdc++ -L ../../screen/rpi_ws281x/ -lws2811 -lm

DEPS = appInterface.h
DEPS += <AppName>.h
DEPS += ../../app/App.h
DEPS += ../../app/helpers.h
DEPS += ../../app/LoopApp.h
DEPS += ../../app/ShaderApp.h
DEPS += ../../app/Simplex.h
DEPS += ../../screen/Color.h
DEPS += ../../screen/Frame.h
DEPS += ../../screen/Screen.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(DEPS:.h=.o)
	gcc -shared -o bin/<AppName>.so $^ $(CFLAGS)