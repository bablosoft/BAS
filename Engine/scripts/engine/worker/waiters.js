BROWSERAUTOMATIONSTUDIO_WAIT_TIMEOUT = 60
BROWSERAUTOMATIONSTUDIO_FULL_LOAD_TIMEOUT = 4


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
        wait(tr("Failed to wait for content ") + text_success,function(){
            _set_result(false);
            page().match(_arguments()[0]).exist(function(){
                _set_result(_result() === 1 || _result() === true);
            })
        },
        function(){
            _set_result(false);
            page().match(_arguments()[1]).exist(function(){
                 _set_result(_result() === 1 || _result() === true);
            })
        },[text_success,text_fail],func);

    }else
    {
        wait(tr("Failed to wait for content ") + text_success,function(){
            _set_result(false);
            page().match(_arguments()).exist(function(){
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
        wait(tr("Failed to wait for css ") + text_success,function(){
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
        wait(tr("Failed to wait for css ") + text_success, function(){
            _set_result(false);
            page().css(_arguments()).exist(function(){
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
        if(i>BROWSERAUTOMATIONSTUDIO_WAIT_TIMEOUT)
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
