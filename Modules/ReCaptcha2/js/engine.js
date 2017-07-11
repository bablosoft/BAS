function NumbersParseRecaptcha2(resp,IS33,IS44,IS42,TOP_PIC,LEFT_PIC,BOTTOM_PIC,RIGHT_PIC,BOTTOM_IMAGE,TOP_IMAGE)
{
	if(typeof(TOP_PIC) == "undefined" || typeof(BOTTOM_IMAGE) == "undefined" || typeof(TOP_IMAGE) == "undefined")
		die("You are using old action. Please recreate Recaptcha2 action.")
	var CLICKS = []
	if(resp.indexOf("coordinates:") >= 0 || resp.indexOf("coordinate:") >= 0)
	{
		resp = resp.split(":")
		resp = resp[resp.length - 1]

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

BAS_CAPMONSTER_IMAGE_ID = 0

function BAS_CapmonsterUpdateImage()
{
	_if(BAS_SolveRecaptcha_Method == "capmonsterimage", function(){
   		cache_get_base64("recaptcha/api2/payload")!		

   		var image_id = native("imageprocessing","load",_result())
   		var image_size = native("imageprocessing","getsize",image_id)
		var image_w = parseInt(image_size.split(",")[0])
		var image_h = parseInt(image_size.split(",")[1])

		if(image_h == 0)
			fail("Recaptcha 2 image cache is empty, use Cache Mask Allow action before page with captcha load.")

   		if(image_h > 200)
   		{
   			if(BAS_CAPMONSTER_IMAGE_ID != 0)
   				native("imageprocessing","delete",BAS_CAPMONSTER_IMAGE_ID)
   			BAS_CAPMONSTER_IMAGE_ID = image_id

   		}else
   		{
   			var image_size = native("imageprocessing","getsize",BAS_CAPMONSTER_IMAGE_ID)
			var image_w = parseInt(image_size.split(",")[0])
			var image_h = parseInt(image_size.split(",")[1])
   			

   			var x = 0;
   			var y = 0;
   			var wx = 1;
   			var wy = 1;

   			var resp = RECAPTCHA2_RESULT

   			if(/^\d+$/.test(resp))
			{
				resp = resp.split("")
			}else
			{
				resp = resp.split(/[\s,]+/)
			}

   			var index = parseInt(resp[BAS_CAPMONSTER_SOLVE_INDEX-1]) - 1

   			if(IS33)
   			{
   				wx = 3;
   				wy = 3;
   			}
   			if(IS44)
   			{
   				wx = 4;
   				wy = 4;
   			}
   			if(IS42)
   			{
   				wx = 2;
   				wy = 4;
   			}
   			
   			x = index % wx
   			y = Math.floor(index / wx)

   			x = Math.floor(image_w/wx) * x
   			y = Math.floor(image_h/wy) * y


   			native("imageprocessing","insert",BAS_CAPMONSTER_IMAGE_ID + "," + image_id + "," + x + "," + y)
			native("imageprocessing","delete",image_id)

   			
   		}
   		
	})!
 


}

function BAS_SolveRecaptcha()
{

	solver_properties_clear(BAS_SolveRecaptcha_Method.replace("-newapi",""))

	if(BAS_SolveRecaptcha_Method == "rucaptcha")
	{
	  solver_property("rucaptcha","coordinatescaptcha","1")
	  rucaptcha(BAS_SolveRecaptcha_Rucaptcha)
	}
	if(BAS_SolveRecaptcha_Method == "2captcha")
	{
	  solver_property("2captcha","coordinatescaptcha","1")
	  twocaptcha(BAS_SolveRecaptcha_Rucaptcha)
	}

	if(BAS_SolveRecaptcha_Method == "rucaptcha-newapi")
	{
	  solver_property("rucaptcha","bas_disable_image_convert","1")
	  rucaptcha(BAS_SolveRecaptcha_Rucaptcha)
	}
	if(BAS_SolveRecaptcha_Method == "2captcha-newapi")
	{
	  solver_property("2captcha","bas_disable_image_convert","1")
	  twocaptcha(BAS_SolveRecaptcha_Rucaptcha)
	}

	if(BAS_SolveRecaptcha_Method == "antigate")
	{
	  antigate(BAS_SolveRecaptcha_Rucaptcha)
	}
	if(BAS_SolveRecaptcha_Method == "dbc")
	{
	  dbc(BAS_SolveRecaptcha_Rucaptcha)
	}
	if(BAS_SolveRecaptcha_Method == "capmonsterimage" || BAS_SolveRecaptcha_Method == "capmonsteraudio" || BAS_SolveRecaptcha_Method == "capmonster")
	{
	  solver_property("capmonster","bas_disable_image_convert","1")
	  solver_property("capmonster","serverurl",BAS_SolveRecaptcha_Serverurl)
	  capmonster(BAS_SolveRecaptcha_Rucaptcha)
	}
	_if(BAS_SolveRecaptcha_Method == "capmonsterimage" || BAS_SolveRecaptcha_Method == "capmonsteraudio"  || BAS_SolveRecaptcha_Method == "capmonster", function(){
	  cache_allow("recaptcha/api2/payload")!
	})!
	cache_allow("recaptcha/api2/userverify")!


	BAS_SolveRecaptcha_Path().script("document.getElementById('rc-imageselect') != null")!
	RECAPTCHA_IS_INVISIBLE = _result() == "true"
	_if(!RECAPTCHA_IS_INVISIBLE, function(){
		cache_data_clear()!
	})!


	
	RECAPTCHA_PREFIX = (BAS_SolveRecaptcha_Query)
	RECAPTCHA_PREFIX_FIRST_FRAME = RECAPTCHA_PREFIX

	{
	  var index = RECAPTCHA_PREFIX.toString().lastIndexOf(">FRAME>")
	  if(index >= 0)
	    RECAPTCHA_PREFIX = RECAPTCHA_PREFIX.substring(0,index)
	
	  RECAPTCHA_PREFIX_FIRST_FRAME = RECAPTCHA_PREFIX
		
	  
	  index = RECAPTCHA_PREFIX.toString().lastIndexOf(">FRAME>")
	  if(index >= 0)
	    RECAPTCHA_PREFIX = RECAPTCHA_PREFIX.substring(0,index + ">FRAME>".length)
	  else
	    RECAPTCHA_PREFIX = ""
	}

	
    

	RECAPTCHA2_FIRST_TIME = true
	RECAPTCHA2_SOLVED = false

	_call(BAS_SolveRecaptcha_Waiter,null)!
	BAS_SolveRecaptcha_Path().exist()!
	if(_result() != "1")
		_break()

	_if_else(BAS_SolveRecaptcha_Method == "2captcha-newapi" || BAS_SolveRecaptcha_Method == "rucaptcha-newapi" || BAS_SolveRecaptcha_Method == "antigate-newapi", function(){
	    get_element_selector(RECAPTCHA_PREFIX_FIRST_FRAME).attr("src")!

	    NEWAPI_DATA_SITEKEY = _result().split(new RegExp("[\?\&]k="))
	    NEWAPI_DATA_SITEKEY = NEWAPI_DATA_SITEKEY[NEWAPI_DATA_SITEKEY.length - 1]
	    NEWAPI_DATA_SITEKEY = NEWAPI_DATA_SITEKEY.split("&")[0]
	    NEWAPI_DATA_SITEKEY = NEWAPI_DATA_SITEKEY.split("#")[0]

	    if(NEWAPI_DATA_SITEKEY.length == 0)
	    {
	      fail("data-sitekey is empty")
	    }
	    url()!
	    NEWAPI_URL = _result()
	    NEWAPI_METHOD = (BAS_SolveRecaptcha_Method).replace("-newapi","")


		NEWAPI_RES = ""

		_if_else(BAS_SolveRecaptcha_Method == "antigate-newapi", function(){
			_switch_http_client_internal()
			var data = JSON.stringify({"clientKey":BAS_SolveRecaptcha_Rucaptcha,softId:"784","task":{"type":"NoCaptchaTaskProxyless","websiteURL":NEWAPI_URL,"websiteKey":NEWAPI_DATA_SITEKEY}})
			http_client_post("https://api.anti-captcha.com/createTask", ["data",data], {"content-type":("custom"), "encoding":("UTF-8"), "method":("POST")})!
			var resp = JSON.parse(http_client_content())
			if(resp["errorId"]!==0)
				fail(resp["errorDescription"])

			NEWAPI_TASK_ID = parseInt(resp["taskId"])

			_do(function(){

				if(_iterator() > 60)
	            	fail("Recaptcha 2 antigate wait res timeout")
				var data = JSON.stringify({"clientKey":BAS_SolveRecaptcha_Rucaptcha,"taskId":NEWAPI_TASK_ID})
				http_client_post("https://api.anti-captcha.com/getTaskResult", ["data",data], {"content-type":("custom"), "encoding":("UTF-8"), "method":("POST")})!

				var resp = JSON.parse(http_client_content())

				if(resp["errorId"]!==0)
					fail(resp["errorDescription"])

				if(resp["status"] === "ready")
				{
					NEWAPI_RES = resp["solution"]["gRecaptchaResponse"]
					_break()
				}


	            sleep(5000)!

			})!
			
			_switch_http_client_main()

		}, function(){
			solver_property(NEWAPI_METHOD,"method","userrecaptcha")
		    solver_property(NEWAPI_METHOD,"googlekey",NEWAPI_DATA_SITEKEY)
		    solver_property(NEWAPI_METHOD,"pageurl",NEWAPI_URL)

	   	    solve_base64(NEWAPI_METHOD, "")!
		    NEWAPI_RES = _result()
		})!


		get_element_selector(RECAPTCHA_PREFIX).script("Array.prototype.slice.call(document.getElementsByClassName('g-recaptcha-response')).forEach(function(el){el.value = " + JSON.stringify(NEWAPI_RES) + "});BrowserAutomationStudio_RecaptchaSolved(" + JSON.stringify(NEWAPI_RES) + ");")!

		get_element_selector(RECAPTCHA_PREFIX).script("document.getElementsByClassName('g-recaptcha')[0].getAttribute('data-callback')")!
		_if(_result().length > 0, function(){
			get_element_selector(RECAPTCHA_PREFIX).script(_result() + '(' + JSON.stringify(NEWAPI_RES) + ");")!
		})!
	    


	}, function(){


	_if(!RECAPTCHA_IS_INVISIBLE, function(){

	  _do(function(){
	       if(_iterator() > 60)
	          fail("Recaptcha image load timeout")
	        
	          BAS_SolveRecaptcha_Path().script("document.getElementById('recaptcha-anchor').className.indexOf('recaptcha-checkbox-unchecked') >= 0")!
	          if(_result() == "true")
	          {
	            RECAPTCHA2_SOLVED = false
	            _break()
	          }

	          sleep(1000)!
	  })!
	  BAS_SolveRecaptcha_Path().move()!
	  cache_data_clear()!
	  BAS_SolveRecaptcha_Path().system_click()!
	  _do(function(){
	       if(_iterator() > 60)
	          fail("Recaptcha frame load timeout")
	        
          	  get_element_selector(RECAPTCHA_PREFIX_FIRST_FRAME).script("var el = Array.prototype.slice.call(document.getElementsByTagName('iframe')).find(function(el){return(el.src.indexOf('api2/bframe')>=0 && getComputedStyle(el)['visibility'] == 'visible')});if(el){el=el['name']}else{el=''};el;")!
          	  if(_result().length>0)
          	  {
				RECAPTCHA_PREFIX_SECOND_FRAME = RECAPTCHA_PREFIX + ">CSS>iframe[name=\"" + _result() + "\"]" + ">FRAME> >CSS> body"
				RECAPTCHA_PREFIX_SECOND_FRAME_ELEMENT = RECAPTCHA_PREFIX + ">CSS>iframe[name=\"" + _result() + "\"]"
				_break()
          	  }

          	  is_load("recaptcha/api2/userverify")!
              _if(_result(),function(){
            	cache_get_string("recaptcha/api2/userverify")!
            	RECAPTCHA2_SOLVED = _result().indexOf('"bgdata"') < 0
            	_break(2)

              })!

	          sleep(1000)!
	  })!
	})!



	_if(RECAPTCHA_IS_INVISIBLE, function(){
		RECAPTCHA_PREFIX_SECOND_FRAME = BAS_SolveRecaptcha_Query

		RECAPTCHA_PREFIX_SECOND_FRAME_ELEMENT = RECAPTCHA_PREFIX_SECOND_FRAME

		var index = RECAPTCHA_PREFIX_SECOND_FRAME_ELEMENT.toString().lastIndexOf(">FRAME>")
		  if(index >= 0)
		    RECAPTCHA_PREFIX_SECOND_FRAME_ELEMENT = RECAPTCHA_PREFIX_SECOND_FRAME_ELEMENT.substring(0,index)

	})!

	  _if_else(BAS_SolveRecaptcha_Method == "capmonsteraudio", function(){

	      _do(function(){

	      	if(RECAPTCHA2_SOLVED)
	      	{
	      		native("imageprocessing","delete",BAS_CAPMONSTER_IMAGE_ID)
	        	_break()
	        }


	        _do(function(){
	           if(_iterator() > 60)
	              fail("Recaptcha 2 wait timeout")


	            get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementById('recaptcha-verify-button').className.indexOf('rc-button-default-disabled') < 0")!
	            if(_result() == "true")
	            {
	              RECAPTCHA2_SOLVED = false
	              _break()
	            }

	            is_load("recaptcha/api2/userverify")!
	            _if(_result(),function(){
	            	cache_get_string("recaptcha/api2/userverify")!
	            	RECAPTCHA2_SOLVED = _result().indexOf('"bgdata"') < 0
	            	_break(2)

	            })!
	      	
	            sleep(1000)!
	        })!
	        

	      if(RECAPTCHA2_SOLVED)
	      {
	      	native("imageprocessing","delete",BAS_CAPMONSTER_IMAGE_ID)
	        _break()
	      }

	      if(_iterator() > BAS_SolveRecaptcha_TimeToSolve)
	        fail("Too many fails solve recaptcha 2")

	      _if(RECAPTCHA2_FIRST_TIME, function(){

	        _do(function(){
	         if(_iterator() > 60)
	            fail("Recaptcha image load timeout")
	          
	            get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementsByClassName('rc-imageselect-dynamic-selected').length")!
	            if(_result() == "0")
	              _break()

	            sleep(1000)!
	        })!

	        _do(function(){
	           if(_iterator() > 60)
	              fail("Recaptcha 2 audio button wait timeout")

	            get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementById('recaptcha-audio-button').getBoundingClientRect().top")!
	            TOP_BUTTON = parseInt(_result())

	            get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementById('recaptcha-audio-button').getBoundingClientRect().left")!
	            LEFT_BUTTON = parseInt(_result())

	            if(TOP_BUTTON > 300)
	              _break()
	        })!

	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME_ELEMENT).script("self.getBoundingClientRect().top + scrolly + positiony")!
	        TOP = parseInt(_result())

	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME_ELEMENT).script("self.getBoundingClientRect().left + scrollx + positionx")!
	        LEFT = parseInt(_result())

	        move(LEFT + LEFT_BUTTON + 12, TOP + TOP_BUTTON + 12)!
	        cache_data_clear()!
	        mouse(LEFT + LEFT_BUTTON + 12, TOP + TOP_BUTTON + 12)!
	      })!

	      RECAPTCHA2_FIRST_TIME = false
	      RECAPTCHA2_TYPE = ""

	      _do(function(){
	         if(_iterator() > 60)
	            fail("Recaptcha type detection timeout")
	          
	            is_load("recaptcha/api2/payload")!

	            if(_result())
	            {
	              RECAPTCHA2_TYPE = "audio"
	              _break()
	            }

	            get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementsByClassName('rc-text-instructions').length")!

	            if(parseInt(_result()) > 0)
	            {
	              RECAPTCHA2_TYPE = "associations"
	              _break()
	            }

	            sleep(1000)!
	        })!


	      _if(RECAPTCHA2_TYPE == "audio", function(){
	        cache_get_base64("recaptcha/api2/payload")!
	        solver_property("capmonster","CapMonsterModule","ZennoLab.AudioReCaptcha")
	        solve_base64("capmonster", _result())!

	        RECAPTCHA2_RESULT = _result()

	        if(RECAPTCHA2_RESULT.indexOf("133193320491090004119440") >= 0)
	        {
	          fail("Your IP was banned!")
	        }

	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementById('audio-response').getBoundingClientRect().top")!
	        TOP_BUTTON = parseInt(_result())

	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementById('audio-response').getBoundingClientRect().left")!
	        LEFT_BUTTON = parseInt(_result())

	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME_ELEMENT).script("self.getBoundingClientRect().top + scrolly + positiony")!
	        TOP = parseInt(_result())

	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME_ELEMENT).script("self.getBoundingClientRect().left + scrollx + positionx")!
	        LEFT = parseInt(_result())

	        move(LEFT + LEFT_BUTTON + 12, TOP + TOP_BUTTON + 12)!
	        mouse(LEFT + LEFT_BUTTON + 12, TOP + TOP_BUTTON + 12)!

	        page().type(RECAPTCHA2_RESULT,100)!

	      })!


	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementById('recaptcha-verify-button').getBoundingClientRect().top")!
	        TOP_BUTTON = parseInt(_result())

	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementById('recaptcha-verify-button').getBoundingClientRect().left")!
	        LEFT_BUTTON = parseInt(_result())

	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME_ELEMENT).script("self.getBoundingClientRect().top + scrolly + positiony")!
	        TOP = parseInt(_result())
	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME_ELEMENT).script("self.getBoundingClientRect().left + scrollx + positionx")!
	        LEFT = parseInt(_result())

	        move(LEFT + LEFT_BUTTON + 50, TOP + TOP_BUTTON + 15)!
	        cache_data_clear()!
	        mouse(LEFT + LEFT_BUTTON + 50, TOP + TOP_BUTTON + 15)!

	      
	     
	    })!

	  },function(){

	    _do(function(){


	      if(RECAPTCHA2_SOLVED)
	      {
	      	native("imageprocessing","delete",BAS_CAPMONSTER_IMAGE_ID)
	        _break()
	      }
	      
	      _do(function(){
	         if(_iterator() > 60)
	            fail("Recaptcha 2 wait timeout")

	          get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementById('recaptcha-verify-button').className.indexOf('rc-button-default-disabled') < 0")!
	          if(_result() == "true")
	          {
	            RECAPTCHA2_SOLVED = false
	            _break()
	          }

	          is_load("recaptcha/api2/userverify")!
              _if(_result(),function(){
            	cache_get_string("recaptcha/api2/userverify")!
            	RECAPTCHA2_SOLVED = _result().indexOf('"bgdata"') < 0
            	_break(2)

              })!


	          sleep(1000)!
	      })!

	      if(RECAPTCHA2_SOLVED)
	      {
	      	native("imageprocessing","delete",BAS_CAPMONSTER_IMAGE_ID)
	        _break()
	      }

	      _do(function(){
	         if(_iterator() > 60)
	            fail("Recaptcha image load timeout")
	          
	            get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementsByClassName('rc-imageselect-dynamic-selected').length")!
	            if(_result() == "0")
	              _break()

	            sleep(1000)!
	      })!



	      get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("window.getComputedStyle(document.getElementsByClassName('rc-imageselect-incorrect-response')[0])['display']")!
	      _if(_result() != "none" && !RECAPTCHA2_SOLVED, function(){
	        solver_failed()
	        wait_load("recaptcha/api2/payload")!
	      })!
	        

	      if(_iterator() > BAS_SolveRecaptcha_TimeToSolve)
	        fail("Too many fails solve recaptcha 2")


	      _if(RECAPTCHA2_FIRST_TIME, function(){
	        RECAPTCHA2_FIRST_TIME = false
	        wait_load("recaptcha/api2/payload")!

	      })!

	      sleep(3000)!

	      get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME_ELEMENT).focus()!
	      
	      _do(function(){

	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementsByClassName('rc-imageselect-table-44').length")!
	        IS44 = parseInt(_result()) > 0

	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementsByClassName('rc-imageselect-table-33').length")!
	        IS33 = parseInt(_result()) > 0
	        
	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementsByClassName('rc-imageselect-table-42').length")!
	        IS42 = parseInt(_result()) > 0


	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementsByClassName('rc-imageselect-tileselected').length")!
	        RECAPTCHA2_TOTAL_SELECTED = parseInt(_result())

	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementsByClassName('rc-imageselect-error-select-more')[0].getAttribute('style') == null")!
	        RECAPTCHA2_SELECT_MORE = _result() == "true"
	        

	        if(!(RECAPTCHA2_TOTAL_SELECTED>0 || RECAPTCHA2_SELECT_MORE || /*IS44 && (BAS_SolveRecaptcha_Method == "capmonsterimage" || BAS_SolveRecaptcha_Method == "capmonster") ||*/ (!IS33 && !IS44 && !IS42)))
	          _break()

	        if(_iterator() > 10)
	            fail("Too many recaptcha 2 reloads")

	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementById('recaptcha-reload-button').getBoundingClientRect().top")!
	        TOP_RECAPTCHA_RELOAD_BUTTON = parseInt(_result())

	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementById('recaptcha-reload-button').getBoundingClientRect().left")!
	        LEFT_RECAPTCHA_RELOAD_BUTTON = parseInt(_result())

	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME_ELEMENT).script("self.getBoundingClientRect().top + scrolly + positiony")!
	        TOP = parseInt(_result())

	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME_ELEMENT).script("self.getBoundingClientRect().left + scrollx + positionx")!
	        LEFT = parseInt(_result())

	        move(LEFT + LEFT_RECAPTCHA_RELOAD_BUTTON + 12, TOP + TOP_RECAPTCHA_RELOAD_BUTTON + 12)!
	        cache_data_clear()!
	        mouse(LEFT + LEFT_RECAPTCHA_RELOAD_BUTTON + 12, TOP + TOP_RECAPTCHA_RELOAD_BUTTON + 12)!

	        wait_load("recaptcha/api2/payload")!

	        
	        sleep(3000)!

	      })!

	      get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementsByClassName('rc-imageselect-payload')[0].getBoundingClientRect().bottom")!
	      BOTTOM_IMAGE = parseInt(_result())

	      get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementsByClassName('rc-imageselect-challenge')[0].getBoundingClientRect().top")!
	      TOP_IMAGE = parseInt(_result())

	      get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementsByClassName('rc-imageselect-table-44').length")!
	      IS44 = parseInt(_result()) > 0

	      get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementsByClassName('rc-imageselect-table-33').length")!
	      IS33 = parseInt(_result()) > 0

	      get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementsByClassName('rc-imageselect-table-42').length")!
	      IS42 = parseInt(_result()) > 0

	      if(!IS33 && !IS44 && !IS42)
	      {
	        fail("Unknown captcha type")
	      }

	      _if_else(BAS_SolveRecaptcha_Method == "capmonsterimage" || BAS_SolveRecaptcha_Method == "capmonster", function(){
	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("(function(){var tmp = document.createElement('DIV');tmp.innerHTML = document.getElementsByClassName('rc-imageselect-desc-wrapper')[0].innerHTML.split('<br>')[0];return tmp.textContent})()")!
	        solver_property("capmonster","Task",_result())
	        solver_property("capmonster","CapMonsterModule","ZennoLab.ReCaptcha2")
	        _call(BAS_CapmonsterUpdateImage,null)!
	        solve_base64_no_fail("capmonster", native("imageprocessing","getdata",BAS_CAPMONSTER_IMAGE_ID))!
	        if(_result().indexOf("ERROR_CAPTCHA_UNSOLVABLE") >= 0)
	        {
	          RECAPTCHA2_RESULT = ""
	        }else if(_result().indexOf("CAPTCHA_FAIL") >= 0)
	        {
	          fail(_result())
	        }else
	        {
	          RECAPTCHA2_RESULT = _result()
	        }
	      },function(){
	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME_ELEMENT).render_base64()!

	        
	        if(BAS_SolveRecaptcha_Method == "rucaptcha" || BAS_SolveRecaptcha_Method == "2captcha")
	        {
	        	var previousID = ""
	        	var can_no_answer = ""
		        if(typeof(CAPTCHA_TYPE_DYNAMIC) != "undefined" && CAPTCHA_TYPE_DYNAMIC && typeof(LAST_CAPTCHA_ID) != "undefined")
		        {
		        	previousID = LAST_CAPTCHA_ID;
		        	can_no_answer = "1"
		        }
		        solver_property(BAS_SolveRecaptcha_Method, "previousID", previousID)
		        solver_property(BAS_SolveRecaptcha_Method, "can_no_answer", can_no_answer)
		    }

	        solve_base64_no_fail(BAS_SolveRecaptcha_Method, _result())!
	        if(_result().indexOf("ERROR_CAPTCHA_UNSOLVABLE") >= 0)
	        {
	          RECAPTCHA2_RESULT = ""
	        }else if(_result().indexOf("CAPTCHA_FAIL") >= 0)
	        {
	          fail(_result())
	        }else
	        {
	          RECAPTCHA2_RESULT = _result()
	        }
	      })!

	      get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementById('rc-imageselect-target').getBoundingClientRect().top")!
	      TOP_PIC = parseInt(_result())

	      get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementById('rc-imageselect-target').getBoundingClientRect().bottom")!
	      BOTTOM_PIC = parseInt(_result())

	      get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementById('rc-imageselect-target').getBoundingClientRect().left")!
	      LEFT_PIC = parseInt(_result())

	      get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementById('rc-imageselect-target').getBoundingClientRect().right")!
	      RIGHT_PIC = parseInt(_result())

	      
	      CLICKS = NumbersParseRecaptcha2(RECAPTCHA2_RESULT,IS33,IS44,IS42,TOP_PIC,LEFT_PIC,BOTTOM_PIC,RIGHT_PIC,BOTTOM_IMAGE,TOP_IMAGE)
	      
	      get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME_ELEMENT).script("window.getComputedStyle(self)['visibility']")!
	      if(_result() == "hidden")
	        fail("Captcha not visible") 


	      CAPTCHA_TYPE_DYNAMIC = false


	      _do(function(){
	        if(_iterator() > CLICKS.length)
	          _break(1)

	      	BAS_CAPMONSTER_SOLVE_INDEX = _iterator()


	        cache_data_clear()!

	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementsByClassName('rc-imageselect-tileselected').length")!
	        RECAPTCHA2_TOTAL_SELECTED = parseInt(_result())

	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME_ELEMENT).script("self.getBoundingClientRect().top + scrolly + positiony")!
	        TOP = parseInt(_result())
	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME_ELEMENT).script("self.getBoundingClientRect().left + scrollx + positionx")!
	        LEFT = parseInt(_result())

	        move(LEFT + CLICKS[_iterator() - 1][0],TOP + CLICKS[_iterator() - 1][1])!
	        mouse(LEFT + CLICKS[_iterator() - 1][0],TOP + CLICKS[_iterator() - 1][1])!

	        _do(function(){
	         if(_iterator() > 30)
	            fail("Failed to wait select responce")
	          
	            get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementsByClassName('rc-imageselect-tileselected').length")!
	            if(RECAPTCHA2_TOTAL_SELECTED != parseInt(_result()))
	              _break()

	            is_load("recaptcha/api2/payload")!
	            _if(_result(), function(){
				  CAPTCHA_TYPE_DYNAMIC = true
	              _call(BAS_CapmonsterUpdateImage,null)!
	              _break(2)
	            })!
	            
	            sleep(1000)!
	        })!

	      })!

	      sleep(1000)!

	      _if(!CAPTCHA_TYPE_DYNAMIC, function(){

	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementById('recaptcha-verify-button').getBoundingClientRect().top")!
	        TOP_RECAPTCHA_VERIFY_BUTTON = parseInt(_result())

	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME).script("document.getElementById('recaptcha-verify-button').getBoundingClientRect().left")!
	        LEFT_RECAPTCHA_VERIFY_BUTTON = parseInt(_result())

	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME_ELEMENT).script("self.getBoundingClientRect().top + scrolly + positiony")!
	        TOP = parseInt(_result())
	        get_element_selector(RECAPTCHA_PREFIX_SECOND_FRAME_ELEMENT).script("self.getBoundingClientRect().left + scrollx + positionx")!
	        LEFT = parseInt(_result())

	        move(LEFT + LEFT_RECAPTCHA_VERIFY_BUTTON + 50, TOP + TOP_RECAPTCHA_VERIFY_BUTTON + 15)!
	        cache_data_clear()!
	        mouse(LEFT + LEFT_RECAPTCHA_VERIFY_BUTTON + 50, TOP + TOP_RECAPTCHA_VERIFY_BUTTON + 15)!

	      	

	      

	      })!
	      
	    })!

	  })!



	})!

}