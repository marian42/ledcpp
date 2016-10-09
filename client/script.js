var apps = {};
var selectedApp = null;

var codeEditor = CodeMirror(document.getElementById("codewrapper"), {
  value: "",
  mode:  "text/x-c++src",
  theme: "base16-dark",
  lineNumbers: true
});

codeEditor.on("changes", function() {
	if (selectedApp == null) {
		return;
	}
	selectedApp.modified = true;
	$(selectedApp.domElement).addClass("modified");
});

function selectApp(app) {
	if (selectedApp != null) {
		oldApp = selectedApp;
		selectedApp = null;
		oldApp.files[0].content = codeEditor.getValue();
		$(oldApp.domElement).removeClass("selected");
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
	img.src = "screen/" + app.shortname + "?" + new Date().getTime();
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
					apps[data[i].shortname].modified = false;
				}
			}
			
			if (selectedApp == null && Object.keys(apps).length != 0) {
				selectApp(apps[Object.keys(apps)[0]]);
			}
		}
	});
}

function handleButtonIntent(intent) {
	if (intent == "compile") {
		$('#status').html("Compiling " + selectedApp.shortname + ".cpp...");	
		$.ajax("compile/" + selectedApp.shortname, {
			method: "POST",
			success: function(data) {
				$('#status').html("Compiled successfully.");		
			},
			error: function(data) {
				$('#status').html("Compilation failed.");
			}
		});
	}
	
	if (intent == "run") {
		$('#status').html("Compiling and Running " + selectedApp.shortname + ".cpp...");	
		$.ajax("run/" + selectedApp.shortname, {
			method: "POST",
			success: function(data) {
				$('#status').html("Running " + selectedApp.shortname + ".");
				selectedApp.domElement.childNodes[0].src = "screen/" + selectedApp.shortname + "?" + new Date().getTime();
			},
			error: function(data) {
				$('#status').html("Compilation failed.");
			}
		});
	}
}

function saveFile(intent) {
	if (!selectedApp.modified && intent != "update") {
		handleButtonIntent(intent);
		return;
	}
	
	$('#status').html("Uploading " + selectedApp.shortname + ".cpp...");
	$.ajax("save/" + selectedApp.shortname + "/" + selectedApp.files[0].filename, {
		method: "POST",
		processData: false,
		data: codeEditor.getValue(),
		contentType: 'text/plain',
		success: function(data) {
			$('#status').html("Uploaded " + selectedApp.shortname + ".cpp.");
			selectedApp.modified = false;
			$(selectedApp.domElement).removeClass("modified");
			
			handleButtonIntent(intent);
		},
		error: function() {
			$('#status').html("Uploading failed.");
		}
	});
}

$('#btnUpload').click(function() {saveFile("update")});
$('#btnCompile').click(function() {saveFile("compile")});
$('#btnRun').click(function() {saveFile("run")});
$('#btnStop').click(function() {
	$.ajax("stop", {method: "POST"});
});
$('#btnFadeout').click(function() {
	$.ajax("fadeout", {method: "POST"});
});

codeEditor.setSize("100%", "100%");
updateApps();