BROWSERAUTOMATIONSTUDIO_WAIT_TIMEOUT = 60
BROWSERAUTOMATIONSTUDIO_FULL_LOAD_TIMEOUT = 4
BROWSERAUTOMATIONSTUDIO_WAIT_TIMEOUT_NEXT = 0
BROWSERAUTOMATIONSTUDIO_WAIT_NOFAIL_NEXT = false


function waiter_timeout_next(timeout)
{
    BROWSERAUTOMATIONSTUDIO_WAIT_TIMEOUT_NEXT = Math.floor(timeout/1000);
}

function waiter_nofail_next()
{
    BROWSERAUTOMATIONSTUDIO_WAIT_NOFAIL_NEXT = true;
}

function wait_url()
{
    var text_success = null;
    var text_fail = null;
    var func = null;
    if(arguments.length === 2)
    {
        text_success = arguments[0];
        func = arguments[1];
    }else if(arguments.length === 3)
    {
        text_success = arguments[0];
        text_fail = arguments[1];
        func = arguments[2];
    }else
    {
        die("Wrong number of arguments");
    }

    if(text_fail)
    {
        wait(tr("Failed to wait for changing url ") + text_success,function(){

            url(function(){
                if(_result().indexOf(_arguments()[0])>=0)
                    _set_result(true);
            })
        },
        function(){
                    url(function(){
                        if(_result().indexOf(_arguments()[1])>=0)
                        {
                            _set_result(true);
                        }
                    })
        },[text_success,text_fail],func);

    }else
    {
        wait(tr("Failed to wait for changing url ") + text_success,function(){
            url(function(){
                if(_result().indexOf(_arguments())>=0)
                {
                    _set_result(true);
                }
            })
        },text_success,func);
    }

}

function wait_load()
{
    var text_success = null;
    var text_fail = null;
    var func = null;
    if(arguments.length === 2)
    {
        text_success = arguments[0];
        func = arguments[1];
    }else if(arguments.length === 3)
    {
        text_success = arguments[0];
        text_fail = arguments[1];
        func = arguments[2];
    }else
    {
        die("Wrong number of arguments");
    }

    if(text_fail)
    {
        wait(tr("Failed to wait for loading ") + text_success,function(){

            is_load(text_success,function(){
                if(_result())
                    _set_result(true);
            })
        },
        function(){
                    is_load(text_fail,function(){
                        if(_result())
                            _set_result(true);
                    })
        },[text_success,text_fail],func);

    }else
    {
        wait(tr("Failed to wait for loading ") + text_success,function(){
            is_load(text_success,function(){
                if(_result())
                    _set_result(true);
            })
        },text_success,func);
    }

}


function wait_memory()
{
    var text_success = null;
    var func = null;
    if(arguments.length === 2)
    {
        text_success = arguments[0];
        func = arguments[1];
    }else
    {
        die("Wrong number of arguments");
    }


    _do(function(){
       if(memory_virtual_available() > text_success)
           _break()

       if(_iterator() === 1)
           log("Memory is low. Waiting ...")

       sleep(5000,function(){
           _next();
       });

    },func);


}

function waiter_prepare_frames(data)
{
    var res = page();

    if(data["frames"])
    {
        var len = data["frames"].length
        for(var i = 0;i<len;i++)
        {
            var el = data["frames"][i]
            if(el["type"] === "css")
            {
                res = res.frame_css(el["data"])
            }else if(el["type"] === "match")
            {
                res = res.frame_match(el["data"])
            }
        }
    }

    return res;
}


function waiter_create_css_path(data)
{
    if(typeof(data) === "string")
        return page().css(data);

    var res = waiter_prepare_frames(data);

    if(data["index"])
        res = res.all(data["raw"]).at(data["index"]);
    else
        res = res.css(data["raw"])

    return res;
}

function waiter_create_match_path(data)
{
    if(typeof(data) === "string")
        return page().match(data);

    var res = waiter_prepare_frames(data);

    if(data["index"])
        res = res.match_all(data["raw"]).at(data["index"]);
    else
        res = res.match(data["raw"])

    return res;
}

