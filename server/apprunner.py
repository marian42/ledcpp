from userapp import UserApp
import subprocess
import os
import ctypes
import time

state = "Ready"
compile_output = ""

def update_state(value):
	global state
	state = value
	print state

def compile(userapp):
	global compile_output
	
	update_state("Compiling " + userapp.shortname + "...")
	command = [
		"gcc",
		"-fPIC",
		userapp.get_directory() + "apprunner.cpp",
		"-std=c++11",
		"-lstdc++",
		"-shared",
		"-L", "cpp/screen/rpi_ws281x/",
		"-lws2811",
		"-lm",
		"-o", userapp.get_directory() + "apprunner.so"]
	shell = subprocess.Popen(
		command,
		stderr = subprocess.PIPE,
		stdout = subprocess.PIPE)
	print " ".join(command)
	
	comm = shell.communicate()
	compile_output = comm[1] if len(comm[1]) != 0 else comm[0]
	
	if (shell.returncode == 0):
		update_state("Compiled " + userapp.shortname + " successfully.")
		return True
	else:
		update_state("Errors while compiling " + userapp.shortname + ".")
		return False
		
def run(userapp):
	interface = ctypes.CDLL(userapp.get_directory() + "apprunner.so")
	interface.start()
	for i in range(10):
		time.sleep(1)
		print interface.getFPS()
	interface.stop()
	
	print "complete"