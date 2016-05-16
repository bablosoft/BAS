function section_start(name, id, callback)
{
    Browser.StartSection(name,id,_get_function_body(callback));
}

function section_insert()
{
}