function wait_content_visible()
{
    var text_success = null;
    var text_fail = null;
    var func = null;
    if(arguments.length === 2)
    {
        text_success = arguments[0];
        func = arguments[1];
    }else if(arguments.length === 3)
    {
        text_success = arguments[0];
        text_fail = arguments[1];
        func = arguments[2];
    }else
    {
        die("Wrong number of argumetns");
    }


    if(text_fail)
    {
        wait(tr("Failed to wait for content ") + JSON.stringify(text_success),function(){
            _set_result(false);
            waiter_create_match_path(_arguments()[0]).exist(function(){
                _set_result(_result() === 1 || _result() === true);
            })
        },
        function(){
            _set_result(false);
            waiter_create_match_path(_arguments()[1]).exist(function(){
                 _set_result(_result() === 1 || _result() === true);
            })
        },[text_success,text_fail],func);

    }else
    {
        wait(tr("Failed to wait for content ") + JSON.stringify(text_success),function(){
            _set_result(false);
            waiter_create_match_path(_arguments()).script("document.readyState!='loading' && self.getBoundingClientRect().height > 0 && self.getBoundingClientRect().width > 0&& window.getComputedStyle(self)['display']!='none'&&window.getComputedStyle(self)['visibility'] != 'hidden'",function(){
                _set_result(_result().indexOf("true")>=0);
            })
        },text_success,func);
    }


}

function wait_css_visible()
{
    var text_success = null;
    var text_fail = null;
    var func = null;
    if(arguments.length === 2)
    {
        text_success = arguments[0];
        func = arguments[1];
    }else if(arguments.length === 3)
    {
        text_success = arguments[0];
        text_fail = arguments[1];
        func = arguments[2];
    }else
    {
        die("Wrong number of arguments");
    }


    if(text_fail)
    {
        _set_result(false);
        wait(tr("Failed to wait for css ") + JSON.stringify(text_success),function(){
            _set_result(false);
            waiter_create_css_path(_arguments()[0]).exist(function(){
                _set_result(_result() === 1 || _result() === true);
            })
        },
        function(){
                    _set_result(false);
                    waiter_create_css_path(_arguments()[1]).exist(function(){
                         _set_result(_result() === 1 || _result() === true);
                    })
        },[text_success,text_fail],func);

    }else
    {
        _set_result(false);
        wait(tr("Failed to wait for css ") + JSON.stringify(text_success), function(){
            _set_result(false);
            waiter_create_css_path(_arguments()).script("document.readyState!='loading' && self.getBoundingClientRect().height > 0 && self.getBoundingClientRect().width > 0&& window.getComputedStyle(self)['display']!='none'&&window.getComputedStyle(self)['visibility'] != 'hidden'",function(){
               _set_result(_result().indexOf("true")>=0);
            })
        },text_success,func);
    }

}


function wait_content()
{
    var text_success = null;
    var text_fail = null;
    var func = null;
    if(arguments.length === 2)
    {
        text_success = arguments[0];
        func = arguments[1];
    }else if(arguments.length === 3)
    {
        text_success = arguments[0];
        text_fail = arguments[1];
        func = arguments[2];
    }else
    {
        die("Wrong number of argumetns");
    }


    if(text_fail)
    {
        wait(tr("Failed to wait for content ") + JSON.stringify(text_success),function(){
            _set_result(false);
            waiter_create_match_path(_arguments()[0]).exist(function(){
                _set_result(_result() === 1 || _result() === true);
            })
        },
        function(){
            _set_result(false);
            waiter_create_match_path(_arguments()[1]).exist(function(){
                 _set_result(_result() === 1 || _result() === true);
            })
        },[text_success,text_fail],func);

    }else
    {
        wait(tr("Failed to wait for content ") + JSON.stringify(text_success),function(){
            _set_result(false);
            waiter_create_match_path(_arguments()).exist(function(){
                _set_result(_result() === 1 || _result() === true);
            })
        },text_success,func);
    }


}

