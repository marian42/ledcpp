from sourcefile import SourceFile
import configparser
import os

USERAPPS_DIRECTORY = "cpp/userapps/"

class UserApp:
	def __init__(self, shortname):
		self.shortname = shortname
		self.files = []
	
	def get_directory(self):
		return USERAPPS_DIRECTORY + self.shortname + "/"
		
	def get_config_filename(self):
		return self.get_directory() + "config.ini"
	
	def initialize(self):
		if not os.path.exists(self.get_directory()):
			os.makedirs(self.get_directory())
		mainFile = SourceFile(self.get_directory(), self.shortname + ".cpp")
		mainFile.save()
		self.files = [mainFile]
		self.save()
	
	def save(self):
		config = configparser.ConfigParser()
		if (not "App" in config):
			config["App"] = {}
		config["App"]["name"] = self.name
		
		with open(self.get_config_filename(), "w") as configfile:
			config.write(configfile)
			
	def load(self):
		config = configparser.ConfigParser()
		config.read(self.get_config_filename())
		self.name = config["App"]["name"]
		
		files = [file for file in os.listdir(self.get_directory()) if os.path.isfile(os.path.join(self.get_directory(), file))]
		
		for file in files:
			if file.endswith(".cpp"):
				sourceFile = SourceFile(self.get_directory(), file)
				sourceFile.load()
				self.files.append(sourceFile)