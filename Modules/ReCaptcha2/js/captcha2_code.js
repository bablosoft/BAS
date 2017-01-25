/*Browser*/
solver_properties_clear(<%= method %>.replace("-newapi",""))

if(<%= method %> == "rucaptcha")
{
  solver_property("rucaptcha","coordinatescaptcha","1")
  rucaptcha(<%= rucaptcha %>)
}
if(<%= method %> == "2captcha")
{
  solver_property("2captcha","coordinatescaptcha","1")
  twocaptcha(<%= rucaptcha %>)
}

if(<%= method %> == "rucaptcha-newapi")
{
  solver_property("rucaptcha","bas_disable_image_convert","1")
  rucaptcha(<%= rucaptcha %>)
}
if(<%= method %> == "2captcha-newapi")
{
  solver_property("2captcha","bas_disable_image_convert","1")
  twocaptcha(<%= rucaptcha %>)
}

if(<%= method %> == "antigate")
{
  antigate(<%= rucaptcha %>)
}
if(<%= method %> == "dbc")
{
  dbc(<%= rucaptcha %>)
}
if(<%= method %> == "capmonsterimage" || <%= method %> == "capmonsteraudio" || <%= method %> == "capmonster")
{
  solver_property("capmonster","bas_disable_image_convert","1")
  solver_property("capmonster","serverurl",<%= serverurl %>)
  capmonster(<%= rucaptcha %>)
}

_if(<%= method %> == "capmonsterimage" || <%= method %> == "capmonsteraudio"  || <%= method %> == "capmonster", function(){
  cache_allow("recaptcha/api2/payload")!
})!

<% 
   var prefix = path
   var frame_index = path.lastIndexOf("frame_css")
   var frame_math_index = path.lastIndexOf("frame_match")
   if(frame_math_index > frame_index)
    frame_index = frame_math_index
   if(frame_index > 0)
   {
    prefix = prefix.substring(0,frame_index-1)
   }else
   {
    prefix = ""
   }
   if(prefix.length > 0)
   {
    prefix += "."
   }

 %>

RECAPTCHA2_FIRST_TIME = true

<%= waiter %>


