from flask import *
from userapp import UserApp
import thread
import logging
import time
import apps
import json
import apprunner
import os
from nocache import nocache
import string

app_list = apps.load_apps()
server = Flask(__name__, static_folder='../client/', static_url_path='')
log = logging.getLogger('werkzeug')
log.setLevel(logging.ERROR)

@server.route("/")
def index():
	return server.send_static_file('index.html')

@server.route("/apps", methods=['GET'])
def get_apps():
	return Response(json.dumps([app.get_serializable() for app in app_list.values()]), mimetype='application/json')

@server.route("/save/<app_name>", methods=['POST'])
def update(app_name):
	if not app_name in app_list.keys():
		return "App not found", 404
	selectedApp = app_list[app_name]
	file = selectedApp.source_file
	file.content = request.data
	file.save()
	selectedApp.compiled_successfully = False
	return "ok"
	
def get_compiler_json(message):
	result = {}
	result["compilerMessage"] = message
	return Response(json.dumps(result), mimetype='application/json', status = 400)
	
@server.route("/compile/<app_name>", methods=['POST'])
def compile(app_name):
	if not app_name in app_list.keys():
		return "App not found", 404
	selectedApp = app_list[app_name]
	
	apprunner.stop()
	
	if not apprunner.compile(selectedApp):
		print apprunner.compile_output
		return get_compiler_json(apprunner.compile_output)
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
			return get_compiler_json(apprunner.compile_output)
	apprunner.stop()
	apprunner.run(selectedApp)
	
	if compiled or True:
		apprunner.save_image(selectedApp.get_image_filename())
	return "ok"
	
@server.route("/stop", methods=['POST'])
def stop():
	apprunner.stop()
	return "ok"
	
@server.route("/fadeout", methods=['POST'])
def fadeout():
	apprunner.fadeout()
	return "ok"
	
@server.route("/screen/<app_name>", methods=['GET'])
@nocache
def get_image(app_name):
	if not app_name in app_list.keys():
		return server.send_static_file('default.png')
	selectedApp = app_list[app_name]
	filename = selectedApp.get_image_filename()
	if os.path.isfile(filename):
		return send_from_directory(os.getcwd(), filename)
	else:
		return server.send_static_file('default.png')

@server.route("/stream", methods=['GET'])
def stream():
	return Response(apprunner.image_stream(), mimetype='multipart/x-mixed-replace; boundary=frame')

@server.route("/status", methods=['GET'])
def status():
	return Response(json.dumps(apprunner.get_status()), mimetype='application/json', status = 200)

	
@server.route("/create", methods=['POST'])
def create_app():
	selected_template = int(request.form["template"])
	name = request.form["name"]
	short_name = request.form["shortName"]
	
	if short_name in app_list:
		return "An app with this file name alread exists.", 400		
	if len(short_name) < 3:
		return "File name too short.", 400
	if selected_template < 0 or selected_template > 2:
		return "Unknown template selected.", 400
	if any((not char in string.letters + string.digits) for char in short_name):
		return "File name may only contain letters or digits", 400
	
	new_app = UserApp(short_name)
	new_app.name = name
	new_app.initialize(selected_template)
	app_list[short_name] = new_app
		
	return "ok"
	
@server.route("/delete/<app_name>", methods=['POST'])
def delete_app(app_name):
	if not app_name in app_list.keys():
		return "App not found", 404
	selectedApp = app_list[app_name]
	selectedApp.delete()
	
	del app_list[selectedApp.shortname]	
	return "ok"
	
	
thread.start_new_thread(server.run, (), {'host': '0.0.0.0', 'port': 80, 'threaded': True})
while True:
	time.sleep(1)