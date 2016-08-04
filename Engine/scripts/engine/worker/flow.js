function _stop_subscript_execution()
{
    ScriptWorker.AbortSubscript();
}

function fail(text)
{
    ScriptWorker.Fail(text);
}

function die(text)
{
    ScriptWorker.Die(text);
}

function success(text)
{
    ScriptWorker.Success(text);
}

function debug_variables(list, callback)
{
    var res = {}

    for(var i = 0;i<list.length;i++)
    {
        var v = list[i]
        try
        {
            res[v.slice(4)] = eval(v)
        }catch(e)
        {
            res[v.slice(4)] = "undefined"
        }
    }

    Browser.DebugVariablesResult(JSON.stringify(res),_get_function_body(callback));
}
