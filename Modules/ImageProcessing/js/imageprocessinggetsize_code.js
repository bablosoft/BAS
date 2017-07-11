{
	var split = native("imageprocessing", "getsize", <%= id %>).split(",")
	<%= variable_width %> = parseInt(split[0])
	<%= variable_height %> = parseInt(split[1])
}