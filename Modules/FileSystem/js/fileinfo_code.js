var json = JSON.parse(native("filesystem", "fileinfo", <%= value %>))
<%= variable_exists %> = json["exists"]
<%= variable_size %> = json["size"]
<%= variable_directory %> = json["directory"]
<%= variable_is_directory %> = json["is_directory"]
<%= variable_last_modified %> = new Date(json["last_modified"] * 1000)
