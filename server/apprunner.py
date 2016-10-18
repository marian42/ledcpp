from PIL import Image
import os
import time
import StringIO

state = "Ready"
compile_output = ""
interface = None
running = False
current_app = None

def reset_state():
	global state
	if running:
		state = "Running " + current_app.name + "."
	else:
		state = "Ready."

def update_state(value):
	global state
	state = value
	print state

def compile(userapp):
	global compile_output	
	update_state("Compiling " + userapp.name + "...")
	
	compile_output = userapp.compile()
	
	reset_state()
	return userapp.compiled_successfully
		
def run(userapp):
	global interface
	global running
	global current_app
	stop()
	interface = userapp.load_app_interface()
	interface.start()
	running = True
	current_app = userapp
	reset_state()
	
def stop():
	global running
	if interface != None and running:
		interface.stop()
	running = False
	reset_state()
	
def fadeout():
	global running
	running = False
	if interface != None:
		interface.fadeout()
	reset_state()

def get_image():
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
	return image
	
def save_image(filename):
	image = get_image()
	image.save(filename, "PNG")
	
def image_stream():
    while True:
		while not running:
			time.sleep(0.1)
		image = get_image()
		output = StringIO.StringIO()
		image.save(output, "PNG")
		image_string = output.getvalue()
		output.close()
		
		yield (b'--frame\r\n'
			b'Content-Type: image/png\r\n\r\n' + image_string + b'\r\n')
			
def get_status():   
	result = {}
	result["state"] = state
	result["app"] = None if current_app == None else current_app.shortname
	result["fps"] = None if not running else interface.getFPS()
	return result
	
reset_state()