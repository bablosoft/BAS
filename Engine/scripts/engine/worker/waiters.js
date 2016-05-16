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
        wait("Failed to wait for changing url " + text_success,function(){

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
        wait("Failed to wait for changing url " + text_success,function(){
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
        wait("Failed to wait for loading " + text_success,function(){

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
        wait("Failed to wait for loading " + text_success,function(){
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
        wait("Failed to wait for content " + text_success,function(){

            page().xml(function(){
                if(_result().indexOf(_arguments()[0])>=0)
                    _set_result(true);
            })
        },
        function(){
                    page().xml(function(){
                        if(_result().indexOf(_arguments()[1])>=0)
                        {
                            _set_result(true);
                        }
                    })
        },[text_success,text_fail],func);

    }else
    {
        wait("Failed to wait for content " + text_success,function(){
            page().xml(function(){
                if(_result().indexOf(_arguments())>=0)
                {
                    _set_result(true);
                }
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
        wait("Failed to wait for css " + text_success,function(){
            _set_result(false);
            page().css(_arguments()[0]).exist(function(){
                _set_result(_result() === 1 || _result() === true);
            })
        },
        function(){
                    _set_result(false);
                    page().css(_arguments()[1]).exist(function(){
                         _set_result(_result() === 1 || _result() === true);
                    })
        },[text_success,text_fail],func);

    }else
    {
        _set_result(false);
        wait("Failed to wait for css " + text_success, function(){
            _set_result(false);
            page().css(_arguments()).exist(function(){
                _set_result(_result() === 1 || _result() === true);
            })
        },text_success,func);
    }

}

function wait_async_load(func)
{
    WAIT_ASYNC_LOAD_FUNC = func;
    url(function(){
        wait("Failed to wait of state complete on page " + _result(),function(){
                    _set_result(false);
                    script("document.readyState", function(){
                      _set_result(_result() === "complete");
                    })
                },null,WAIT_ASYNC_LOAD_FUNC);
        })
}


function wait()
{
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
        if(i>60)
            fail(fail_message)

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
