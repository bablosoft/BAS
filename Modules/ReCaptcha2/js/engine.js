function NumbersParseRecaptcha2(resp,IS33,IS44,IS42)
{
	var CLICKS = []
	if(resp.indexOf("coordinates:") >= 0 || resp.indexOf("coordinate:") >= 0)
	{
		resp = resp.split(":")[1]
		resp = resp.split(";")
		for(var i = 0;i<resp.length;i++)
		{
			if(resp[i].length>0)
			{
				var split = resp[i].split(",")
				CLICKS.push([parseInt(split[0].split("=")[1]),parseInt(split[1].split("=")[1])])
			}
		}
		return CLICKS
	}


	if(/^\d+$/.test(resp))
	{
		resp = resp.split("")
	}else
	{
		resp = resp.split(/[\s,]+/)
	}
	
	for(var i = 0;i<resp.length;i++)
	{
		if(IS33)
		{
			var num = parseInt(resp[i])
			if(num == 1)
				CLICKS.push([62,182])
			else if(num == 2)
				CLICKS.push([192,182])
			else if(num == 3)
				CLICKS.push([321,182])
			else if(num == 4)
				CLICKS.push([62,307])
			else if(num == 5)
				CLICKS.push([192,307])
			else if(num == 6)
				CLICKS.push([321,307])
			else if(num == 7)
				CLICKS.push([62,432])
			else if(num == 8)
				CLICKS.push([192,432])
			else if(num == 9)
				CLICKS.push([321,432])
		}else if(IS44)
		{
			var num = parseInt(resp[i])
			if(num == 1)
				CLICKS.push([60,175])
			else if(num == 2)
				CLICKS.push([154,175])
			else if(num == 3)
				CLICKS.push([250,175])
			else if(num == 4)
				CLICKS.push([343,175])

			else if(num == 5)
				CLICKS.push([60,268])
			else if(num == 6)
				CLICKS.push([154,268])
			else if(num == 7)
				CLICKS.push([250,268])
			else if(num == 8)
				CLICKS.push([343,268])


			else if(num == 9)
				CLICKS.push([60,365])
			else if(num == 10)
				CLICKS.push([154,365])
			else if(num == 11)
				CLICKS.push([250,365])
			else if(num == 12)
				CLICKS.push([343,365])


			else if(num == 13)
				CLICKS.push([60,465])
			else if(num == 14)
				CLICKS.push([154,465])
			else if(num == 15)
				CLICKS.push([250,465])
			else if(num == 16)
				CLICKS.push([343,465])
			
		}else if(IS42)
		{
			var num = parseInt(resp[i])
			if(num == 1)
				CLICKS.push([110,175])
			else if(num == 2)
				CLICKS.push([290,175])
			
			else if(num == 3)
				CLICKS.push([110,268])
			else if(num == 4)
				CLICKS.push([290,268])
			

			else if(num == 5)
				CLICKS.push([110,365])
			else if(num == 6)
				CLICKS.push([290,365])
			

			else if(num == 7)
				CLICKS.push([110,465])
			else if(num == 8)
				CLICKS.push([290,465])
			
		}
	}


	return CLICKS
}