function wait_css()
{
    var text_success = null;
    var text_fail = null;
    var func = null;
    if(arguments.length === 2)
    {
        text_success = arguments[0];
        func = arguments[1];
    }else if(arguments.length === 3)
    {
        text_success = arguments[0];
        text_fail = arguments[1];
        func = arguments[2];
    }else
    {
        die("Wrong number of arguments");
    }


    if(text_fail)
    {
        _set_result(false);
        wait(tr("Failed to wait for css ") + JSON.stringify(text_success),function(){
            _set_result(false);
            waiter_create_css_path(_arguments()[0]).exist(function(){
                _set_result(_result() === 1 || _result() === true);
            })
        },
        function(){
                    _set_result(false);
                    waiter_create_css_path(_arguments()[1]).exist(function(){
                         _set_result(_result() === 1 || _result() === true);
                    })
        },[text_success,text_fail],func);

    }else
    {
        _set_result(false);
        wait(tr("Failed to wait for css ") + JSON.stringify(text_success), function(){
            _set_result(false);
            waiter_create_css_path(_arguments()).exist(function(){
                _set_result(_result() === 1 || _result() === true);
            })
        },text_success,func);
    }

}

function wait_async_load(func)
{
    WAIT_ASYNC_LOAD_START_TIME = (new Date()).getTime();
    //WAIT_ASYNC_LOAD_LOAD_TIME = 0;
    WAIT_ASYNC_LOAD_TIMEOUT_TIME = 0;


    //0 -  ***    IsLoading = 1       IsLoading = 0
    //1 -         IsLoading = 1  ***  IsLoading = 0
    //2 -         IsLoading = 1       IsLoading = 0   ***
    WAIT_ASYNC_LOAD_STAGE = 0;

    WAIT_ASYNC_LOAD_ITERATOR = 0;

    wait(tr("Failed to wait of state complete"),function(){
        _set_result(false);

        get_load_stats(function(){

            var is_loading = parseInt(_result().split(",")[0])

            switch(WAIT_ASYNC_LOAD_STAGE)
            {
                case 0:
                {
                    if(is_loading === 1)
                    {
                        WAIT_ASYNC_LOAD_STAGE = 1
                        //log("Stage #1")
                    }
                }break;
                case 1:
                {
                    if(is_loading === 0)
                    {
                        WAIT_ASYNC_LOAD_STAGE = 2
                        //WAIT_ASYNC_LOAD_LOAD_TIME = (new Date()).getTime();
                        //log("Stage #2")
                    }
                }break;
            }

            if(WAIT_ASYNC_LOAD_ITERATOR == BROWSERAUTOMATIONSTUDIO_FULL_LOAD_TIMEOUT - 1)
            {
                WAIT_ASYNC_LOAD_TIMEOUT_TIME = (new Date()).getTime();
            }

            var oldest_not_loaded_request_time = parseInt(_result().split(",")[1]);
            //log("[" + WAIT_ASYNC_LOAD_ITERATOR + "][" + WAIT_ASYNC_LOAD_STAGE + "] Wait start time : " + WAIT_ASYNC_LOAD_START_TIME + "; Oldest request time : " + oldest_not_loaded_request_time + "; Second stage time : " + WAIT_ASYNC_LOAD_LOAD_TIME)

            _set_result(

                        //No requests during 7 seconds.
                        (WAIT_ASYNC_LOAD_STAGE == 0 && WAIT_ASYNC_LOAD_ITERATOR >= BROWSERAUTOMATIONSTUDIO_FULL_LOAD_TIMEOUT - 1 && (oldest_not_loaded_request_time > WAIT_ASYNC_LOAD_TIMEOUT_TIME || oldest_not_loaded_request_time === 0)) ||

                        //Page loaded and every request that was started before page ended
                        (WAIT_ASYNC_LOAD_STAGE == 2 /*&& (oldest_not_loaded_request_time > WAIT_ASYNC_LOAD_LOAD_TIME || oldest_not_loaded_request_time === 0)*/)

                      );

            WAIT_ASYNC_LOAD_ITERATOR++;
        })



    },null,func);

}

