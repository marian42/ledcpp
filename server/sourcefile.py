import os

class SourceFile:
	def __init__(self, directory, filename):
		self.directory = directory
		self.filename = filename
		self.content = ""
		self.load()
	
	def save(self):
		text_file = open(self.directory + self.filename, "w")
		text_file.write(self.content)
		text_file.close()
		
	def load(self):
		if (os.path.isfile(self.directory + self.filename)):
			with open(self.directory + self.filename, 'r') as file:
				self.content = file.read()
				
	def get_file_name(self):
		return self.directory + self.filename
		
	def get_serializable(self):
		return {
			"filename": self.filename,
			"content": self.content
		}
		
	def load_template(self, index, shortname):
		filename = "cpp/template/"
		if index == 0:
			filename += "App.cpp"
		elif index == 1:
			filename += "LoopApp.cpp"
		elif index == 2:
			filename += "ShaderApp.cpp"
		else:
			return
			
		with open(filename, 'r') as file:
			self.content = file.read().replace("<AppName>", shortname)