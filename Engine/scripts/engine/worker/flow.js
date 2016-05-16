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