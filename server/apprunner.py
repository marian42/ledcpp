from userapp import UserApp
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