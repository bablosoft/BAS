_R = {}
_RKEY = null

function RS(key, notreuse, onlyfail, callback)
{
    IS_REFUSED=false


    if(!notreuse && !onlyfail)
    {
        // Reuse and die on non exists

        if(key in _R && _R[key])
        {
            _set_result(_R[key]);
            callback();
            return;
        }

        _RKEY = key
        MultiScriptWorker.GetHandler(key,true,"_R[_RKEY]=_result();" + _get_function_body(callback));
    }else if(notreuse && !onlyfail)
    {
        if(key in _R && _R[key])
        {
            _R[key].success()
            _R[key] = null
        }

        _RKEY = key
        MultiScriptWorker.GetHandler(key,true,"_R[_RKEY]=_result();" + _get_function_body(callback));
    }else if(!notreuse && onlyfail)
    {
        if(key in _R && _R[key])
        {
            _set_result(_R[key]);
            callback();
            return;
        }

        _RKEY = key
        MultiScriptWorker.GetHandler(key,false,"if(_result() == null){fail('Resource get error for ' + _RKEY);return;}else{_R[_RKEY]=_result();}" + _get_function_body(callback));

    }else if(notreuse && onlyfail)
    {
        if(key in _R && _R[key])
        {
            _R[key].success()
            _R[key] = null
        }

        _RKEY = key
        MultiScriptWorker.GetHandler(key,false,"if(_result() == null){fail('Resource get error for ' + _RKEY);return;}else{_R[_RKEY]=_result();}" + _get_function_body(callback));
    }
}

function R(key, callback)
{
    MultiScriptWorker.GetHandler(key,true,_get_function_body(callback));
}

function Reload(key)
{
    MultiScriptWorker.ReloadResource(key);
}

function Remove(key)
{
    MultiScriptWorker.RemoveResource(key);
}

function RSafe(key, callback)
{
    MultiScriptWorker.GetHandler(key,false,_get_function_body(callback));
}

function RCreate(name, successes, fails, simultaneous, interval, greedy, dont_give_up)
{
    EngineRes.Create(name, successes, fails, simultaneous, interval, greedy, dont_give_up)
}


function RInsert(name, value)
{
    EngineRes.Insert(name, value)
}

function RTake(name, callback)
{
    ARG_RES_NAME = name;
    RTakeAll_RESULT = [];
    _do(function(){
        RSafe(ARG_RES_NAME, function(){
            if(_result() === null)
            {
                _set_result(RTakeAll_RESULT);
                _break();
            }
            RTakeAll_RESULT.push(_result().get());
            _result().die()
        });

    }, callback)

}

function RInfo(name, key)
{
    return EngineRes.GetInfo(name, key);
}


function RPick(name)
{
    return MultiScriptWorker.GetAllData(name)
}


function RPickRandom(name, size)
{
    return MultiScriptWorker.GetRandomSubarrayData(name,size)
}

function RMap(name)
{
    function Map(_name){
      var __name = _name;
      this.length = function()
      {
          return MultiScriptWorker.GetTotalLength(__name);
      }
      this.at = function(index)
      {
           return MultiScriptWorker.GetAtIndex(__name,index);
      }
      this.set = function(index,value)
      {
           return MultiScriptWorker.SetAtIndex(__name,index,value);
      }

    };
    return new Map(name);
}