_if_else(<%= method %> == "2captcha-newapi" || <%= method %> == "rucaptcha-newapi", function(){
    <%= prefix %>match("google.com/recaptcha/api2/anchor").attr("src")!

    NEWAPI_DATA_SITEKEY = _result().split("?k=")
    NEWAPI_DATA_SITEKEY = NEWAPI_DATA_SITEKEY[NEWAPI_DATA_SITEKEY.length - 1]
    NEWAPI_DATA_SITEKEY = NEWAPI_DATA_SITEKEY.split("&")[0]

    if(NEWAPI_DATA_SITEKEY.length == 0)
    {
      fail("data-sitekey is empty")
    }
    url()!
    NEWAPI_URL = _result()
    NEWAPI_METHOD = (<%= method %>).replace("-newapi","")
    solver_property(NEWAPI_METHOD,"method","userrecaptcha")
    solver_property(NEWAPI_METHOD,"googlekey",NEWAPI_DATA_SITEKEY)
    solver_property(NEWAPI_METHOD,"pageurl",NEWAPI_URL)

    solve_base64(NEWAPI_METHOD, "")!

    <%= prefix %>script("Array.prototype.slice.call(document.getElementsByClassName('g-recaptcha-response')).forEach(function(el){el.value = " + JSON.stringify(_result()) + "});")!


}, function(){

  _do(function(){
       if(_iterator() > 60)
          fail("Recaptcha image load timeout")
        
          <%= path %>.script("document.getElementById('recaptcha-anchor').className.indexOf('recaptcha-checkbox-unchecked') >= 0")!
          if(_result() == "true")
          {
            RECAPTCHA2_SOLVED = true
            _break()
          }

          sleep(1000)!
  })!
  <%= path %>.move()!
  cache_data_clear()!
  <%= path %>.system_click()!

  _if_else(<%= method %> == "capmonsteraudio", function(){

      _do(function(){

        _do(function(){
           if(_iterator() > 60)
              fail("Recaptcha 2 wait timeout")
            
            <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementById('recaptcha-verify-button').className.indexOf('rc-button-default-disabled') < 0")!
            if(_result() == "true")
            {
              RECAPTCHA2_SOLVED = false
              _break()
            }

            <%= path %>.exist()!
            if(_result() == 0)
            {
              RECAPTCHA2_SOLVED = true
              _break()
            }        


            <%= path %>.script("document.getElementById('recaptcha-anchor').className.indexOf('recaptcha-checkbox-checked') >= 0")!
            if(_result() == "true")
            {
              RECAPTCHA2_SOLVED = true
              _break()
            }

            
            sleep(1000)!
        })!
        

      if(RECAPTCHA2_SOLVED)
        _break()

      if(_iterator() > <%= timestosolve %>)
        fail("Too many fails solve recaptcha 2")

      _if(RECAPTCHA2_FIRST_TIME, function(){

        _do(function(){
         if(_iterator() > 60)
            fail("Recaptcha image load timeout")
          
            <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementsByClassName('rc-imageselect-dynamic-selected').length")!
            if(_result() == "0")
              _break()

            sleep(1000)!
        })!

        _do(function(){
           if(_iterator() > 60)
              fail("Recaptcha 2 audio button wait timeout")

            <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementById('recaptcha-audio-button').getBoundingClientRect().top")!
            TOP_BUTTON = parseInt(_result())

            <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementById('recaptcha-audio-button').getBoundingClientRect().left")!
            LEFT_BUTTON = parseInt(_result())

            if(TOP_BUTTON > 300)
              _break()
        })!

        <%= prefix %>match("src=\"https://www.google.com/recaptcha/api2/frame").script("self.getBoundingClientRect().top + scrolly + positiony")!
        TOP = parseInt(_result())

        <%= prefix %>match("src=\"https://www.google.com/recaptcha/api2/frame").script("self.getBoundingClientRect().left + scrollx + positionx")!
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

            <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementsByClassName('rc-text-instructions').length")!

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

        RECAPTCHA2_SOLVED = _result()

        if(RECAPTCHA2_SOLVED.indexOf("133193320491090004119440") >= 0)
        {
          fail("Your IP was banned!")
        }

        <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementById('audio-response').getBoundingClientRect().top")!
        TOP_BUTTON = parseInt(_result())

        <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementById('audio-response').getBoundingClientRect().left")!
        LEFT_BUTTON = parseInt(_result())

        <%= prefix %>match("src=\"https://www.google.com/recaptcha/api2/frame").script("self.getBoundingClientRect().top + scrolly + positiony")!
        TOP = parseInt(_result())

        <%= prefix %>match("src=\"https://www.google.com/recaptcha/api2/frame").script("self.getBoundingClientRect().left + scrollx + positionx")!
        LEFT = parseInt(_result())

        move(LEFT + LEFT_BUTTON + 12, TOP + TOP_BUTTON + 12)!
        mouse(LEFT + LEFT_BUTTON + 12, TOP + TOP_BUTTON + 12)!

        page().type(RECAPTCHA2_SOLVED,100)!

      })!


        <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementById('recaptcha-verify-button').getBoundingClientRect().top")!
        TOP_BUTTON = parseInt(_result())

        <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementById('recaptcha-verify-button').getBoundingClientRect().left")!
        LEFT_BUTTON = parseInt(_result())

        <%= prefix %>match("src=\"https://www.google.com/recaptcha/api2/frame").script("self.getBoundingClientRect().top + scrolly + positiony")!
        TOP = parseInt(_result())
        <%= prefix %>match("src=\"https://www.google.com/recaptcha/api2/frame").script("self.getBoundingClientRect().left + scrollx + positionx")!
        LEFT = parseInt(_result())

        move(LEFT + LEFT_BUTTON + 50, TOP + TOP_BUTTON + 15)!
        cache_data_clear()!
        mouse(LEFT + LEFT_BUTTON + 50, TOP + TOP_BUTTON + 15)!

      
     
    })!

  },function(){

    _do(function(){
      
      _do(function(){
         if(_iterator() > 60)
            fail("Recaptcha 2 wait timeout")
          
          <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementById('recaptcha-verify-button').className.indexOf('rc-button-default-disabled') < 0")!
          if(_result() == "true")
          {
            RECAPTCHA2_SOLVED = false
            _break()
          }

          <%= path %>.exist()!
          if(_result() == 0)
          {
            RECAPTCHA2_SOLVED = true
            _break()
          }     

          <%= path %>.script("document.getElementById('recaptcha-anchor').className.indexOf('recaptcha-checkbox-checked') >= 0")!
          if(_result() == "true")
          {
            RECAPTCHA2_SOLVED = true
            _break()
          }

             

          sleep(1000)!
      })!

      _do(function(){
         if(_iterator() > 60)
            fail("Recaptcha image load timeout")
          
            <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementsByClassName('rc-imageselect-dynamic-selected').length")!
            if(_result() == "0")
              _break()

            sleep(1000)!
      })!

      if(RECAPTCHA2_SOLVED)
        _break()

      <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("window.getComputedStyle(document.getElementsByClassName('rc-imageselect-incorrect-response')[0])['display']")!
      _if(_result() != "none" && !RECAPTCHA2_SOLVED, function(){
        solver_failed()
        wait_load("recaptcha/api2/payload")!
      })!
        

      if(_iterator() > <%= timestosolve %>)
        fail("Too many fails solve recaptcha 2")


      _if(RECAPTCHA2_FIRST_TIME, function(){
        RECAPTCHA2_FIRST_TIME = false
        wait_load("recaptcha/api2/payload")!
      })!

      sleep(3000)!

      <%= prefix %>match("src=\"https://www.google.com/recaptcha/api2/frame").focus()!
      
      _do(function(){

        <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementsByClassName('rc-imageselect-table-44').length")!
        IS44 = parseInt(_result()) > 0

        <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementsByClassName('rc-imageselect-table-33').length")!
        IS33 = parseInt(_result()) > 0
        
        <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementsByClassName('rc-imageselect-table-42').length")!
        IS42 = parseInt(_result()) > 0


        <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementsByClassName('rc-imageselect-tileselected').length")!
        RECAPTCHA2_TOTAL_SELECTED = parseInt(_result())

        if(!(RECAPTCHA2_TOTAL_SELECTED>0 || IS44 && (<%= method %> == "capmonsterimage" || <%= method %> == "capmonster") || (!IS33 && !IS44 && !IS42)))
          _break()

        if(_iterator() > 10)
            fail("Too many recaptcha 2 reloads")

        <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementById('recaptcha-reload-button').getBoundingClientRect().top")!
        TOP_RECAPTCHA_RELOAD_BUTTON = parseInt(_result())

        <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementById('recaptcha-reload-button').getBoundingClientRect().left")!
        LEFT_RECAPTCHA_RELOAD_BUTTON = parseInt(_result())

        <%= prefix %>match("src=\"https://www.google.com/recaptcha/api2/frame").script("self.getBoundingClientRect().top + scrolly + positiony")!
        TOP = parseInt(_result())

        <%= prefix %>match("src=\"https://www.google.com/recaptcha/api2/frame").script("self.getBoundingClientRect().left + scrollx + positionx")!
        LEFT = parseInt(_result())

        move(LEFT + LEFT_RECAPTCHA_RELOAD_BUTTON + 12, TOP + TOP_RECAPTCHA_RELOAD_BUTTON + 12)!
        cache_data_clear()!
        mouse(LEFT + LEFT_RECAPTCHA_RELOAD_BUTTON + 12, TOP + TOP_RECAPTCHA_RELOAD_BUTTON + 12)!

        wait_load("recaptcha/api2/payload")!
        
        sleep(3000)!

      })!

      <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementsByClassName('rc-imageselect-payload')[0].getBoundingClientRect().bottom")!
      BOTTOM_IMAGE = parseInt(_result())

      <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementsByClassName('rc-imageselect-challenge')[0].getBoundingClientRect().top")!
      TOP_IMAGE = parseInt(_result())

      <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementsByClassName('rc-imageselect-table-44').length")!
      IS44 = parseInt(_result()) > 0

      <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementsByClassName('rc-imageselect-table-33').length")!
      IS33 = parseInt(_result()) > 0

      <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementsByClassName('rc-imageselect-table-42').length")!
      IS42 = parseInt(_result()) > 0

      if(!IS33 && !IS44 && !IS42)
      {
        fail("Unknown captcha type")
      }

      _if_else(<%= method %> == "capmonsterimage" || <%= method %> == "capmonster", function(){
        <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("(function(){var tmp = document.createElement('DIV');tmp.innerHTML = document.getElementsByClassName('rc-imageselect-desc-wrapper')[0].innerHTML.split('<br>')[0];return tmp.textContent})()")!
        solver_property("capmonster","Task",_result())
        solver_property("capmonster","CapMonsterModule","ZennoLab.ReCaptcha2")
        cache_get_base64("recaptcha/api2/payload")!
        solve_base64("capmonster", _result())!
        RECAPTCHA2_SOLVED = _result()
      },function(){
        <%= prefix %>match("src=\"https://www.google.com/recaptcha/api2/frame").render_base64()!
        solve_base64_no_fail(<%= method %>, _result())!
        if(_result().indexOf("ERROR_CAPTCHA_UNSOLVABLE") >= 0)
        {
          RECAPTCHA2_SOLVED = ""
        }else if(_result().indexOf("CAPTCHA_FAIL") >= 0)
        {
          fail(_result())
        }else
        {
          RECAPTCHA2_SOLVED = _result()
        }
      })!

      <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementById('rc-imageselect-target').getBoundingClientRect().top")!
      TOP_PIC = parseInt(_result())

      <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementById('rc-imageselect-target').getBoundingClientRect().bottom")!
      BOTTOM_PIC = parseInt(_result())

      <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementById('rc-imageselect-target').getBoundingClientRect().left")!
      LEFT_PIC = parseInt(_result())

      <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementById('rc-imageselect-target').getBoundingClientRect().right")!
      RIGHT_PIC = parseInt(_result())

      
      CLICKS = NumbersParseRecaptcha2(RECAPTCHA2_SOLVED,IS33,IS44,IS42,TOP_PIC,LEFT_PIC,BOTTOM_PIC,RIGHT_PIC,BOTTOM_IMAGE,TOP_IMAGE)
      
      <%= prefix %>match("src=\"https://www.google.com/recaptcha/api2/frame").script("window.getComputedStyle(self)['visibility']")!
      if(_result() == "hidden")
        fail("Captcha not visible") 


      CAPTCHA_TYPE_DYNAMIC = false


      _do(function(){
        if(_iterator() > CLICKS.length)
          _break(1)

        cache_data_clear()!

        <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementsByClassName('rc-imageselect-tileselected').length")!
        RECAPTCHA2_TOTAL_SELECTED = parseInt(_result())

        <%= prefix %>match("src=\"https://www.google.com/recaptcha/api2/frame").script("self.getBoundingClientRect().top + scrolly + positiony")!
        TOP = parseInt(_result())
        <%= prefix %>match("src=\"https://www.google.com/recaptcha/api2/frame").script("self.getBoundingClientRect().left + scrollx + positionx")!
        LEFT = parseInt(_result())

        move(LEFT + CLICKS[_iterator() - 1][0],TOP + CLICKS[_iterator() - 1][1])!
        mouse(LEFT + CLICKS[_iterator() - 1][0],TOP + CLICKS[_iterator() - 1][1])!

        _do(function(){
         if(_iterator() > 30)
            fail("Failed to wait select responce")
          
            <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementsByClassName('rc-imageselect-tileselected').length")!
            if(RECAPTCHA2_TOTAL_SELECTED != parseInt(_result()))
              _break()

            is_load("recaptcha/api2/payload")!
            if(_result())
            {
              CAPTCHA_TYPE_DYNAMIC = true
              _break()
            }

            sleep(1000)!
        })!

      })!

      sleep(1000)!

      _if(!CAPTCHA_TYPE_DYNAMIC, function(){

        <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementById('recaptcha-verify-button').getBoundingClientRect().top")!
        TOP_RECAPTCHA_VERIFY_BUTTON = parseInt(_result())

        <%= prefix %>frame_match("google.com/recaptcha/api2/frame").script("document.getElementById('recaptcha-verify-button').getBoundingClientRect().left")!
        LEFT_RECAPTCHA_VERIFY_BUTTON = parseInt(_result())

        <%= prefix %>match("src=\"https://www.google.com/recaptcha/api2/frame").script("self.getBoundingClientRect().top + scrolly + positiony")!
        TOP = parseInt(_result())
        <%= prefix %>match("src=\"https://www.google.com/recaptcha/api2/frame").script("self.getBoundingClientRect().left + scrollx + positionx")!
        LEFT = parseInt(_result())

        move(LEFT + LEFT_RECAPTCHA_VERIFY_BUTTON + 50, TOP + TOP_RECAPTCHA_VERIFY_BUTTON + 15)!
        cache_data_clear()!
        mouse(LEFT + LEFT_RECAPTCHA_VERIFY_BUTTON + 50, TOP + TOP_RECAPTCHA_VERIFY_BUTTON + 15)!

      })!
      
    })!

  })!



})!



