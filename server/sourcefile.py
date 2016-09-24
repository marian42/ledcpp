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