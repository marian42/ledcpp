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

function updateApps(appToSelect) {
	$.ajax("apps", {
		success: function(data) {
			for (var i = 0; i < data.length; i++) {
				if (apps[data[i].shortname] == null) {
					apps[data[i].shortname] = data[i];			
					apps[data[i].shortname].domElement = createAppItem(data[i]);
					apps[data[i].shortname].modified = false;
					if (appToSelect != null && data[i].shortname == appToSelect) {
						selectApp(apps[data[i].shortname]);
					}
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
				showCompiler(false);
			},
			error: function(data) {
				$('#status').html("Compilation failed.");
				if (data.responseJSON.compilerMessage != null) {					
					$('#compilerText').text(data.responseJSON.compilerMessage);
					showCompiler(true);
				}
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
				showCompiler(false);
			},
			error: function(data) {
				if (data.responseJSON.compilerMessage != null) {					
					$('#status').html("Compilation failed.");
					$('#compilerText').text(data.responseJSON.compilerMessage);
					showCompiler(true);
				} else {
					$('#status').html("Failed to run app.");
				}
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

function showCompiler(show) {
	$(document.body).removeClass(show ? "nocompiler" : "compiler");
	$(document.body).addClass(show ? "compiler" : "nocompiler");
}

var selectedTemplate = 2;

function templateSelectorClick(event) {
	var element = event.target;
	selectedTemplate = $($(element)[0].parentNode.parentNode.children).index($(element)[0].parentNode);
	$('#btnTemplateText').text($(event.target).text());
}

function createApp() {
	var name = $('#inputAppName').val();
	var shortName = $('#inputShortName').val();
	$('#createAppForm').slideUp();
	
	$.ajax("create", {
		method: "POST",
		data: {
			template: selectedTemplate,
			name: name,
			shortName: shortName
		},
		success: function(data) {
			$('#status').html("Created " + shortName + ".cpp.");
			$('#inputAppName').val('');
			$('#inputShortName').val('');
			updateApps(shortName);
		},
		error: function(data) {
			$('#createAppForm').slideDown();
			$('#status').html(data.responseText);
		}
	});
}

$('#btnUpload').click(function() {saveFile("update");});
$('#btnCompile').click(function() {saveFile("compile");});
$('#btnRun').click(function() {saveFile("run");});
$('#btnStop').click(function() {
	$.ajax("stop", {method: "POST"});
});
$('#btnFadeout').click(function() {
	$.ajax("fadeout", {method: "POST"});
});
$('#btnCompiler').click(function() {showCompiler($(document.body).hasClass("nocompiler"));});
$('#btnHideCompiler').click(function() {showCompiler(false);});

$('#btnShowCreateApp').click(function() { $('#createAppForm').slideDown(); });
$('#btnHideCreateApp').click(function() { $('#createAppForm').slideUp(); });
$('#btnCreateApp').click(createApp);

codeEditor.setSize("100%", "100%");
updateApps();