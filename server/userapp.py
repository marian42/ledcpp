from sourcefile import SourceFile
import configparser
import os
import ctypes
import subprocess
import json
from shutil import copyfile

USERAPPS_DIRECTORY = "cpp/userapps/"
APP_INTERFACE_FILENAME = "appInterface.cpp"
APP_INTERFACE_DIRECTORY = "cpp/template/"

dll_counter = 0

class UserApp:
	def __init__(self, shortname):
		self.shortname = shortname
		self.files = []
		self.compiled_successfully = False
	
	def get_directory(self):
		return USERAPPS_DIRECTORY + self.shortname + "/"
		
	def get_config_filename(self):
		return self.get_directory() + "config.ini"
	
	def initialize(self):
		if not os.path.exists(self.get_directory()):
			os.makedirs(self.get_directory())
		mainFile = SourceFile(self.get_directory(), self.shortname + ".cpp")
		mainFile.save()
		self.create_app_interface()
		self.files = [mainFile]
		self.save()
	
	def save(self):
		config = configparser.ConfigParser()
		config.read(self.get_config_filename())
		if (not "App" in config):
			config["App"] = {}
		config["App"]["name"] = self.name
		config["App"]["compiled_successfully"] = "true" if self.compiled_successfully else "false"
		
		with open(self.get_config_filename(), "w") as configfile:
			config.write(configfile)
			
	def load(self):
		config = configparser.ConfigParser()
		config.read(self.get_config_filename())
		config["DEFAULT"] = {
			"name" : "",
			"compiled_successfully" : "false"
		}
		if (not "App" in config):
			config["App"] = {}
		self.name = config["App"]["name"]
		self.compiled_successfully = config["App"]["compiled_successfully"] == "true"
		
		files = [file for file in os.listdir(self.get_directory()) if os.path.isfile(os.path.join(self.get_directory(), file))]
		
		for file in files:
			if file.endswith(".cpp") and file != APP_INTERFACE_FILENAME:
				sourceFile = SourceFile(self.get_directory(), file)
				sourceFile.load()
				self.files.append(sourceFile)
				
	def create_app_interface(self):
		cpp_template = ""
		with open(APP_INTERFACE_DIRECTORY + APP_INTERFACE_FILENAME, 'r') as file:
			cpp_template = file.read()
		cpp_template = cpp_template.replace("<AppName>", self.shortname)
		text_file = open(self.get_directory() + APP_INTERFACE_FILENAME, "w")
		text_file.write(cpp_template)
		text_file.close()
	
	def get_file(self, filename):
		for sourcefile in self.files:
			if sourcefile.filename == filename:
				return sourcefile
	
	def get_main_file(self):
		return self.get_file(self.shortname + ".cpp")
				
	def compile(self):
		self.create_app_interface()
		command = [
			"gcc",
			"-fPIC",
			self.get_directory() + APP_INTERFACE_FILENAME,
			"-std=c++11",
			"-lstdc++",
			"-shared",
			"-L", "cpp/screen/rpi_ws281x/",
			"-lws2811",
			"-lm",
			"-o", self.get_directory() + "appInterface.so"]
		print " ".join(command)
		shell = subprocess.Popen(
			command,
			stderr = subprocess.PIPE,
			stdout = subprocess.PIPE)
		comm = shell.communicate()
		
		self.compiled_successfully = shell.returncode == 0
		if (self.compiled_successfully):
			self.save()
		
		return comm[1] if len(comm[1]) != 0 else comm[0]
				
	def load_app_interface(self):
		global dll_counter
		filename = self.get_directory() + "bin/" + str(dll_counter) + ".so"
		
		if not os.path.exists(self.get_directory() + "bin/"):
			os.makedirs(self.get_directory() + "bin/")
		
		copyfile(self.get_directory() + "appInterface.so", filename)
		dll_counter += 1
		
		result = ctypes.CDLL(filename)
		return ctypes.CDLL(filename)
		
	def get_serializable(self):
		return {
			"name": self.name,
			"shortname": self.shortname,
			"files": [file.get_serializable() for file in self.files]
		}