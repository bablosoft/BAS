function _ensure_browser_created()
{
    if(typeof(NetworkAccessManager)=='undefined')
        die("NetworkAccessManager is not accessible, try to create new browser with browser()! command")
}

function new_browser(callback)
{
    Browser.CreateNewBrowser(true, "ScriptWorker.AttachNetworkAccessManager();" + _get_function_body(callback))
}

function _mbr()
{
    Browser.MarkBeforeReset();
}

function _mar()
{
    Browser.MarkAfterReset();
}

function browser(callback)
{
    Browser.CreateNewBrowser(false, "_mbr();ScriptWorker.AttachNetworkAccessManager();reset(function(){_mar();" + _get_function_body(callback) + "})")
}

function mouse(x, y, callback)
{
    _ensure_browser_created();
    Browser.MouseClick(x,y,_get_function_body(callback))
}

function render(x, y, width, height, callback)
{
    _ensure_browser_created();
    Browser.Render(x,y,width,height,_get_function_body(callback))
}

function scroll(x, y, callback)
{
    _ensure_browser_created();
    Browser.Scroll(x,y,_get_function_body(callback))
}

function move(x, y, callback)
{
    _ensure_browser_created();
    Browser.MouseMove(x,y,_get_function_body(callback))
}

function wait_code(callback)
{
    _ensure_browser_created();
    Browser.WaitCode(_get_function_body(callback))
}

function section_end(callback)
{
    _ensure_browser_created();
    Browser.WaitCode(_get_function_body(callback))
}

function load(text, callback)
{
    _ensure_browser_created();
    LOAD_TEXT = text;
    Browser.LoadPage(text,"if(_result() == false){fail('Failed to load page ' + LOAD_TEXT)};" + _get_function_body(callback));
}

function open_file_dialog(text, callback)
{
    _ensure_browser_created();
    Browser.SetOpenFileName(text,_get_function_body(callback));
}

function screenshot(path, callback)
{
    _ensure_browser_created();
    page().render_file(path, callback);
}

function url(callback)
{
    _ensure_browser_created();
    Browser.GetUrl(_get_function_body(callback));
}

function get_cookies(url, callback)
{
    _ensure_browser_created();
    Browser.GetCookiesForUrl(url,_get_function_body(callback));
}

function resize(x, y, callback)
{
    _ensure_browser_created();
    Browser.Resize(x, y,_get_function_body(callback));
}

function reset(callback)
{
    _ensure_browser_created();
    Browser.Reset(_get_function_body(callback));
}

function jquery(callback)
{
    _ensure_browser_created();
    Browser.Jquery(_get_function_body(callback));
}

function optimize(callback)
{
    _ensure_browser_created();
    Browser.OptimizeMemory(_get_function_body(callback));
}

function save_cookies(callback)
{
    _ensure_browser_created();
    Browser.SaveCookies(_get_function_body(callback));
}

function restore_cookies(cookies, callback)
{
    _ensure_browser_created();
    Browser.RestoreCookies(cookies, _get_function_body(callback));
}

function page()
{
    _ensure_browser_created();
    return ScriptWorker.GetRootElement();
}

function log(text)
{
    Logger.Write(ScriptWorker.PrepareMessage(text));
}

function log_html(html, text)
{
    Logger.WriteHtml(html, text);
}

function log_success(text)
{
    Logger.WriteSuccess(ScriptWorker.PrepareMessage(text));
}

function log_fail(text)
{
    Logger.WriteFail(ScriptWorker.PrepareMessage(text));
}

function ResultResolve(number)
{
    if(number === 0)
    {
        return Results1;
    }else if(number === 1)
    {
        return Results2;
    }else if(number === 2)
    {
        return Results3;
    }
    else if(number === 3)
        {
            return Results4;
        }

    else if(number === 4)
        {
            return Results5;
        }

    else if(number === 5)
        {
            return Results6;
        }

    else if(number === 6)
        {
            return Results7;
        }

    else if(number === 7)
        {
            return Results8;
        }

    else if(number === 8)
        {
            return Results9;
        }

}

function result(text, number)
{
    if(typeof(number) === "undefined")
    {
        number = 0;
    }
    ResultResolve(number).Write(text);
}

function result_html(html, text, number)
{
    if(typeof(number) === "undefined")
    {
        number = 0;
    }
    ResultResolve(number).WriteHtml(html, text);
}

function result_file(number)
{
    if(typeof(number) === "undefined")
    {
        number = 0;
    }
    return ResultResolve(number).GetFileName(number);
}

function css(text)
{
    _ensure_browser_created();
    return page().css(text);
}

function frame(name)
{
    _ensure_browser_created();
    return page().frame(name);
}


function position(x, y)
{
    _ensure_browser_created();
    return page().position(x,y);
}

function match(text)
{
    _ensure_browser_created();
    return page().match(text);
}

