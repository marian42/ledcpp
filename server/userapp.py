from sourcefile import SourceFile
import configparser
import os
import ctypes
import subprocess
import json
import time
from shutil import copyfile, rmtree

USERAPPS_DIRECTORY = "cpp/userapps/"
TEMPLATE_DIRECTORY = "cpp/template/"

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
	
	def initialize(self, selected_template):
		if not os.path.exists(self.get_directory()):
			os.makedirs(self.get_directory())
		
		template_name = "App"
		if selected_template == 1:
			template_name = "LoopApp"
		if selected_template == 2:
			template_name = "ShaderApp"
		self.create_from_template(template_name + ".h", self.shortname + ".h")
		self.create_from_template(template_name + ".cpp", self.shortname + ".cpp")
		self.create_from_template("CMakeLists.txt")
		self.create_app_interface()
		
		mainFile = SourceFile(self.get_directory(), self.shortname + ".cpp")
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
			if file.endswith(".cpp") and file != "appInterface.cpp":
				sourceFile = SourceFile(self.get_directory(), file)
				sourceFile.load()
				self.files.append(sourceFile)
				
	def create_from_template(self, template_name, target_name = ""):
		if target_name == "":
			target_name = template_name;
		template_lines = ""
		with open(TEMPLATE_DIRECTORY + template_name, 'r') as file:
			template_lines = file.read()
		template_lines = template_lines.replace("<AppName>", self.shortname)
		text_file = open(self.get_directory() + target_name, "w")
		text_file.write(template_lines)
		text_file.close()
		
	def create_app_interface(self):
		self.create_from_template("appInterface.cpp")
		self.create_from_template("appInterface.h")
	
	def get_file(self, filename):
		for sourcefile in self.files:
			if sourcefile.filename == filename:
				return sourcefile
	
	def get_main_file(self):
		return self.get_file(self.shortname + ".cpp")
				
	def compile(self):
		compile_start = time.time()
		
		if not os.path.isfile(self.get_directory() + "Makefile"):
			print "Running cmake..."
			subprocess.call(['cmake', '-G', 'Unix Makefiles'], cwd = self.get_directory())
		
		shell = subprocess.Popen(
			["make"],
			stderr = subprocess.PIPE,
			stdout = subprocess.PIPE,
			cwd = self.get_directory())
		comm = shell.communicate()
		print "Compiled in {:.2f}s.".format(time.time() - compile_start)
		self.compiled_successfully = shell.returncode == 0
		if (self.compiled_successfully):
			self.save()
		compile_output = comm[1] if len(comm[1]) != 0 else comm[0]
		print compile_output
		
		return compile_output
				
	def load_app_interface(self):
		global dll_counter
		filename = self.get_directory() + "bin/" + str(dll_counter) + ".so"
		
		if not os.path.exists(self.get_directory() + "bin/"):
			os.makedirs(self.get_directory() + "bin/")
		
		copyfile(self.get_directory() + "bin/" + self.shortname + ".so", filename)
		dll_counter += 1
		
		result = ctypes.CDLL(filename)
		result.getFrame.argtypes = []
		result.getFrame.restype = ctypes.POINTER(ctypes.c_char)
		return result
		
	def get_serializable(self):
		return {
			"name": self.name,
			"shortname": self.shortname,
			"files": [file.get_serializable() for file in self.files]
		}
		
	def get_image_filename(self):
		return self.get_directory() + "screen.png"
		
	def delete(self):
		rmtree(self.get_directory())