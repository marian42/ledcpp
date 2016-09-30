from flask import *
import thread
import logging
import time
import apps
import json

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

@server.route("/save/<app>/<filename>", methods=['POST'])
def update(app, filename):
	if not app in app_list.keys():
		return 404, "App not found"
	selectedApp = app_list[app]
	file = selectedApp.get_file(filename)
	if file == None:
		return 404, "File not found"
	file.content = request.data
	file.save()
	return "ok"
	
@server.route("/screen/<app>", methods=['GET'])
def get_image(app):
	return server.send_static_file('default.png')

thread.start_new_thread(server.run, (), {'host': '0.0.0.0', 'port': 80})
while True:
	time.sleep(1)