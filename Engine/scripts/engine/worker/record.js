function section_start(name, id, callback)
{
    _sa(id)
    Browser.StartSection(name,id,_get_function_body(callback));
}

function _sa(id)
{
    ScriptWorker.SetCurrentAction(id)
}

function section_insert()
{
}
