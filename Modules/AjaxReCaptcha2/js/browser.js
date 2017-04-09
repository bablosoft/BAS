Object.defineProperty(window, 'grecaptcha', {set: function(value){
	window.BrowserAutomationStudio_GRecaptchaOriginal = value;
	Object.defineProperty(window.BrowserAutomationStudio_GRecaptchaOriginal, 'render', {set: function(value1){
		 window.BrowserAutomationStudio_GRecaptchaRenderOriginal = value1
		 window.BrowserAutomationStudio_GRecaptchaRender = function()
		 {
		 	if(typeof(window.BrowserAutomationStudio_GRecaptchaCallback) == "undefined")
		 		window.BrowserAutomationStudio_GRecaptchaCallback = []

		 	try{
		 		window.BrowserAutomationStudio_GRecaptchaCallback.push(arguments[1]["callback"])
		 	}catch(e){}
		 	return window.BrowserAutomationStudio_GRecaptchaRenderOriginal.apply(this, arguments);
		 }

		}, get: function(){
		 return window.BrowserAutomationStudio_GRecaptchaRender
		}
	})

	Object.defineProperty(window.BrowserAutomationStudio_GRecaptchaOriginal, 'getResponse', {set: function(value1){
		 window.BrowserAutomationStudio_GRecaptchaGetResponseOriginal = value1
		 window.BrowserAutomationStudio_GRecaptchaGetResponse = function()
		 {
		 	if(typeof(window.BrowserAutomationStudio_RecaptchaResult) == "string")
		 	{
		 		return window.BrowserAutomationStudio_RecaptchaResult
		 	}
		 	return window.BrowserAutomationStudio_GRecaptchaGetResponseOriginal.apply(this, arguments);
		 }

		}, get: function(){
		 return window.BrowserAutomationStudio_GRecaptchaGetResponse
		}
	})

}, get: function()
{
	if(typeof(window.BrowserAutomationStudio_GRecaptchaOriginal) != "undefined")
		return BrowserAutomationStudio_GRecaptchaOriginal;
}});

window.BrowserAutomationStudio_RecaptchaSolved = function(result)
{
	try{
		window.BrowserAutomationStudio_RecaptchaResult = result
	}catch(e){}

	try{
		if(typeof(window.BrowserAutomationStudio_GRecaptchaCallback) == "object")
		{
			window.BrowserAutomationStudio_GRecaptchaCallback.forEach(function(resp){
				try{
					resp(result)
				}catch(e){}						
			})
		}
	}catch(e){}		

};