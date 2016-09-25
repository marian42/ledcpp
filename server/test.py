from userapp import UserApp
import apprunner

app = UserApp("TestApp")
app.load()

if not apprunner.compile(app):
	print apprunner.compile_output
else:
	apprunner.run(app)