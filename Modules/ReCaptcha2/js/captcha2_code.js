/*Browser*/
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
if(<%= method %> == "antigate")
{
  antigate(<%= rucaptcha %>)
}
if(<%= method %> == "dbc")
{
  dbc(<%= dbc %>)
}


<%= waiter %>
_do(function(){
     if(_iterator() > 60)
        fail("Recaptcha image load timeout")
      
        frame("google.com/recaptcha/api2/anchor").script("document.getElementById('recaptcha-anchor').className.indexOf('recaptcha-checkbox-unchecked') >= 0")!
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

_do(function(){
  
  _do(function(){
     if(_iterator() > 60)
        fail("Recaptcha 2 wait timeout")
      
      frame("google.com/recaptcha/api2/frame").script("document.getElementById('recaptcha-verify-button').className.indexOf('rc-button-default-disabled') < 0")!
      if(_result() == "true")
      {
        RECAPTCHA2_SOLVED = false
        _break()
      }

      frame("google.com/recaptcha/api2/anchor").script("document.getElementById('recaptcha-anchor').className.indexOf('recaptcha-checkbox-checked') >= 0")!
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
      
        frame("google.com/recaptcha/api2/frame").script("document.getElementsByClassName('rc-imageselect-dynamic-selected').length")!
        if(_result() == "0")
          _break()

        sleep(1000)!
  })!

  if(RECAPTCHA2_SOLVED)
    _break()

  frame("google.com/recaptcha/api2/frame").script("window.getComputedStyle(document.getElementsByClassName('rc-imageselect-incorrect-response')[0])['display']")!
  if(_result() != "none" && !RECAPTCHA2_SOLVED)
    solver_failed()

  if(_iterator() > <%= timestosolve %>)
    fail("Too many fails solve recaptcha 2")


  wait_load("recaptcha/api2/payload")!

  match("src=\"https://www.google.com/recaptcha/api2/frame").script("self.getBoundingClientRect().top + window.scrollY")!
  TOP = parseInt(_result())
  match("src=\"https://www.google.com/recaptcha/api2/frame").script("self.getBoundingClientRect().left + window.scrollX")!
  LEFT = parseInt(_result())

  frame("google.com/recaptcha/api2/frame").script("document.getElementsByClassName('rc-imageselect-table-33').length")!
  IS33 = parseInt(_result()) > 0

  frame("google.com/recaptcha/api2/frame").script("document.getElementsByClassName('rc-imageselect-table-44').length")!
  IS44 = parseInt(_result()) > 0

  frame("google.com/recaptcha/api2/frame").script("document.getElementsByClassName('rc-imageselect-table-42').length")!
  IS42 = parseInt(_result()) > 0

  if(!IS33 && !IS44 && !IS42)
  {
    fail("Unknown captcha type")
  }

  
  match("src=\"https://www.google.com/recaptcha/api2/frame").render_base64()!
  solve_base64(<%= method %>, _result())!
  RECAPTCHA2_SOLVED = _result()
  CLICKS = NumbersParseRecaptcha2(RECAPTCHA2_SOLVED,IS33,IS44,IS42)
  
  match("src=\"https://www.google.com/recaptcha/api2/frame").script("window.getComputedStyle(self)['visibility']")!
  if(_result() == "hidden")
    fail("Captcha not visible") 


  _do(function(){
    if(_iterator() > CLICKS.length)
      _break(1)
    move(LEFT + CLICKS[_iterator() - 1][0],TOP + CLICKS[_iterator() - 1][1])!
    mouse(LEFT + CLICKS[_iterator() - 1][0],TOP + CLICKS[_iterator() - 1][1])!
  })!

  sleep(1000)!
  frame("google.com/recaptcha/api2/frame").script("document.getElementById('recaptcha-verify-button').getBoundingClientRect().top")!
  TOP_RECAPTCHA_VERIFY_BUTTON = parseInt(_result())

  frame("google.com/recaptcha/api2/frame").script("document.getElementById('recaptcha-verify-button').getBoundingClientRect().left")!
  LEFT_RECAPTCHA_VERIFY_BUTTON = parseInt(_result())

  move(LEFT + LEFT_RECAPTCHA_VERIFY_BUTTON + 50, TOP + TOP_RECAPTCHA_VERIFY_BUTTON + 15)!
  cache_data_clear()!
  mouse(LEFT + LEFT_RECAPTCHA_VERIFY_BUTTON + 50, TOP + TOP_RECAPTCHA_VERIFY_BUTTON + 15)!

})!

