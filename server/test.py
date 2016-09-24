from userapp import UserApp
import apprunner

app = UserApp("TestApp")
app.load()

apprunner.compile(app)
print apprunner.compile_output
apprunner.run(app)