function match_all(text)
{
    _ensure_browser_created();
    return page().match_all(text);
}

function all(text)
{
    _ensure_browser_created();
    return page().all(text);
}

function thread_number()
{
    return ThreadNumber;
}

function sleep(milliseconds, callback)
{
    ScriptWorker.Sleep(milliseconds,_get_function_body(callback));
}

function script(text, callback)
{
    _ensure_browser_created();
    page().script(text,callback);
}

function agent(text, callback)
{
    _ensure_browser_created();
    Browser.SetUserAgent(text,_get_function_body(callback));
}


function antigate(key)
{
    ScriptWorker.GetSolver("antigate").SetProperty("key",key);
}

function antigate_russian(is_russian)
{
    ScriptWorker.GetSolver("antigate").SetProperty("is_russian",((is_russian)?"true":"false"));
}

function dbc(key)
{
    ScriptWorker.GetSolver("dbc").SetProperty("key",key);
}

function solve(match, url, callback)
{
    _ENGINE_CALLBACK = [match,url,callback];

    is_load(_ENGINE_CALLBACK[1], function(){
        if(_result() === false)
        {
            fail("CAPTCHA_FAIL : No image in cache");
        }
        cache_get_base64(_ENGINE_CALLBACK[1],function(){
            ScriptWorker.Solve(_ENGINE_CALLBACK[0], _result(),_get_function_body(_ENGINE_CALLBACK[2]));
        })
    })
}


function solve_base64(match, data_base64, callback)
{
    ScriptWorker.Solve(match, data_base64,_get_function_body(callback));
}

function progress()
{
    progress_value(-1);
}

function progress_value(val)
{
    ScriptWorker.ProgressValueSlot(val);
}

function progress_maximum(val)
{
    ScriptWorker.ProgressMaximumSlot(val);
}

function suspend(milliseconds, callback)
{
    SUSPEND_MILLISECONDS = milliseconds;
    SUSPEND_CALLBACK = callback;

    if(typeof(NetworkAccessManager)!='undefined')
    {

        save_cookies(function(){
            SUSPEND_COOKIES = _result();

            ScriptWorker.Suspend(SUSPEND_MILLISECONDS,"new_browser(function(){restore_cookies(SUSPEND_COOKIES," + SUSPEND_CALLBACK.toString() + ")});");
        })
    }
    else
    {
        ScriptWorker.Suspend(SUSPEND_MILLISECONDS,_get_function_body(SUSPEND_CALLBACK));
    }



}

function on_fail(callback)
{
    ScriptWorker.SetFailFunction(_get_function_body(callback));
}

function clear_on_fail()
{
    ScriptWorker.SetFailFunction("");
}

function on_success(callback)
{
    ScriptWorker.SetSuccessFunction(_get_function_body(callback));
}

function clear_on_success()
{
    ScriptWorker.SetSuccessFunction("");
}


function _on_fail(callback)
{
    var label = rand()
    _set_label(label)
    ScriptWorker.SetFailFunction("_rewind('" + label + "');" + _get_function_body(callback));
}

function _on_fail_exceed(callback)
{
    var label = rand()
    _set_label(label)
    ScriptWorker.SetFailExceedFunction("_rewind('" + label + "');" + _get_function_body(callback));
}

function _on_success_exceed(callback)
{
    var label = rand()
    _set_label(label)
    ScriptWorker.SetSuccessExceedFunction("_rewind('" + label + "');" + _get_function_body(callback));
}

function _finnaly(callback)
{
    ScriptWorker.SetAbortFunction(_get_function_body(callback));
}

function _clear_on_fail()
{
    ScriptWorker.SetFailFunction("");
}

function _on_success(callback)
{
    var label = rand()
    _set_label(label)
    ScriptWorker.SetSuccessFunction("_rewind('" + label + "');" + _get_function_body(callback));
}

function _clear_on_success()
{
    ScriptWorker.SetSuccessFunction("");
}

function _set_max_fail(max_fail_number)
{
    ScriptWorker.SetMaxFail(max_fail_number);
}

function _set_max_success(max_success_number)
{
    ScriptWorker.SetMaxSuccess(max_success_number);
}


function DEC(callback)
{
    ScriptWorker.Decrypt(callback);
}

function db_add_record(group_id, data_list, table_id)
{
    ScriptWorker.DatabaseAddRecord(group_id, data_list, table_id);
}

function _on_start()
{
    if(typeof(OnApplicationStart) == "undefined")
    {
        _break(1)
        return
    }

    _do(function(){
        APP_START = P("_","_s")
        if(APP_START == "2")
        {
            _break(2)
            return
        }
        if(APP_START == "")
        {
            PSet("_","_s","1")
            _break(1)
            return
        }
        sleep(1000, function(){})
    }, function(){
        _call(OnApplicationStart,null, function(){
            PSet("_","_s","2")
            success("none")
        })
    })
}
