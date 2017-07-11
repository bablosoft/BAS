function _stop_subscript_execution()
{
    ScriptWorker.AbortSubscript();
}

function fail(text, dont_create_more)
{
    /*var c = CYCLES.Current()
    if(c)
        ScriptWorker.SetFailFunction(c.OnFail);
    else
        ScriptWorker.SetFailFunction("");*/

    ScriptWorker.Fail(text,dont_create_more);
}

function die(text, instant)
{
    ScriptWorker.Die(text,instant);
}

function success(text)
{
    /*var c = CYCLES.Current()
    if(c)
        ScriptWorker.SetSuccessFunction(c.OnSuccess);
    else
        ScriptWorker.SetSuccessFunction("");*/

    ScriptWorker.Success(text);
}

function debug_variables(list, callback)
{
    var res = {}

    for(var i = 0;i<list.length;i++)
    {
        var v = list[i]
        if(v.indexOf("GLOBAL:") == 0)
        {
            res[v] = JSON.parse(P("basglobal",v.slice(7)) || '""');
        }else
        {

            try
            {
                res[v.slice(4)] = eval(v)
            }catch(e)
            {
                res[v.slice(4)] = "undefined"
            }
        }
    }

    Browser.DebugVariablesResult(JSON.stringify(res),_get_function_body(callback));
}



