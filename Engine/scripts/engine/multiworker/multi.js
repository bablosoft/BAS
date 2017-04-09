function section(threads_number, maximum_success, maximum_failure, maximum_run_time, worker_function, callback)
{
    MultiScriptWorker.RunStage(threads_number,maximum_success,maximum_failure, maximum_run_time,_get_function_body(worker_function),_get_function_body(callback));
}

function log(text)
{
    Logger.Write(text);
}

function log_html(html, text)
{
    Logger.WriteHtml(html, text);
}

function log_success(text)
{
    Logger.WriteSuccess(text);
}

function log_fail(text)
{
    Logger.WriteFail(text);
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

function sleep(milliseconds, callback)
{
    MultiScriptWorker.Sleep(milliseconds,_get_function_body(callback));
}

function progress()
{
    progress_value(-1);
}

function progress_value(val)
{
    MultiScriptWorker.ProgressValueSlot(val);
}

function progress_maximum(val)
{
    MultiScriptWorker.ProgressMaximumSlot(val);
}

function _finnaly(callback)
{
    MultiScriptWorker.SetAbortFunction(_get_function_body(callback));
}

function DEC(callback)
{
    MultiScriptWorker.Decrypt(callback);
}

function _db_add_group(group_name, group_description, table_id)
{
    return MultiScriptWorker.DatabaseAddGroup(group_name, group_description, table_id);
}
