function BrowserAutomationStudio_ApplyFingerprint()
{
	if(_arguments().length == 0)
		fail("fingerprint is empty")

	FINGERPRINT_JSON = JSON.parse(_arguments())

	if(FINGERPRINT_JSON["valid"] == false)
	{
		var error = "Unknown error"
		if(FINGERPRINT_JSON["message"])
			error = FINGERPRINT_JSON["message"]
		fail("Fingerprint error: \""+ error + "\"") 
	}


	//User agent
	try
	{
		FINGERPRINT_USERAGENT = FINGERPRINT_JSON["ua"] || ""
	}catch(e){FINGERPRINT_USERAGENT = ""}

	_if(FINGERPRINT_USERAGENT.length > 0, function(){
		header("User-Agent", FINGERPRINT_JSON["ua"])!
	})!
	

	// Screen size
	try
	{
		FINGERPRINT_WIDTH = parseInt(FINGERPRINT_JSON["width"])
		FINGERPRINT_HEIGHT = parseInt(FINGERPRINT_JSON["height"])
	}catch(e){FINGERPRINT_HEIGHT = -1;FINGERPRINT_WIDTH = -1}

	
	_if(FINGERPRINT_WIDTH > 0, function(){
		resize(FINGERPRINT_WIDTH, FINGERPRINT_HEIGHT)!
	})!

	//Font
	font_list(FINGERPRINT_JSON["fonts"].join("; "))!

	_if(FINGERPRINT_JSON["dnt"], function(){
		header("DNT","1")!
	})!

	//Headers
	header_order(FINGERPRINT_JSON["headers"])!


	//log(FINGERPRINT_SCRIPT)
	_if(FINGERPRINT_JSON["payload"].length > 0, function(){
		onloadjavascriptinternal(FINGERPRINT_JSON["payload"], "_fingerprint")!
	})!


}


