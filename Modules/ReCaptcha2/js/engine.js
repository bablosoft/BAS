function NumbersParseRecaptcha2(resp,IS33,IS44,IS42,TOP_PIC,LEFT_PIC,BOTTOM_PIC,RIGHT_PIC,BOTTOM_IMAGE,TOP_IMAGE)
{
	if(typeof(TOP_PIC) == "undefined" || typeof(BOTTOM_IMAGE) == "undefined" || typeof(TOP_IMAGE) == "undefined")
		die("You are using old action. Please recreate Recaptcha2 action.")
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
				var x = parseInt(split[0].split("=")[1])
				var y = parseInt(split[1].split("=")[1])
				if(y <= BOTTOM_IMAGE && y >= TOP_IMAGE)
					CLICKS.push([x,y])
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
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.166),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.166)])
			else if(num == 2)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.5),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.166)])
			else if(num == 3)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.833),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.166)])
			else if(num == 4)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.166),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.5)])
			else if(num == 5)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.5),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.5)])
			else if(num == 6)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.833),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.5)])
			else if(num == 7)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.166),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.833)])
			else if(num == 8)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.5),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.833)])
			else if(num == 9)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.833),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.833)])
		}else if(IS44)
		{
			var num = parseInt(resp[i])
			if(num == 1)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.125),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.125)])
			else if(num == 2)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.375),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.125)])
			else if(num == 3)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.625),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.125)])
			else if(num == 4)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.875),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.125)])

			else if(num == 5)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.125),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.375)])
			else if(num == 6)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.375),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.375)])
			else if(num == 7)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.625),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.375)])
			else if(num == 8)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.875),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.375)])


			else if(num == 9)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.125),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.625)])
			else if(num == 10)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.375),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.625)])
			else if(num == 11)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.625),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.625)])
			else if(num == 12)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.875),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.625)])


			else if(num == 13)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.125),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.875)])
			else if(num == 14)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.375),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.875)])
			else if(num == 15)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.625),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.875)])
			else if(num == 16)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.875),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.875)])
			
		}else if(IS42)
		{
			var num = parseInt(resp[i])
			if(num == 1)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.25),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.125)])
			else if(num == 2)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.75),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.125)])
			
			else if(num == 3)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.25),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.375)])
			else if(num == 4)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.75),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.375)])
			

			else if(num == 5)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.25),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.625)])
			else if(num == 6)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.75),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.625)])
			

			else if(num == 7)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.25),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.875)])
			else if(num == 8)
				CLICKS.push([LEFT_PIC + (RIGHT_PIC - LEFT_PIC) * (0.75),TOP_PIC + (BOTTOM_PIC - TOP_PIC) * (0.875)])
			
		}
	}


	return CLICKS
}