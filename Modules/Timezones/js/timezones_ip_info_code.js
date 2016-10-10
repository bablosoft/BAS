var json = JSON.parse(native("timezones", "ipinfo", <%= value %>))
<%= variable_valid %> = json["valid"]
<%= variable_country %> = json["country"]
<%= variable_city %> = json["city"]
<%= variable_latitude %> = json["latitude"]
<%= variable_longitude %> = json["longitude"]
<%= variable_timezone %> = json["timezone"]
<%= variable_offset %> = json["offset"]
<%= variable_dst_offset %> = json["dstoffset"]