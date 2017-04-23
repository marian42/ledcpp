![Screenshot](https://i.imgur.com/dB2leW9.png)

# About

This project provides a web interface for a hardware 16x16 LED matrix where users can quickly and easily program simple animations which are then played on the LED matrix.
The goal is to provide a similar experience to [Shadertoy](https://shadertoy.com).

# Prerequisites
This software is meant to run on a Raspberry Pi with 256 WS2812 LEDs.
It makes use of the [rpi_ws281x](https://github.com/jgarff/rpi_ws281x) library.
Adafruit has a [good tutorial](https://learn.adafruit.com/neopixels-on-raspberry-pi?view=all) on how to set up the hardware for these LEDs.
You should be able to run the `strandtest.py` example as described in the tutorial before using this software.
The setup assumes that you use the default configuration of the `rpi_ws281x` library (GPIO pin 18).
If your setup is different, please edit `cpp/screen/Screen.cpp`.

# Installation

1. Clone this repository:
```
git clone --recursive https://github.com/marian42/ledcpp
```
Note that you need to clone recursively in order to initialize the submodule.

2.  Go to the `ws281x` library and build:
```
cd ledcpp/cpp/screen/rpi_ws281x
scons
```

# Usage

From within the project root directory, run `sudo python server/server.py`

Use a webbrowser to go to the IP address of your Raspberry Pi and you should see the web interface.

# Writing apps
There are three templates of apps you can choose from:
1. `ShaderApp` Inspired by fragment shaders, you implement a function that computes a color given the screen position.
It is called for every pixel, every frame.
2. `LoopApp` You implement a method that is called once per frame and draws something on the screen.
3. `App` You have control over timing and you write the draw loop yourself.

## Color
The color class is mutable. Its values can be changed like this:

```
color.r = 128;                // 0 .. 255
color.rgb(255, 255, 0);       // 0 .. 255
color.hsv(10, 255, 255);      // all values 0 .. 255
color.gray(255);              // grayscale
color.hue(0);                 // fully saturated colors
color.blend(c1, c2, progress);// progress 0 .. 1
color.set(color)              // copy existing color
```

## Math and convenience methods
These common methods are available:
```
min, max, map, fract, clamp, modulo
```

And some more specialized ones:
```
float getRadius(int x, int y);        // distance from (8,8)
float getAngle(int x, int y);         // angle around the center, in radians
float map(float value, float oldLow, float oldHigh, float newLow, float newHigh);
float noise(float x, float y);        // Simplex noise
int getRing(int x, int y);            // distance from (8,8) counting concentric square rings
int getRingPosition(int x, int y);    // position of the pixel within its ring
```
In addition, you can use everything from `cmath`, write your own functions or include other libraries.

# Known issues

The user written C++ code is run directly within the python server.
Whenever the user code causes an error, the entire server crashes and needs to be restarted manually.
That's annoying and I'm working on a solution.
