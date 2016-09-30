var codeEditor = CodeMirror(document.getElementById("codewrapper"), {
  value: "",
  mode:  "text/x-c++src",
  theme: "base16-dark",
  lineNumbers: true
});

codeEditor.setSize("100%", "100%");