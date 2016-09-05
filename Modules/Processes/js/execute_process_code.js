native_async("processmanager", "start", JSON.stringify({location: <%= location %>, waitfinish: <%= waitfinish %>, arguments: <%= arguments %>}))!
<%= variable %> = _result()