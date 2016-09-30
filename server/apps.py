from userapp import UserApp
import os

APP_DIRECTORY = "cpp/userapps"

app_list = {}

def load_apps():
	global app_list

	subfolders = [subfolder for subfolder in os.listdir(APP_DIRECTORY) if os.path.isdir(os.path.join(APP_DIRECTORY, subfolder))]
		
	for subfolder in subfolders:
		userapp = UserApp(subfolder)
		userapp.load()
		app_list[subfolder] = userapp
	
	return app_list