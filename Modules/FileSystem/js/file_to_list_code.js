{
	var d = native("filesystem", "readfile", JSON.stringify({value: <%= value %>,base64:false,from:0,to:0}))
	<%= variable %>	= (d.length == 0) ? [] : d.split(/\r?\n/)
}