VAR_WAS_ERROR = false;
VAR_LAST_ERROR = "";
_BAS_SOLVER_PROPERTIES = {}

function _ensure_browser_created()
{
    if(typeof(NetworkAccessManager)=='undefined' || NetworkAccessManager == null)
        die("NetworkAccessManager is not accessible, try to create new browser with open browser command")
}

function _simulate_crush(callback)
{
    _ensure_browser_created();
    Browser.SimulateCrush(_get_function_body(callback));
}

function _settings(json, callback)
{
    Browser.SendWorkerSettings(JSON.stringify(json), "if(_result())ScriptWorker.AttachNetworkAccessManager();" + _get_function_body(callback))
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

open_browser = browser;

function close_browser()
{
    if(!ScriptWorker.GetIsRecord())
    {
        Browser.CloseBrowser();
        NetworkAccessManager = null;
    }
}

function mouse(x, y, callback)
{
    _ensure_browser_created();
    Browser.MouseClick(x,y,_get_function_body(callback))
}

function mouse_up(x, y, callback)
{
    _ensure_browser_created();
    Browser.MouseClickUp(x,y,_get_function_body(callback))
}

function mouse_down(x, y, callback)
{
    _ensure_browser_created();
    Browser.MouseClickDown(x,y,_get_function_body(callback))
}

function timezone(offset, callback)
{
    _ensure_browser_created();
    Browser.Timezone(offset,_get_function_body(callback))
}

function geolocation(latitude,longitude,callback)
{
    _ensure_browser_created();
    Browser.Geolocation(latitude,longitude,_get_function_body(callback))
}

function popupclose(index, callback)
{
    _ensure_browser_created();
    Browser.PopupClose(index,_get_function_body(callback))
}

function popupselect(index, callback)
{
    _ensure_browser_created();
    Browser.PopupSelect(index,_get_function_body(callback))
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

_DEFAULT_MOVE_PARAMS = {}

function _default_move_params(params)
{
    _DEFAULT_MOVE_PARAMS = params
}

function move()
{
    var length = arguments.length

    var x = arguments[0]
    var y = arguments[1]
    var params = arguments[2]
    var callback = arguments[3]


    if(length == 4)
    {
        x = arguments[0]
        y = arguments[1]
        params = arguments[2]
        callback = arguments[3]
    }else if(length == 3)
    {
        x = arguments[0]
        y = arguments[1]
        params = {}
        callback = arguments[2]
    }else if(length == 2)
    {
        X = parseInt(_result().split(",")[0])
        Y = parseInt(_result().split(",")[1])
        x = X
        y = Y
        params = arguments[0]
        callback = arguments[1]
    }else if(length == 1)
    {
        X = parseInt(_result().split(",")[0])
        Y = parseInt(_result().split(",")[1])
        x = X
        y = Y
        callback = arguments[0]
    }else
    {
        fail("move, wrong number of arguments")
    }

    if(Object.keys(params).length == 0)
    {
        params = _DEFAULT_MOVE_PARAMS
    }
    _ensure_browser_created();
    Browser.MouseMove(x,y,JSON.stringify(params),_get_function_body(callback))
}

function _clarify()
{
    _MOUSE_SETTINGS = _arguments()
    _if(_result().length > 0, function(){
        X = parseInt(_result().split(",")[0])
        Y = parseInt(_result().split(",")[1])
        move(X,Y, _MOUSE_SETTINGS, function(){
            delete _MOUSE_SETTINGS
        })
    }, function(){delete _MOUSE_SETTINGS})
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
    Browser.LoadPage(text,"if(_result() == false){fail(tr('Failed to load page ') + LOAD_TEXT)};" + _get_function_body(callback));
}

function load_instant(text, callback)
{
    _ensure_browser_created();
    Browser.LoadPageInstant(text,_get_function_body(callback));
}

function open_file_dialog(text, callback)
{
    _ensure_browser_created();
    var sendtext = text
    if(text instanceof Array)
        sendtext = JSON.stringify(text)
    Browser.SetOpenFileName(sendtext,_get_function_body(callback));
}

function prompt_result(text, callback)
{
    _ensure_browser_created();
    Browser.SetPromptResult(text,_get_function_body(callback));
}

function http_auth_result(login, pass, callback)
{
    _ensure_browser_created();
    Browser.SetHttpAuthResult(login,pass,_get_function_body(callback));
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
    _DEFAULT_MOVE_PARAMS = {}
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

function restore_localstorage(localstorage, callback)
{
    _ensure_browser_created();
    Browser.RestoreLocalStorage(localstorage, _get_function_body(callback));
}

function page()
{
    _ensure_browser_created();
    return ScriptWorker.GetRootElement();
}

function clear_log()
{
    Logger.Clear();
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

function frame_css(name)
{
    _ensure_browser_created();
    return page().frame_css(name);
}

function xpath(name)
{
    _ensure_browser_created();
    return page().xpath(name);
}

function xpath_all(name)
{
    _ensure_browser_created();
    return page().xpath_all(name);
}

function frame_match(name)
{
    _ensure_browser_created();
    return page().frame_match(name);
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
    return ScriptWorker.GetThreadNumber();
}

function success_number()
{
    return ScriptWorker.GetSuccessNumber();
}

function project_path()
{
    return ScriptWorker.GetProjectPath();
}

function fail_number()
{
    return ScriptWorker.GetFailNumber();
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

function font_list(fonts, callback)
{
    _ensure_browser_created();
    Browser.SetFontList(fonts,_get_function_body(callback));
}


function onloadjavascript(text, callback)
{
    _ensure_browser_created();
    Browser.SetStartupScript(text,"Main",_get_target(),_get_function_body(callback));
}

function onloadjavascriptinternal(text, script_id, callback)
{
    _ensure_browser_created();
    Browser.SetStartupScript(text,script_id,_get_target(),_get_function_body(callback));
}

function agent(text, callback)
{
    _ensure_browser_created();
    Browser.SetUserAgent(text,_get_function_body(callback));
}


function antigate(key)
{
    solver_property("antigate","key",key)
}

function rucaptcha(key)
{
    solver_property("rucaptcha","key",key)
}

function twocaptcha(key)
{
    solver_property("2captcha","key",key)
}

function capmonster(key)
{
    solver_property("capmonster","key",key)
}

function solver_properties_clear(solver)
{
    _BAS_SOLVER_PROPERTIES[solver] = {}
}

function solver_property(solver,key,value)
{
    var h;
    if(!(solver in _BAS_SOLVER_PROPERTIES && _BAS_SOLVER_PROPERTIES[solver]))
    {
        _BAS_SOLVER_PROPERTIES[solver] = {}
    }
    h = _BAS_SOLVER_PROPERTIES[solver]

    h[key] = value

    _BAS_SOLVER_PROPERTIES[solver] = h
}

function dbc(key)
{
    solver_property("dbc","key",key)
}

function _solver_properties_list(solver)
{
    var h;
    if(!(solver in _BAS_SOLVER_PROPERTIES && _BAS_SOLVER_PROPERTIES[solver]))
        _BAS_SOLVER_PROPERTIES[solver] = {}

    h = _BAS_SOLVER_PROPERTIES[solver]
    return Object.keys(h).reduce(function(a,k){a.push(k);a.push(h[k]);return a},[])
}

function solve(match, url, callback)
{
    LAST_CAPTCHA_METHOD = match
    _ENGINE_CALLBACK = [match,url,callback];

    is_load(_ENGINE_CALLBACK[1], function(){
        if(_result() === false)
        {
            fail("CAPTCHA_FAIL : No image in cache");
        }
        cache_get_base64(_ENGINE_CALLBACK[1],function(){
            ScriptWorker.Solve(_ENGINE_CALLBACK[0], _result(),_solver_properties_list(_ENGINE_CALLBACK[0]),_get_function_body(_ENGINE_CALLBACK[2]));
        })
    })
}


function solve_base64(match, data_base64, callback)
{
    LAST_CAPTCHA_METHOD = match
    ScriptWorker.Solve(match, data_base64,_solver_properties_list(match),_get_function_body(callback));
}

function solve_base64_no_fail(match, data_base64, callback)
{
    LAST_CAPTCHA_METHOD = match
    ScriptWorker.SolveNoFail(match, data_base64,_solver_properties_list(match),_get_function_body(callback));
}

function solver_failed()
{
    if(typeof(LAST_CAPTCHA_ID) != "undefined" && LAST_CAPTCHA_ID != "")
        ScriptWorker.GetSolver(LAST_CAPTCHA_METHOD).ReportBad(LAST_CAPTCHA_ID);
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
    var c = CYCLES.Current()
    if(c)
        c.OnFail = "_rewind('" + label + "');" + _get_function_body(callback)
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
    var c = CYCLES.Current()
    if(c)
        c.OnFail = ""

    ScriptWorker.SetFailFunction("");
}

function _on_success(callback)
{
    var label = rand()
    _set_label(label)
    var c = CYCLES.Current()
    if(c)
        c.OnSuccess = "_rewind('" + label + "');" + _get_function_body(callback)
    ScriptWorker.SetSuccessFunction("_rewind('" + label + "');" + _get_function_body(callback));
}

function _clear_on_success()
{
    var c = CYCLES.Current()
    if(c)
        c.OnSuccess = ""

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

function _db_add_record(group_id, data_list, table_id)
{
    return ScriptWorker.DatabaseAddRecord(group_id, data_list, table_id);
}
function _db_select_records(selector, page_number,page_size, table_id)
{
    return ScriptWorker.DatabaseSelectRecords(JSON.stringify(selector),page_number,page_size, table_id);
}

function _db_delete_records(selector, table_id)
{
    return ScriptWorker.DatabaseDeleteRecords(JSON.stringify(selector),table_id);
}


function _db_update_record(record_id, data_list, table_id)
{
    return ScriptWorker.DatabaseUpdateRecord(record_id, data_list, table_id);
}

function _db_add_group(group_name, group_description, table_id)
{
    return ScriptWorker.DatabaseAddGroup(group_name, group_description, table_id);
}


function _on_start()
{
    if(ScriptWorker.SubstageGetParentId() > 0)
    {
        _call(eval(ScriptWorker.SubstageGetStartingFunction()), null, function(){
            success("")
        })
        return
    }

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

function native(dll,func,data)
{
    return ScriptWorker.ExecuteNativeModuleCodeSync(dll,func,data);
}

function native_async(dll,func,data,callback)
{
    ScriptWorker.ExecuteNativeModuleCodeAsync(dll,func,data,_get_function_body(callback));
}

function general_timeout_next(timeout)
{
    ScriptWorker.SetGeneralWaitTimeoutNext(timeout);
}

function general_timeout(timeout)
{
    ScriptWorker.SetGeneralWaitTimeout(timeout);
    BROWSERAUTOMATIONSTUDIO_WAIT_TIMEOUT = Math.floor(timeout/1000);
}

function async_load_timeout(timeout)
{
    BROWSERAUTOMATIONSTUDIO_FULL_LOAD_TIMEOUT = Math.floor(timeout/1000);
}

function solver_timeout_next(timeout)
{
    ScriptWorker.SetSolverWaitTimeoutNext(timeout);
}

function solver_timeout(timeout)
{
    ScriptWorker.SetSolverWaitTimeout(timeout);
}

function _preprocess(script)
{
    return ScriptWorker.Preprocess(script);
}
