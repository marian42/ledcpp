from PIL import Image
import os
import time
import StringIO

state = "Ready"
compile_output = ""
interface = None
running = False

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
	global running
	stop()
	interface = userapp.load_app_interface()
	interface.start()
	running = True
	
def stop():
	global interface
	global running
	running = False
	if interface == None:
		return
	interface.stop()
	interface = None

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
		while interface == None or not running:
			time.sleep(0.1)
		image = get_image()
		output = StringIO.StringIO()
		image.save(output, "PNG")
		image_string = output.getvalue()
		output.close()
		
		yield (b'--frame\r\n'
			b'Content-Type: image/png\r\n\r\n' + image_string + b'\r\n')
		