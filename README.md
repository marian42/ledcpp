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

# Known issues

The user written C++ code is run directly within the python server.
Whenever the user code causes an error, the entire server crashes and needs to be restarted manually.
That's annoying and I'm working on a solution.
