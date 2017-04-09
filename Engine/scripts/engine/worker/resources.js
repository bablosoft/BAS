_R = {}
_RKEY = null

function _get_last_record_id(record)
{
    if(RInfo(_RKEY,'Type') === 'Database')
    {
        var res = csv_parse(_result().get())
        if(res.length > 0)
        {
            LAST_DATABASE_RECORD = res[res.length - 1];
        }
    }
}

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
        ScriptWorker.GetHandler(key,true,"_get_last_record_id();_R[_RKEY]=_result();" + _get_function_body(callback));
    }else if(notreuse && !onlyfail)
    {
        if(key in _R && _R[key])
        {
            _R[key].success()
            _R[key] = null
        }

        _RKEY = key
        ScriptWorker.GetHandler(key,true,"_get_last_record_id();_R[_RKEY]=_result();" + _get_function_body(callback));
    }else if(!notreuse && onlyfail)
    {
        if(key in _R && _R[key])
        {
            _set_result(_R[key]);
            callback();
            return;
        }

        _RKEY = key
        ScriptWorker.GetHandler(key,false,"_get_last_record_id();if(_result() == null){fail('Resource get error for ' + _RKEY);return;}else{_R[_RKEY]=_result();}" + _get_function_body(callback));

    }else if(notreuse && onlyfail)
    {
        if(key in _R && _R[key])
        {
            _R[key].success()
            _R[key] = null
        }

        _RKEY = key
        ScriptWorker.GetHandler(key,false,"_get_last_record_id();if(_result() == null){fail('Resource get error for ' + _RKEY);return;}else{_R[_RKEY]=_result();}" + _get_function_body(callback));
    }
}

function R(key, callback)
{
    IS_REFUSED=false
    ScriptWorker.GetHandler(key,true,_get_function_body(callback));
}

function RSafe(key, callback)
{
    IS_REFUSED=false
    ScriptWorker.GetHandler(key,false,_get_function_body(callback));
}

function Refuse(key, value)
{
    ScriptWorker.Refuse(key,value);
}

function RIsRefused()
{
    return IS_REFUSED;
}

function Reload(key)
{
    ScriptWorker.ReloadResource(key);
}

function RInsert(name, value, onlywrite)
{
    EngineRes.Insert(name, value, onlywrite)
}

function RSync(name)
{
    EngineRes.Sync(name)
}

function RCreate(name, successes, fails, simultaneous, interval, greedy, dont_give_up)
{
    EngineRes.Create(name, successes, fails, simultaneous, interval, greedy, dont_give_up)
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

function RSuccessAll()
{
    return ResourceHandlers.Success()
}
function RFailAll()
{
    return ResourceHandlers.Fail()
}
function RDieAll()
{
    return ResourceHandlers.Die()
}

function RInfo(name, key)
{
    return EngineRes.GetInfo(name, key);
}

function RPick(name)
{
    return ScriptWorker.GetAllData(name)
}

function RPickRandom(name, size)
{
    return ScriptWorker.GetRandomSubarrayData(name,size)
}

function RMap(name)
{
    function Map(_name){
      var __name = _name;
      this.length = function()
      {
          return ScriptWorker.GetTotalLength(__name);
      }
      this.at = function(index)
      {
           return ScriptWorker.GetAtIndex(__name,index);
      }
      this.set = function(index,value)
      {
           return ScriptWorker.SetAtIndex(__name,index,value);
      }

    };
    return new Map(name);
}
