VAR_CYCLE_INDEX = 0
VAR_FOREACH_DATA = ""
LINK_REGEXP = /https?:\/\/(www\.)?[-a-zA-Z0-9@:%._\+~#=]{1,256}\.[a-z]{2,6}\b([-a-zA-Z0-9@:%_\+.~#?&//=]*)/g
VAR_FOR_EACH_CSS = "html"
VAR_FOR_EACH_MATCH = "a"
IF_ELSE_EXPRESSION = true;

function Cycle(Next,Break)
{
    this.OnFail = "";
    this.OnSuccess = "";

    {
        var c = CYCLES.Current()
        if(c)
        {
            this.OnFail = c.OnFail;
            this.OnSuccess = c.OnSuccess;
        }
    }

    this._Label = [];

    this._Break = Break;
    this._Next = Next;
    this._Argunments = null;
    this._Iterator = 0;
    this.WasNextOrBreak = false;

    this.Next = function()
    {
        this._Next(this._Iterator++);
    }

    this.SetLabel = function(label)
    {
        if(this._Label.indexOf(label)<0)
            this._Label.push(label);
    }

    this.Break = function(arg)
    {

        if(typeof(arg) === "string")
        {
            var c = CYCLES.Current();
            if(!c || c._Label.indexOf(arg)>=0)
                c = null

            while(c && c._Label.indexOf(arg)<0)
            {
                c = CYCLES.Pop();
            }

            if(c)
            {
                c._Break();
            }
        }else
        {
            if(arg >= CYCLES.Data.length)
            {
                arg = CYCLES.Data.length;
            }
            if(arg > 0)
            {
                var c = null
                for(var i = 0;i<arg;i++)
                    c = CYCLES.Pop();
                if(c)
                {
                    c._Break();
                }
            }
        }


    }

    this.Start = function()
    {
        CYCLES.Push(this);
        this.Next();
    }
}

function Cycles()
{
    this.Data = [];
    this.Result = null;
    this.Push = function(el)
    {
        this.Data.push(el)
        var c = CYCLES.Current()
        if(c)
        {
            ScriptWorker.SetFailFunction(c.OnFail);
            ScriptWorker.SetSuccessFunction(c.OnSuccess);
        }else
        {
            ScriptWorker.SetFailFunction("");
            ScriptWorker.SetSuccessFunction("");
        }
    }
    this.Pop = function()
    {
        var r = this.Data.pop()
        var c = CYCLES.Current()
        if(c)
        {
            ScriptWorker.SetFailFunction(c.OnFail);
            ScriptWorker.SetSuccessFunction(c.OnSuccess);
        }else
        {
            ScriptWorker.SetFailFunction("");
            ScriptWorker.SetSuccessFunction("");
        }

        return r;
    }
    this.Rewind = function(arg)
    {
        var c = CYCLES.Current();
        while(c && c._Label.indexOf(arg)<0)
        {
            CYCLES.Pop();
            c = CYCLES.Current();

        }
    }
    this.Current = function()
    {
        return (this.Data.length>0)? this.Data[this.Data.length - 1] : null;
    }
}
CYCLES = new Cycles();


function _next()
{

    var c = CYCLES.Current();

    if(c)
    {
        c.Next();
        _stop_subscript_execution();

    }
    else
        success("Ok");
}

function _next_or_section(id, callback)
{
    var c = CYCLES.Current();
    if(c)
    {
        c.Next();
        _stop_subscript_execution();
    }
    else
        section_start("test",id,callback)
}

function _kill_call_stack()
{
    VAR_CYCLE_INDEX = 0
    CYCLES = new Cycles();
}


function _break()
{
    var arg = 1;
    if(arguments.length === 1)
    {
        arg = arguments[0];
    }

    var c = CYCLES.Current();
    if(c)
    {
        c.Break(arg);
        _stop_subscript_execution();
    }
    /*else
        success("Ok");*/

}

function _iterator()
{

    var c = CYCLES.Current();
    if(c)
    {
        return c._Iterator;
    }
    else
        return 0;

}


function _arguments()
{

    var c = CYCLES.Current();
    if(c)
    {
        return c._Arguments;
    }
    else
        return null;

}


function _do(n,b)
{
    var c = new Cycle(n,b);
    c.Start();
}

function _repeat(t,n,b)
{
    _do(function(i){
        if(i>t-1)
        {
            _break();
            return;
        }
        n(i);
    },b)
}

function _if(c,f,n)
{
    _do(function(i){
        if(i>0 || !c)
        {
            _break();
            return;
        }
        f();
    },n)

}

function _if_else(c, f1, f2,n)
{
    _do(function(i){
        if(i>0)
        {
            _break();
            return;
        }
        if(c)
            f1();
        else
            f2();

    },n)
}


function _call(f,a,n)
{
    var c = new Cycle(function(i){
        if(i>0)
        {
            _break();
            return;
        }
        f();

    },n);
    c._Arguments = a;
    c.Start();

}

function _result()
{
    return CYCLES.Result
}

function _set_result(val)
{
    CYCLES.Result = val;
}

function _return(val)
{
    CYCLES.Result = val
    _stop_subscript_execution()
}


function _set_label(label)
{
    var c = CYCLES.Current();
    if(c)
        c.SetLabel(label);
}

function _rewind(arg)
{
    CYCLES.Rewind(arg);
}

