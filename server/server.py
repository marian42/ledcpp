import flask
import thread
import logging
import time
import apps
import json

app_list = apps.load_apps()
server = flask.Flask(__name__, static_folder='../client/', static_url_path='')
#log = logging.getLogger('werkzeug')
#log.setLevel(logging.ERROR)

@server.route("/")
def index():
	return server.send_static_file('index.html')

@server.route("/apps", methods=['GET'])
def get_apps():
	return flask.Response(json.dumps([app.get_serializable() for app in app_list.values()]), mimetype='application/json')

@server.route("/update", methods=['GET'])
def update(app, code):
	return "ok"
	
@server.route("/screen/<app>", methods=['GET'])
def get_image(app):
	return server.send_static_file('default.png')

thread.start_new_thread(server.run, (), {'host': '0.0.0.0', 'port': 80})
while True:
	time.sleep(1)