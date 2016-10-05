from PIL import Image
import os
import time

state = "Ready"
compile_output = ""
interface = None

def update_state(value):
	global state
	state = value
	print state

def compile(userapp):
	global compile_output
	
	update_state("Compiling " + userapp.shortname + "...")
	
	compile_output = userapp.compile()
	
	if userapp.compiled_successfully:
		update_state("Compiled " + userapp.shortname + " successfully.")
	else:
		update_state("Errors while compiling " + userapp.shortname + ".")
	return userapp.compiled_successfully
		
def run(userapp):
	global interface
	stop()
	interface = userapp.load_app_interface()
	interface.start()
	
def stop():
	global interface
	if interface == None:
		return
	interface.stop()
	interface = None
	
def save_image(filename):
	pixels = interface.getFrame()
	
	image = Image.new('RGB', (16, 16))
	pixels_out = image.load()
	
	for x in range(16):
		for y in range(16):
			color = (
				ord(pixels[(y * 16 + x) * 3 + 0]),
				ord(pixels[(y * 16 + x) * 3 + 1]),
				ord(pixels[(y * 16 + x) * 3 + 2]))
			pixels_out[x, y] = color
	
	image.save(filename, "PNG")