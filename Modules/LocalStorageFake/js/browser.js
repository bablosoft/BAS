function BrowserAutomationStudio_InjectLocalStorageArray(res)
{
				Object.defineProperty(res, "length",{
	   	 	 		get: function() {
	   	 	 			return Object.keys(res).filter(function(k) {return ["length","key","getItem","setItem","removeItem","clear"].indexOf(k) < 0}).length;
	   	 	 		}
	   	 	 	})	
	   	 	 	res["key"] = function(number)
	   	 	 	{
	   	 	 		return Object.keys(res).filter(function(k) {return ["length","key","getItem","setItem","removeItem","clear"].indexOf(k) < 0})[number];
	   	 	 	}
	   	 	 	res["getItem"] = function(key)
	   	 	 	{
	 	 			if(Object.keys(res).filter(function(k) {return ["length","key","getItem","setItem","removeItem","clear"].indexOf(k) < 0}).indexOf(key) < 0)
	 	 			{
	 	 				return null
	 	 			}
	 	 			return res[key]
	   	 	 	}	

	   	 	 	res["setItem"] = function(key, value)
	   	 	 	{
	 	 			if(typeof(value) == "undefined")
	 	 				value = "undefined"

	 	 			switch (value) {
			        	case null:
			          	value = "null";
			          break;
			        	default:
			          		value = value.toString();
				      }

				      if (res[key] === value)
				      {
				        return;
				      }
					res[key] = value;

					BrowserAutomationStudio_SaveLocalStorage(JSON.stringify(window.BrowserAutomationStudio_LocalStorages));
	   	 	 	}

	   	 	 	res["removeItem"] = function(key)
	   	 	 	{
					if (res[prop])
		 			{
						var r = delete res[prop];
						BrowserAutomationStudio_SaveLocalStorage(JSON.stringify(window.BrowserAutomationStudio_LocalStorages));
						return r
					}
	   	 	 	}

	   	 	 	res["clear"] = function()
	   	 	 	{
		 	 		for (var prop in res)
		 	 		{
					   if (res.hasOwnProperty(prop))
					   {
	    					delete res[prop];
					   }
					}
					BrowserAutomationStudio_SaveLocalStorage(JSON.stringify(window.BrowserAutomationStudio_LocalStorages));
		 	 	
	   	 	 	}
}

function BrowserAutomationStudio_InitLocalStorage()
{
	if(typeof(window.BrowserAutomationStudio_LocalStorages) != "undefined")
		return;

	window.BrowserAutomationStudio_LocalStorages = new Object()

	Object.defineProperty(window, 'localStorage', {
	   	 get: function() {
			var parser = document.createElement('a'), searchObject = {}, queries, split, i;
	        parser.href = window.location.href;
	        queries = parser.search.replace(/^\?/, '').split('&');
			for( i = 0; i < queries.length; i++ ) {
	    		split = queries[i].split('=');
	    		searchObject[split[0]] = split[1];
			}
			var url = parser.protocol + "//" +  parser.host + ((parser.port.length > 0) ? ":" + parser.port : "")
			if(!(url in window.BrowserAutomationStudio_LocalStorages))
			{
				var res = new Object()
				BrowserAutomationStudio_InjectLocalStorageArray(res)

				window.BrowserAutomationStudio_LocalStorages[url] = res
			}
			
			return window.BrowserAutomationStudio_LocalStorages[url]
	     }
	 });
}

function BrowserAutomationStudio_RestoreLocalStorage(data)
{
	BrowserAutomationStudio_InitLocalStorage();
	if(data.length == 0)
	{
		window.BrowserAutomationStudio_LocalStorages = new Object()
		return;
	}

	window.BrowserAutomationStudio_LocalStorages = JSON.parse(data)

	for (var site in window.BrowserAutomationStudio_LocalStorages)
	{
		if (window.BrowserAutomationStudio_LocalStorages.hasOwnProperty(site))
		{
			BrowserAutomationStudio_InjectLocalStorageArray(window.BrowserAutomationStudio_LocalStorages[site])
		}
	}
}
