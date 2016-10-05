from flask import *
import thread
import logging
import time
import apps
import json
import apprunner
import os
from nocache import nocache

app_list = apps.load_apps()
server = Flask(__name__, static_folder='../client/', static_url_path='')
#log = logging.getLogger('werkzeug')
#log.setLevel(logging.ERROR)

@server.route("/")
def index():
	return server.send_static_file('index.html')

@server.route("/apps", methods=['GET'])
def get_apps():
	return Response(json.dumps([app.get_serializable() for app in app_list.values()]), mimetype='application/json')

@server.route("/save/<app_name>/<filename>", methods=['POST'])
def update(app_name, filename):
	if not app_name in app_list.keys():
		return "App not found", 404
	selectedApp = app_list[app_name]
	file = selectedApp.get_file(filename)
	if file == None:
		return "File not found", 404
	file.content = request.data
	file.save()
	selectedApp.compiled_successfully = False
	return "ok"
	
@server.route("/compile/<app_name>", methods=['POST'])
def compile(app_name):
	if not app_name in app_list.keys():
		return "App not found", 404
	selectedApp = app_list[app_name]
	
	apprunner.stop()
	
	if not apprunner.compile(selectedApp):
		print apprunner.compile_output
		return apprunner.compile_output, 400
	else:
		return "ok"
		
@server.route("/run/<app_name>", methods=['POST'])
def run(app_name):
	if not app_name in app_list.keys():
		return "App not found", 404
	selectedApp = app_list[app_name]
	
	compiled = not selectedApp.compiled_successfully
	if not selectedApp.compiled_successfully:
		apprunner.stop()
		if not apprunner.compile(selectedApp):
			print apprunner.compile_output
			return apprunner.compile_output, 400
	apprunner.stop()
	apprunner.run(selectedApp)
	
	if compiled:
		apprunner.save_image(selectedApp.get_image_filename())
	return "ok"
	
@server.route("/screen/<app_name>", methods=['GET'])
@nocache
def get_image(app_name):
	if not app_name in app_list.keys():
		return "App not found", 404
	selectedApp = app_list[app_name]
	filename = selectedApp.get_image_filename()
	if os.path.isfile(filename):
		return send_from_directory(os.getcwd(), filename)
	else:
		print "not found"
		return flask.send_static_file('default.png')

thread.start_new_thread(server.run, (), {'host': '0.0.0.0', 'port': 80})
while True:
	time.sleep(1)