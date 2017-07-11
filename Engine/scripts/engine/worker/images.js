function _clear_image_data(callback)
{
    Browser.ClearImageData(_get_function_body(callback));
}
function _set_image_data(base64, callback)
{
    Browser.SetImageData(base64, _get_function_body(callback));
}
function _find_image(callback)
{
    Browser.FindImage(_get_function_body(callback));
}

IMAGE_FINDER = new(function()
{
    var IsEmpty = true;
    var X = 0;
    var Y = 0;
    var Width = 0;
    var Height = 0;

    this.SetEmpty = function()
    {
        IsEmpty = true;
        X = 0;
        Y = 0;
        Width = 0;
        Height = 0;
    }
    this.SetFound = function(x,y,width,height)
    {
        IsEmpty = false;
        X = x;
        Y = y;
        Width = width;
        Height = height;
    }

    this.exist = function(callback)
    {
        _set_result(!IsEmpty);
        ScriptWorker.SetScript(_get_function_body(callback))
        ScriptWorker.RunSubScript()
    }

    this.random_point = function(callback)
    {
        if(IsEmpty)
        {
            _set_result("");
        }else
        {
            var x = 0;
            for(var i1 = 0;i1 < 10;i1++)
            {
                x+=Math.random()*(Width/10);
            };
            x = Math.floor(x) + X + 1;
            if(x >= X + Width)
                x = X + Width - 1;
            if(x <= X)
                x = X + 1;

            var y = 0;
            for(var i2 = 0;i2 < 10;i2++)
            {
                y += Math.random()*(Height/10);
            };
            y = Math.floor(y) + Y + 1;
            if(y >= Y + Height)
                y = Y + Height - 1;
            if(y <= Y)
                y = Y + 1;

            //log(X + "," + Y + "," + Width + "," + Height)
            _set_result(x + "," + y);
        }

        ScriptWorker.SetScript(_get_function_body(callback))
        ScriptWorker.RunSubScript()
    }
    this.script = function(text, callback)
    {
        if(IsEmpty)
        {
            _set_result("");
        }else
        {
            _set_result(X + "|" + Y + "|" + Width + "|" + Height);
        }

        ScriptWorker.SetScript(_get_function_body(callback))
        ScriptWorker.RunSubScript()
    }
    this.clarify = function(X,Y,callback)
    {
        _set_result("");
        ScriptWorker.SetScript(_get_function_body(callback))
        ScriptWorker.RunSubScript()
    }
})

function _image()
{
    return IMAGE_FINDER;
}

