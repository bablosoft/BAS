VAR_CYCLE_INDEX = 0
VAR_FOREACH_DATA = ""
LINK_REGEXP = /https?:\/\/(www\.)?[-a-zA-Z0-9@:%._\+~#=]{1,256}\.[a-z]{2,6}\b([-a-zA-Z0-9@:%_\+.~#?&//=]*)/g
VAR_FOR_EACH_CSS = "html"
VAR_FOR_EACH_MATCH = "a"
VAR_FOR_EACH_XPATH = "//html"
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

    this.Next = function(arg)
    {
        if(typeof(arg) === "number")
        {
            if(arg >= CYCLES.Data.length)
            {
                arg = CYCLES.Data.length;
            }
            if(arg > 0)
            {
                for(var i = 0;i<arg - 1;i++)
                {
                    CYCLES.Pop();
                }

                var c = CYCLES.Current();

                if(c)
                {
                    c._Next(c._Iterator++);
                }
            }
        }

        if(typeof(arg) === "undefined")
            this._Next(this._Iterator++);
    }

    this.SetLabel = function(label)
    {
        if(this._Label.indexOf(label)<0)
            this._Label.push(label);
    }

    this.HasLabel = function(label)
    {
        return this._Label.indexOf(label) >= 0;
    }

    this.RemoveLabel = function(label)
    {
        var index = this._Label.indexOf(label);
        if(index>=0)
            this._Label.splice(index,1);
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
    this.FindLabelDepth = function(label)
    {
        var res = 1
        for(var i = this.Data.length - 1;i>=0;i--)
        {
            var c = this.Data[i]
            if(c.HasLabel(label))
            {
                return res
            }
            res += 1
        }
        return -1
    }
}
CYCLES = new Cycles();


function _next()
{
    var usearg = false;
    var arg = 1;
    if(arguments.length === 1)
    {
        arg = arguments[0];
        usearg = true;
    }
    if(typeof(arg) == "string")
    {
        arg = CYCLES.FindLabelDepth(arg)
        if(arg === -1)
            return
    }

    var c = CYCLES.Current();
    if(c)
    {
        if(usearg)
            c.Next(arg);
        else
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
    if(typeof(arg) == "string")
    {
        arg = CYCLES.FindLabelDepth(arg)
        if(arg === -1)
            arg = 99999
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
    c.SetLabel("function");
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
        var cc = CYCLES.Current();
        if(cc)
            cc.RemoveLabel("function");
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
        var cc = CYCLES.Current();
        if(cc)
            cc.RemoveLabel("function");
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
    c.SetLabel("function");
    c._Arguments = a;
    c.Start();

}

function _call_section(func,threads,success_number,fail_number,callback)
{
    ScriptWorker.SubstageCall(func.name,threads,success_number,fail_number,_get_function_body(callback))
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

function _goto(label, callback)
{

    if(typeof(_BAS_GOTO_DATA) == "undefined" || !(label in _BAS_GOTO_DATA))
    {
        fail("Goto to non existing label " + label)
        return
    }
    _kill_call_stack()
    ScriptWorker.SetScript(_get_function_body(_BAS_GOTO_DATA[label]))
    ScriptWorker.RunSubScript()
}

function _fast_goto(label, callback)
{

    if(typeof(_BAS_GOTO_DATA) == "undefined" || !(label in _BAS_GOTO_DATA))
    {
        fail("Goto to non existing label " + label)
        return
    }
    ScriptWorker.SetScript(_get_function_body(_BAS_GOTO_DATA[label]))
    ScriptWorker.RunSubScript()
}
