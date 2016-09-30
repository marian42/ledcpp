var apps = {};
var selectedApp = null;

var codeEditor = CodeMirror(document.getElementById("codewrapper"), {
  value: "",
  mode:  "text/x-c++src",
  theme: "base16-dark",
  lineNumbers: true
});

function selectApp(app) {
	if (selectedApp != null) {
		selectedApp.files[0].content = codeEditor.getValue();
		$(selectedApp.domElement).removeClass("selected");
	}
	
	codeEditor.setValue(app.files[0].content);
	$(app.domElement).addClass("selected");
	selectedApp = app;
}

function createAppItem(app) {
	var sidebar = $(".sidebar")[0];
	var item = document.createElement("div");
	item.className = "appitem";
	
	var img = document.createElement("img");
	img.src = "screen/" + app.shortname;
	img.className = "appscreen";
	item.appendChild(img);
	
	var title = document.createElement("div");
	title.className = "apptitle";
	title.appendChild(document.createTextNode(app.name));
	item.appendChild(title);
	
	var shortname = document.createElement("div");
	shortname.className = "appshortname";
	shortname.appendChild(document.createTextNode(app.shortname + ".cpp"));
	item.appendChild(shortname);	
	
	sidebar.appendChild(item);
	
	$(item).click(function() {
		selectApp(app);
	})
	
	return item;
}

function updateApps() {
	$.ajax("apps", {
		success: function(data) {
			for (var i = 0; i < data.length; i++) {
				if (apps[data[i].shortname] == null) {
					apps[data[i].shortname] = data[i];					
					apps[data[i].shortname].domElement = createAppItem(data[i]);
				}
			}
			
			if (selectedApp == null && Object.keys(apps).length != 0) {
				selectApp(apps[Object.keys(apps)[0]]);
			}
		}
	});
}

codeEditor.setSize("100%", "100%");
updateApps();