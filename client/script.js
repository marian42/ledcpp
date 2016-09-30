apps = {};

var codeEditor = CodeMirror(document.getElementById("codewrapper"), {
  value: "",
  mode:  "text/x-c++src",
  theme: "base16-dark",
  lineNumbers: true
});

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
		}
	});
}

codeEditor.setSize("100%", "100%");
updateApps();