{
	var split = native("imageprocessing", "find", (<%= id1 %>) + "," + (<%= id2 %>)).split(",")
	<%= x %> = split[0];
	<%= y %> = split[1];
	<%= threshold %> = split[2];
}
