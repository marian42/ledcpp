from userapp import UserApp
import apprunner

app = UserApp("TestApp")
app.load()
app.create_app_interface()

if not apprunner.compile(app):
	print apprunner.compile_output
else:
	apprunner.run(app)