{
	var split = native("imageprocessing", "getpixel", (<%= id %>) + "," + (<%= x %>) + "," + (<%= y %>)).split(",")
	<%= variable_r %> = parseInt(split[0])
	<%= variable_g %> = parseInt(split[1])
	<%= variable_b %> = parseInt(split[2])
	<%= variable_a %> = parseInt(split[3])
}