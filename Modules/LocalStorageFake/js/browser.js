function BrowserAutomationStudio_InjectLocalStorageArray(res, domain)
{

				Object.defineProperty(res, "length",{
	   	 	 		get: function() {
	   	 	 			//console.log("length = " + Object.keys(localStorage).filter(function(k) {return ["length","key","getItem","setItem","removeItem","clear"].indexOf(k) < 0}).length)
	   	 	 			return Object.keys(localStorage).filter(function(k) {return ["length","key","getItem","setItem","removeItem","clear"].indexOf(k) < 0}).length;
	   	 	 		}
	   	 	 	})	
	   	 	 	res["key"] = function(number)
	   	 	 	{
	   	 	 		var all = Object.keys(res).filter(function(k) {return ["length","key","getItem","setItem","removeItem","clear"].indexOf(k) < 0});
	   	 	 		if(number>=0 && number< all.length)
	   	 	 		{
		   	 	 		//console.log("key[" + number + "] = " + all[number])
		   	 	 		return all[number];
	   	 	 		}
	   	 			//console.log("key[" + number + "] = null")
	   				return null
	   	
	   	 	 	}
	   	 	 	res["getItem"] = function(key)
	   	 	 	{
	 	 			if(Object.keys(res).filter(function(k) {return ["length","key","getItem","setItem","removeItem","clear"].indexOf(k) < 0}).indexOf(key) < 0)
	 	 			{
		   	 	 		//console.log("getItem[" + key + "] = null")
	 	 				return null
	 	 			}
	 	 			//console.log("getItem[" + key + "] = " + res[key])
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


	   	 	 		var item = {type: "set", key: key, value: value, domain: domain, frame: window.BrowserAutomationStudio_LocalStoragesFrameId, time: Date.now().toString()}
					window.BrowserAutomationStudio_LocalStoragesData.push(item)
					BrowserAutomationStudio_SaveLocalStorage("set", key, value, domain, window.BrowserAutomationStudio_LocalStoragesFrameId, Date.now().toString());

					if (res[key] !== value)
					{
						//console.log("setItem[" + key + "] = " + value)
						res[key] = value;
					}
					
	   	 	 	}

	   	 	 	res["removeItem"] = function(key)
	   	 	 	{
	   	 	 		var item = {type: "remove", key: key, value: "", domain: domain, frame: window.BrowserAutomationStudio_LocalStoragesFrameId, time: Date.now().toString()}
					window.BrowserAutomationStudio_LocalStoragesData.push(item)
					BrowserAutomationStudio_SaveLocalStorage("remove", key, "", domain, window.BrowserAutomationStudio_LocalStoragesFrameId, Date.now().toString());

					if (res[key])
		 			{
						delete res[key];
					}
	   	 	 	}

	   	 	 	res["clear"] = function()
	   	 	 	{
	   	 	 		var item = {type: "cleardomain", key: "", value: "", domain: domain, frame: window.BrowserAutomationStudio_LocalStoragesFrameId, time: Date.now().toString()}
					window.BrowserAutomationStudio_LocalStoragesData.push(item)
					BrowserAutomationStudio_SaveLocalStorage("cleardomain", "", "", domain, window.BrowserAutomationStudio_LocalStoragesFrameId, Date.now().toString());

		 	 		for (var prop in res)
		 	 		{
					   if (res.hasOwnProperty(prop))
					   {
	    					delete res[prop];
					   }
					}
		 	 	
	   	 	 	}
	   	 	 	var ProxyHandler = 
				{
					get: function(target, key)
			    	{
			    		//console.log(key)
			    		//return target.getItem(key)
			    		return target[key]
			    	},
			    	set: function(target, key, value)
			    	{
			    		target.setItem(key, value)
			    	}
				};
	   	 	 	return new Proxy(res, ProxyHandler)
}

function BrowserAutomationStudio_InitLocalStorage()
{
	if(typeof(window.BrowserAutomationStudio_LocalStorages) != "undefined")
		return;

	window.BrowserAutomationStudio_LocalStoragesData = []
	window.BrowserAutomationStudio_LocalStorages = new Object()
	window.BrowserAutomationStudio_LocalStoragesFrameId = Math.floor(Math.random() * (100000))

	Object.defineProperty(window, 'localStorage', {
	   	 get: function() {
	   	 	//console.trace("get local storage")
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
				res = BrowserAutomationStudio_InjectLocalStorageArray(res, url)

				window.BrowserAutomationStudio_LocalStorages[url] = res
			}
			
			return window.BrowserAutomationStudio_LocalStorages[url]
	     }
	 });
}

function BrowserAutomationStudio_GenerateLocalStorage()
{
	window.BrowserAutomationStudio_LocalStoragesData.sort(function(a, b) {
	  return parseInt(a.time) - parseInt(b.time);
	});
	
	window.BrowserAutomationStudio_LocalStorages = new Object()

	for(var i = 0;i < window.BrowserAutomationStudio_LocalStoragesData.length;i++)
	{
		var item = window.BrowserAutomationStudio_LocalStoragesData[i]
		if(item["type"] == "set")
		{
			var domain = window.BrowserAutomationStudio_LocalStorages[item["domain"]]
			if(typeof(domain) == "undefined" || !domain)
			{
				domain = new Object()
			}

			domain[item["key"]] = item["value"]

			window.BrowserAutomationStudio_LocalStorages[item["domain"]] = domain
		}
		if(item["type"] == "remove")
		{
			var domain = window.BrowserAutomationStudio_LocalStorages[item["domain"]]
			if(typeof(domain) == "undefined" || !domain)
			{
				domain = new Object()
			}

			delete domain[item["key"]];

			window.BrowserAutomationStudio_LocalStorages[item["domain"]] = domain
		}
		if(item["type"] == "cleardomain")
		{
			delete window.BrowserAutomationStudio_LocalStorages[item["domain"]]
		}
		if(item["type"] == "clearall")
		{
			window.BrowserAutomationStudio_LocalStorages = new Object()
		}
	}

	for (var site in window.BrowserAutomationStudio_LocalStorages)
	{
		if (window.BrowserAutomationStudio_LocalStorages.hasOwnProperty(site))
		{
			window.BrowserAutomationStudio_LocalStorages[site] = BrowserAutomationStudio_InjectLocalStorageArray(window.BrowserAutomationStudio_LocalStorages[site], site)
		}
	}
}

function BrowserAutomationStudio_UpdateLocalStorage(type, key, value, domain, frame, time)
{
	BrowserAutomationStudio_InitLocalStorage();

	//console.log(JSON.stringify([type, key, value, domain, frame, time]))
	if(frame != window.BrowserAutomationStudio_LocalStoragesFrameId)
	{
		window.BrowserAutomationStudio_LocalStoragesData.push({type:type, key:key, value:value, domain:domain, frame:frame, time:time})
		BrowserAutomationStudio_GenerateLocalStorage();
	}
}


function BrowserAutomationStudio_RestoreLocalStorage(data)
{
	if(data == "" || data == '""')
	{
		data = "[]"
	}
	BrowserAutomationStudio_InitLocalStorage();

	window.BrowserAutomationStudio_LocalStoragesData = JSON.parse(data)
	BrowserAutomationStudio_GenerateLocalStorage();
}
