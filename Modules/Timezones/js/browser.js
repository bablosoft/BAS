function BrowserAutomationStudio_TimezoneRestore()
{
	if(typeof(window.BrowserAutomationStudio_OriginalDate) != "undefined")
	{
		Date = window.BrowserAutomationStudio_OriginalDate
		delete window.BrowserAutomationStudio_OriginalDate
	}
}

function BrowserAutomationStudio_SetTimezone(TimezoneOffset)
{
	if(typeof(Intl.DateTimeFormatOriginal) == "undefined")
	{
		Intl.DateTimeFormatOriginal = Intl.DateTimeFormat()
		Intl.ResolvedOptionsOriginal = Intl.DateTimeFormatOriginal.resolvedOptions();
		delete Intl.ResolvedOptionsOriginal["timeZone"];

		Object.defineProperty(Intl, 'DateTimeFormat', {
	        configurable: true, get: function() {
	             return function(){
	             	var dtres = Intl.DateTimeFormatOriginal;
	             	dtres.resolvedOptions = function()
					{
						return Intl.ResolvedOptionsOriginal;
					}
	             	return dtres;
	             };
	         }
	     });
	}else
	{
		delete Intl.ResolvedOptionsOriginal["timeZone"];		
	}
	
	if(typeof(window.BrowserAutomationStudio_OriginalDate) == "undefined")
		window.BrowserAutomationStudio_OriginalDate = Date;

	function realLocalToUtc(realLocal)
	{
		return new window.BrowserAutomationStudio_OriginalDate(realLocal.getTime() - realLocal.getTimezoneOffset()*60*1000 + TimezoneOffset*60*1000);
	}
	function utcToLocal(utc)
	{
		return new window.BrowserAutomationStudio_OriginalDate(utc.getTime() - TimezoneOffset*60*1000);
	}
	function localToUtc(local)
	{
		return new window.BrowserAutomationStudio_OriginalDate(local.getTime() + TimezoneOffset*60*1000);
	}
	function twoDigit(n)
	{
		if (n < 10)
		{
			return "0" + n;
		}else
		{
			return "" + n;
		}
	}
	function timezoneName()
	{
		var zone = "GMT";
		var offset = Math.abs(TimezoneOffset);
		if (TimezoneOffset < 0) {
			zone = zone + "+";
		} else if (TimezoneOffset > 0) {
			zone = zone + "-";
		} else {
			return zone;
		}
		return zone + twoDigit(Math.floor(offset/60)) + twoDigit(offset%60);
	}

	var ProxyHandler = 
	{
    	get: function(target, name)
    	{
    		if(name in target)
    			return target[name]

        	return Date.prototype[name]
    	}
	};

	Date = function()
	{
	    var res = new window.BrowserAutomationStudio_OriginalDate();

		switch(arguments.length)
		{
			case 0:
				res.utc = new window.BrowserAutomationStudio_OriginalDate();
				break;
			case 1:
				if(typeof(arguments[0]) == "string")
				{
					res.utc = realLocalToUtc(new window.BrowserAutomationStudio_OriginalDate(arguments[0]))
				}
				else
					res.utc = new window.BrowserAutomationStudio_OriginalDate(arguments[0]);
				break;
			case 2:
				res.utc = realLocalToUtc(new window.BrowserAutomationStudio_OriginalDate(arguments[0], arguments[1]));
				break;
			case 3:
				res.utc = realLocalToUtc(new window.BrowserAutomationStudio_OriginalDate(arguments[0], arguments[1], arguments[2]));
				break;
			case 4:
				res.utc = realLocalToUtc(new window.BrowserAutomationStudio_OriginalDate(arguments[0], arguments[1], arguments[2], arguments[3]));
				break;
			case 5:
				res.utc = realLocalToUtc(new window.BrowserAutomationStudio_OriginalDate(arguments[0], arguments[1], arguments[2], arguments[3], arguments[4]));
				break;
			case 6:
				res.utc = realLocalToUtc(new window.BrowserAutomationStudio_OriginalDate(arguments[0], arguments[1], arguments[2], arguments[3], arguments[4], arguments[5]));
				break;
			default:
				res.utc = realLocalToUtc(new window.BrowserAutomationStudio_OriginalDate(arguments[0], arguments[1], arguments[2], arguments[3], arguments[4], arguments[5], arguments[6]));
				break;
		}

	   	res.getDate = function() { return utcToLocal(this.utc).getUTCDate(); }
	   	res.getDay = function() { return utcToLocal(this.utc).getUTCDay(); }
		res.getFullYear = function() { return utcToLocal(this.utc).getUTCFullYear(); }
		res.getHours = function() { return utcToLocal(this.utc).getUTCHours(); }
		res.getMilliseconds = function() { return utcToLocal(this.utc).getUTCMilliseconds(); }
		res.getMinutes = function() { return utcToLocal(this.utc).getUTCMinutes(); }
		res.getMonth = function() { return utcToLocal(this.utc).getUTCMonth(); }
		res.getSeconds = function() { return utcToLocal(this.utc).getUTCSeconds(); }

		res.getUTCDate = function() { return this.utc.getUTCDate(); }
		res.getUTCDay = function() { return this.utc.getUTCDay(); }
		res.getUTCFullYear = function() { return this.utc.getUTCFullYear(); }
		res.getUTCHours = function() { return this.utc.getUTCHours(); }
		res.getUTCMilliseconds = function() { return this.utc.getUTCMilliseconds(); }
		res.getUTCMinutes = function() { return this.utc.getUTCMinutes(); }
		res.getUTCMonth = function() { return this.utc.getUTCMonth(); }
		res.getUTCSeconds = function() { return this.utc.getUTCSeconds(); }

		res.setDate = function() { var d = utcToLocal(this.utc); d.setUTCDate.apply(d, Array.prototype.slice.call(arguments, 0)); this.utc = localToUtc(d); return this.utc.getTime();}
		res.setFullYear = function() { var d = utcToLocal(this.utc); d.setUTCFullYear.apply(d, Array.prototype.slice.call(arguments, 0)); this.utc = localToUtc(d);return this.utc.getTime(); }
		res.setHours = function() { var d = utcToLocal(this.utc); d.setUTCHours.apply(d, Array.prototype.slice.call(arguments, 0)); this.utc = localToUtc(d);return this.utc.getTime(); }
		res.setMilliseconds = function() { var d = utcToLocal(this.utc); d.setUTCMilliseconds.apply(d, Array.prototype.slice.call(arguments, 0)); this.utc = localToUtc(d);return this.utc.getTime(); }
		res.setMinutes = function() { var d = utcToLocal(this.utc); d.setUTCMinutes.apply(d, Array.prototype.slice.call(arguments, 0)); this.utc = localToUtc(d);return this.utc.getTime(); }
		res.setMonth = function() { var d = utcToLocal(this.utc); d.setUTCMonth.apply(d, Array.prototype.slice.call(arguments, 0)); this.utc = localToUtc(d);return this.utc.getTime(); }
		res.setSeconds = function() { var d = utcToLocal(this.utc); d.setUTCSeconds.apply(d, Array.prototype.slice.call(arguments, 0)); this.utc = localToUtc(d);return this.utc.getTime(); }

		res.setUTCDate = function() { this.utc.setUTCDate.apply(this.utc, Array.prototype.slice.call(arguments, 0));return this.utc.getTime(); }
		res.setUTCFullYear = function() { this.utc.setUTCFullYear.apply(this.utc, Array.prototype.slice.call(arguments, 0)); return this.utc.getTime();}
		res.setUTCHours = function() { this.utc.setUTCHours.apply(this.utc, Array.prototype.slice.call(arguments, 0));return this.utc.getTime(); }
		res.setUTCMilliseconds = function() { this.utc.setUTCMilliseconds.apply(this.utc, Array.prototype.slice.call(arguments, 0));return this.utc.getTime(); }
		res.setUTCMinutes = function() { this.utc.setUTCMinutes.apply(this.utc, Array.prototype.slice.call(arguments, 0));return this.utc.getTime(); }
		res.setUTCMonth = function() { this.utc.setUTCMonth.apply(this.utc, Array.prototype.slice.call(arguments, 0));return this.utc.getTime(); }
		res.setUTCSeconds = function() { this.utc.setUTCSeconds.apply(this.utc, Array.prototype.slice.call(arguments, 0));return this.utc.getTime(); }


		res.getYear = function() { return this.getFullYear() - 1900; }
		res.setYear = function(v) { this.setFullYear(v + 1900); return this.utc.getTime(); }

		res.getTime = function() { return this.utc.getTime(); }
		res.setTime = function(v) { this.utc.setTime(v); return this.utc.getTime();}

		res.getTimezoneOffset = function() { return TimezoneOffset; }

		res.toDateString = function() { return utcToLocal(this.utc).toDateString(); }
		res.toLocaleDateString = function() { return utcToLocal(this.utc).toLocaleDateString(); }

		res.toISOString = function() { return this.utc.toISOString(); }
		res.toGMTString = function() { return this.utc.toGMTString(); }
		res.toUTCString = function() { return this.utc.toUTCString(); }

		res.toString = function() {
			var wkdays = ["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"];
			var months = ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"];
			var d = utcToLocal(this.utc);
			var res = wkdays[d.getUTCDay()] + " " + months[d.getUTCMonth()] + " " + twoDigit(d.getUTCDate()) + " " + d.getUTCFullYear() +
				" " + twoDigit(d.getUTCHours()) + ":" + twoDigit(d.getUTCMinutes()) + ":" + twoDigit(d.getUTCSeconds()) + " " + timezoneName();

			return res;
		}
		res.valueOf = function() {return this.utc.getTime();}

		res.toLocaleString = function() { return this.toString(); }
		res.toLocaleTimeString = function() { return this.toString(); }
		res.toTimeString = function() { return this.toString(); }

		res.toJSON = function() { return this.utc.toJSON(); }

	   return new Proxy(res, ProxyHandler);
	}

	Date.prototype = window.BrowserAutomationStudio_OriginalDate.prototype


	Date.now = window.BrowserAutomationStudio_OriginalDate.now;
	Date.parse = window.BrowserAutomationStudio_OriginalDate.parse;
	Date.UTC = window.BrowserAutomationStudio_OriginalDate.UTC;
}


function BrowserAutomationStudio_GeolocationRestore()
{
	delete window.navigator.geolocation.getCurrentPosition
}



function BrowserAutomationStudio_SetGeolocation(Latitude,Longitude)
{
	window.navigator.geolocation.BrowserAutomationStudio_Location = 
	{
		accuracy: 10000,
		altitude: 0,
		altitudeAccuracy: 0,
		latitude: Latitude,
		longitude: Longitude
	}
	Object.defineProperty(window.navigator.geolocation, 'getCurrentPosition', {
	        configurable: true, get: function() {
	             return function(callback){
	             	callback({coords: window.navigator.geolocation.BrowserAutomationStudio_Location, timestamp: Date.now()});
	             };
	         }
	     });

	Object.defineProperty(window.navigator.geolocation, 'watchPosition', {
	        configurable: true, get: function() {
	             return function(callback){
	             	callback({coords: window.navigator.geolocation.BrowserAutomationStudio_Location, timestamp: Date.now()});
	             };
	         }
	     });
}