function wait()
{
    BROWSERAUTOMATIONSTUDIO_WAIT_TIMEOUT_CURRENT = BROWSERAUTOMATIONSTUDIO_WAIT_TIMEOUT
    if(BROWSERAUTOMATIONSTUDIO_WAIT_TIMEOUT_NEXT > 0)
    {
        BROWSERAUTOMATIONSTUDIO_WAIT_TIMEOUT_CURRENT = BROWSERAUTOMATIONSTUDIO_WAIT_TIMEOUT_NEXT;
        BROWSERAUTOMATIONSTUDIO_WAIT_TIMEOUT_NEXT = 0;
    }

    BROWSERAUTOMATIONSTUDIO_WAIT_NOFAIL_CURRENT = BROWSERAUTOMATIONSTUDIO_WAIT_NOFAIL_NEXT;
    BROWSERAUTOMATIONSTUDIO_WAIT_NOFAIL_NEXT = false;

    var func_success = null;
    var func_fail = null;
    var func_continue = null;
    var arg = null;
    var fail_message = "Waiter Failed";

    var a = []
    for(var i = 0;i<arguments.length;i++)
        a.push(arguments[i]);


    var first = a.shift()
    if(typeof(first) === "string")
    {
        fail_message = first
        func_success = a.shift()
    }else
    {
        func_success = first
    }


    func_continue = a.pop()
    if(a.length > 0)
    {
        if(typeof(a[0]) === 'function')
        {
            func_fail = a.shift()
        }
    }
    if(a.length > 0)
    {
        if(typeof(a[0]) != 'function')
        {
            arg = a.shift()
        }
    }


    _do(function(i)
    {
        if(i>BROWSERAUTOMATIONSTUDIO_WAIT_TIMEOUT_CURRENT)
        {
            if(BROWSERAUTOMATIONSTUDIO_WAIT_NOFAIL_CURRENT)
                _break()
            else
                fail(fail_message)
        }

        _set_result(false)
        _call(func_success,arg,function(){
            if(_result() === true)
            {
                _break();
            }
            _if(func_fail,function(){
                _set_result(false)
                _call(func_fail,arg,function(){
                    if(_result() === true)
                        fail("Fail function trigger with message " + fail_message);
                })
            },function(){

                sleep(1000,function(){
                    _next();
                });

            });
        })

    },func_continue);

}

function get_element_selector(selector, need_all)
{
    if(selector.length === 0)
        return page()

    var res = []

    while(true)
    {
      var indexcss = selector.indexOf(">CSS>")
      var indexmatch = selector.indexOf(">MATCH>")
      var indexxpath = selector.indexOf(">XPATH>")
      var indexat = selector.indexOf(">AT>")
      var indexframe = selector.indexOf(">FRAME>")

      if(indexcss < 0 && indexmatch < 0 && indexxpath < 0 && indexat < 0 && indexframe < 0)
        break;

      var allmatch = []
      if(indexcss>=0)
          allmatch.push(indexcss)
      if(indexmatch>=0)
          allmatch.push(indexmatch)
      if(indexxpath>=0)
          allmatch.push(indexxpath)
      if(indexat>=0)
          allmatch.push(indexat)
      if(indexframe>=0)
          allmatch.push(indexframe)
      var minindex = Math.min.apply(null,allmatch)

      if(indexcss >= 0 && minindex === indexcss)
      {
        var item = selector.substring(0,indexcss)
        res.push(item)
        res.push("css")
        indexcss += ">CSS>".length
        selector = selector.substring(indexcss,selector.length)
        continue;
      }

      if(indexmatch >= 0 && minindex === indexmatch)
      {
        var item = selector.substring(0,indexmatch)
        res.push(item)
        res.push("match")
        indexmatch += ">MATCH>".length
        selector = selector.substring(indexmatch,selector.length)
        continue;
      }

      if(indexxpath >= 0 && minindex === indexxpath)
      {
        var item = selector.substring(0,indexxpath)
        res.push(item)
        res.push("xpath")
        indexxpath += ">XPATH>".length
        selector = selector.substring(indexxpath,selector.length)
        continue;
      }

      if(indexat >= 0 && minindex === indexat)
      {
        var item = selector.substring(0,indexat)
        res.push(item)
        res.push("at")
        indexat += ">AT>".length
        selector = selector.substring(indexat,selector.length)
        continue;
      }

      if(indexframe >= 0 && minindex === indexframe)
      {
        var item = selector.substring(0,indexframe)
        res.push(item)
        res.push("frame")
        indexframe += ">FRAME>".length
        selector = selector.substring(indexframe,selector.length)
        continue;
      }
    }
    res.shift()
    res.push(selector)

    var r = page()

    for(var i = 0;i<res.length;i++)
    {
        var el = {s:res[i]}
        i++;
        el["i"] = res[i];

        var next_at = i + 1 < res.length && res[i+1]=== "at";
        if(need_all && i + 1 >= res.length)
            next_at = true;

        if(el["s"] === "css" && next_at)
        {
            r = r.all(el["i"])
        }else if(el["s"] === "css" && !next_at)
        {
            r = r.css(el["i"])
        }else if(el["s"] === "match" && next_at)
        {
            r = r.match_all(el["i"])
        }else if(el["s"] === "match" && !next_at)
        {
            r = r.match(el["i"])
        }else if(el["s"] === "xpath" && next_at)
        {
            r = r.xpath_all(el["i"])
        }else if(el["s"] === "xpath" && !next_at)
        {
            r = r.xpath(el["i"])
        }else if(el["s"] === "at")
        {
            r = r.at(parseInt(el["i"]))
        }else if(el["s"] === "frame")
        {
            r = r.frame_element()
        }
    }

    return r;
}

