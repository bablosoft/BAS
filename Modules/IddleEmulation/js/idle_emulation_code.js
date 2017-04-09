/*Browser*/
IDDLE_EMULATION_END = Date.now() + 1000 * (<%= iddle %>)
IDDLE_EMULATION_DISTRIBUTION = <%= distribution %>
IDDLE_CURSOR_POSITION_X = -1
IDDLE_CURSOR_POSITION_Y = -1

IDDLE_CURSOR_POSITION_WAS_SCROLL = false

page().script("window.innerWidth")!
IDDLE_CURSOR_POSITION_WIDTH = parseInt(_result())

page().script("window.innerHeight")!
IDDLE_CURSOR_POSITION_HEIGHT = parseInt(_result())


_do(function(){
  if(Date.now() >= IDDLE_EMULATION_END)
    _break()

  IDDLE_EMULATION_CURRENT_ITEM = IDDLE_EMULATION_DISTRIBUTION[Math.floor(Math.random()*IDDLE_EMULATION_DISTRIBUTION.length)]

  if(_iterator() == 1)
    IDDLE_EMULATION_CURRENT_ITEM = 2

  _if(IDDLE_EMULATION_CURRENT_ITEM == 1, function(){
    //scroll
    IDDLE_EMULATION_CURRENT_DIRECTION = (rand(1,2) == 2) ? "<MOUSESCROLLUP>" : "<MOUSESCROLLDOWN>"
    if(!IDDLE_CURSOR_POSITION_WAS_SCROLL)
      IDDLE_EMULATION_CURRENT_DIRECTION = "<MOUSESCROLLDOWN>"

    IDDLE_CURSOR_POSITION_WAS_SCROLL = true
    
    IDDLE_EMULATION_CURRENT_NUMBER = rand(1,5)

    _do(function(){
      if(_iterator() >= IDDLE_EMULATION_CURRENT_NUMBER)
        _break()
      page().type(IDDLE_EMULATION_CURRENT_DIRECTION,1000)!
      sleep(rand(300,1000))!
    })!
    
  })!

  _if(IDDLE_EMULATION_CURRENT_ITEM == 2, function(){
    //long move
    page().script("document.body.scrollLeft")!
    IDDLE_CURSOR_POSITION_SCROLL_X = parseInt(_result())

    page().script("document.body.scrollTop")!
    IDDLE_CURSOR_POSITION_SCROLL_Y = parseInt(_result())

    IDDLE_CURSOR_POSITION_X = rand(1,IDDLE_CURSOR_POSITION_WIDTH)
    IDDLE_CURSOR_POSITION_Y = rand(1,IDDLE_CURSOR_POSITION_HEIGHT)
    move(IDDLE_CURSOR_POSITION_SCROLL_X + IDDLE_CURSOR_POSITION_X,IDDLE_CURSOR_POSITION_SCROLL_Y + IDDLE_CURSOR_POSITION_Y)!

  })!

  _if(IDDLE_EMULATION_CURRENT_ITEM == 3, function(){
    //short move
    if(IDDLE_CURSOR_POSITION_X < 0 || IDDLE_CURSOR_POSITION_Y < 0)
      _break()

    
    page().script("document.body.scrollLeft")!
    IDDLE_CURSOR_POSITION_SCROLL_X = parseInt(_result())

    page().script("document.body.scrollTop")!
    IDDLE_CURSOR_POSITION_SCROLL_Y = parseInt(_result())

    IDDLE_EMULATION_CURRENT_NUMBER = rand(1,4)

    _do(function(){
      if(_iterator() >= IDDLE_EMULATION_CURRENT_NUMBER)
        _break()
      IDDLE_CURSOR_POSITION_X += rand(-50,50)
      IDDLE_CURSOR_POSITION_Y += rand(-50,50)
      if(IDDLE_CURSOR_POSITION_X > IDDLE_CURSOR_POSITION_WIDTH)
        IDDLE_CURSOR_POSITION_X = IDDLE_CURSOR_POSITION_WIDTH
      if(IDDLE_CURSOR_POSITION_Y > IDDLE_CURSOR_POSITION_HEIGHT)
        IDDLE_CURSOR_POSITION_Y = IDDLE_CURSOR_POSITION_HEIGHT
      if(IDDLE_CURSOR_POSITION_X < 0)
        IDDLE_CURSOR_POSITION_X = 0
      if(IDDLE_CURSOR_POSITION_Y < 0)
        IDDLE_CURSOR_POSITION_Y = 0
      move(IDDLE_CURSOR_POSITION_SCROLL_X + IDDLE_CURSOR_POSITION_X,IDDLE_CURSOR_POSITION_SCROLL_Y + IDDLE_CURSOR_POSITION_Y)!
      _if(rand(1,10) > 3,function(){
       sleep(rand(10,300))!
      })!
    })!
    
  })!

  _if(IDDLE_EMULATION_CURRENT_ITEM == 4, function(){
    //sleep
    sleep(rand(500,5000))!
  })!


   
})!