function _wait_image(params, callback)
{
    IMAGE_END = Date.now() + params["timeout"]
    IMAGE_PARAMS = params
    IMAGE_SLEEP = 0
    IMAGE_PAGE_POSITION = 0
    IMAGE_PAGE_ALL = -1
    IMAGE_SCREEN_SIZE = 0
    IMAGE_FIRST_SCROLL = true

    _call(function(){

        _set_image_data(IMAGE_PARAMS["data"], function(){

            _if(IMAGE_PARAMS["scroll"], function(){

                /*Get viewport stats*/

                page().script("document.body.scrollTop + '|' + document.body.scrollHeight + '|' + document.documentElement.clientHeight", function(){
                    //log("Viewport stats " + _result())

                    if(_result().length == 0)
                    {
                        IMAGE_PAGE_POSITION = 0
                        IMAGE_PAGE_ALL = 600
                        IMAGE_SCREEN_SIZE = 600
                    }else
                    {
                        var split = _result().split("|")
                        IMAGE_PAGE_POSITION = parseInt(split[0])
                        IMAGE_PAGE_ALL = parseInt(split[1])
                        IMAGE_SCREEN_SIZE = parseInt(split[2])
                    }


                })

            }, function(){
                _do(function(){

                    /*End if timeout*/

                    if(Date.now() > IMAGE_END)
                    {
                        IMAGE_FINDER.SetEmpty()
                        if(IMAGE_PARAMS["fail"])
                        {
                            fail("Search image timeout");
                        }
                        _break()
                    }

                    _if_else(IMAGE_FIRST_SCROLL, function(){
                        IMAGE_FIRST_SCROLL = false
                    }, function(){
                        IMAGE_SLEEP = rand(500,2000);

                        /*Do scroll*/
                        _if_else(IMAGE_PARAMS["scroll"], function(){
                            IMAGE_SLEEP = rand(50,300);
                            _if(IMAGE_PAGE_POSITION + Math.floor(IMAGE_SCREEN_SIZE/2) >= IMAGE_PAGE_ALL, function(){
                                IMAGE_PAGE_POSITION = 0
                                IMAGE_SLEEP = rand(500,2000);

                                _if(!IMAGE_PARAMS["wait"], function(){
                                    render(0,0,0,0, function(){
                                        IMAGE_FINDER.SetEmpty()
                                        if(IMAGE_PARAMS["fail"])
                                        {
                                            fail("Failed to search for image");
                                        }
                                        _break("function")
                                    })


                                }, function(){
                                    page().script("document.body.scrollTop + '|' + document.body.scrollHeight + '|' + document.documentElement.clientHeight", function(){
                                        //log("Viewport stats " + _result())
                                        if(_result().length == 0)
                                        {
                                            IMAGE_PAGE_ALL = 600
                                            IMAGE_SCREEN_SIZE = 600
                                        }else
                                        {
                                            var split = _result().split("|")
                                            IMAGE_PAGE_ALL = parseInt(split[1])
                                            IMAGE_SCREEN_SIZE = parseInt(split[2])
                                        }


                                    })
                                })


                            }, function(){
                                IMAGE_PAGE_POSITION += Math.floor(IMAGE_SCREEN_SIZE/2)
                                if(IMAGE_PAGE_POSITION > IMAGE_PAGE_ALL - 1)
                                    IMAGE_PAGE_POSITION = IMAGE_PAGE_ALL - 1
                                //log("Scrolling to " + IMAGE_PAGE_POSITION)
                                render(0,IMAGE_PAGE_POSITION,0,0, function(){

                                })

                            })

                        }, function(){
                            if(!IMAGE_PARAMS["wait"])
                            {
                                IMAGE_FINDER.SetEmpty()
                                if(IMAGE_PARAMS["fail"])
                                {
                                    fail("Failed to search for image");
                                }
                                _break("function")

                            }
                        },function(){

                        })

                    }, function(){

                        /*Sleep if needed*/
                        _if(IMAGE_SLEEP > 0, function(){

                            if(Date.now() + IMAGE_SLEEP > IMAGE_END)
                            {
                                IMAGE_FINDER.SetEmpty()
                                if(IMAGE_PARAMS["fail"])
                                {
                                    fail("Search image timeout");
                                }
                                _break()
                            }

                            //log("Sleeping for " + IMAGE_SLEEP)

                            sleep(IMAGE_SLEEP, function(){

                            })
                        }, function(){

                            /*Find image*/
                            _find_image(function(){

                                //log("Found image result " + _result())

                                var split = _result().split("|")
                                var threshold = parseInt(split[0])
                                if(threshold == -1)
                                {
                                    IMAGE_FIRST_SCROLL = true
                                    IMAGE_SLEEP = 2000
                                }
                                if(threshold >= IMAGE_PARAMS["threshold"])
                                {
                                    var x = parseInt(split[1])
                                    var y = parseInt(split[2])
                                    var width = parseInt(split[3])
                                    var height = parseInt(split[4])

                                    IMAGE_FINDER.SetFound(x,y,width,height)
                                    _break("function")

                                }

                            })

                        })

                    })


                }, function(){
                    /*Cleanup*/
                    //log("cleanup")
                    delete IMAGE_END
                    delete IMAGE_PARAMS
                    delete IMAGE_SLEEP
                    delete IMAGE_PAGE_POSITION
                    delete IMAGE_PAGE_ALL
                    delete IMAGE_SCREEN_SIZE
                    delete IMAGE_FIRST_SCROLL
                })

            })
        })
    }, null, callback)



}