function wait_element()
{
    var text_success = null;
    var text_fail = null;
    var func = null;
    if(arguments.length === 2)
    {
        text_success = arguments[0];
        func = arguments[1];
    }else if(arguments.length === 3)
    {
        text_success = arguments[0];
        text_fail = arguments[1];
        func = arguments[2];
    }else
    {
        die("Wrong number of arguments");
    }


    if(text_fail)
    {
        _set_result(false);
        wait(tr("Failed to wait for element ") + text_success,function(){
            _set_result(false);
            get_element_selector(_arguments()[0]).exist(function(){
                _set_result(_result() === 1 || _result() === true);
            })
        },
        function(){
                    _set_result(false);
                    get_element_selector(_arguments()[1]).exist(function(){
                         _set_result(_result() === 1 || _result() === true);
                    })
        },[text_success,text_fail],func);

    }else
    {
        _set_result(false);
        wait(tr("Failed to wait for element ") + text_success, function(){
            _set_result(false);
            get_element_selector(_arguments()).exist(function(){
                _set_result(_result() === 1 || _result() === true);
            })
        },text_success,func);
    }

}

function wait_element_visible()
{
    var text_success = null;
    var text_fail = null;
    var func = null;
    if(arguments.length === 2)
    {
        text_success = arguments[0];
        func = arguments[1];
    }else if(arguments.length === 3)
    {
        text_success = arguments[0];
        text_fail = arguments[1];
        func = arguments[2];
    }else
    {
        die("Wrong number of arguments");
    }


    if(text_fail)
    {
        _set_result(false);
        wait(tr("Failed to wait for element ") + text_success,function(){
            _set_result(false);
            get_element_selector(_arguments()[0]).exist(function(){
                _set_result(_result() === 1 || _result() === true);
            })
        },
        function(){
                    _set_result(false);
                    get_element_selector(_arguments()[1]).exist(function(){
                         _set_result(_result() === 1 || _result() === true);
                    })
        },[text_success,text_fail],func);

    }else
    {
        _set_result(false);
        wait(tr("Failed to wait for element ") + text_success, function(){
            _set_result(false);
            get_element_selector(_arguments()).script("document.readyState!='loading' && self.getBoundingClientRect().height > 0 && self.getBoundingClientRect().width > 0&& window.getComputedStyle(self)['display']!='none'&&window.getComputedStyle(self)['visibility'] != 'hidden'",function(){
               _set_result(_result().indexOf("true")>=0);
            })
        },text_success,func);
    }

}
