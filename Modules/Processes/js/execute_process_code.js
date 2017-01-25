RANDOM_FILE = "temp_" + rand() + ".bat"
native("filesystem", "writefile", JSON.stringify({path: RANDOM_FILE,value: <%= command %>,base64:false,append:false}))
native_async("processmanager", "start", JSON.stringify({location: RANDOM_FILE, waitfinish: <%= waitfinish %>, arguments: ""}))!
<%= variable %> = _result()
sleep(1000)!
native("filesystem", "removefile", RANDOM_FILE)
