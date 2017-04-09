_BROWSERAUTOMATIONSTUDIO_TARGET = ""

function _set_target(target)
{
    _BROWSERAUTOMATIONSTUDIO_TARGET = target
}

function _get_target()
{
    var res = "";

    if(typeof(_BROWSERAUTOMATIONSTUDIO_TARGET) != "string")
    {
        try{
            _BROWSERAUTOMATIONSTUDIO_TARGET["tab"] = _BROWSERAUTOMATIONSTUDIO_TARGET["tab"].toString()
        }catch(e){}
        res = JSON.stringify(_BROWSERAUTOMATIONSTUDIO_TARGET)
    }

    _BROWSERAUTOMATIONSTUDIO_TARGET = ""
    return res
}

function _get_network_access_manager()
{
    if(typeof(NetworkAccessManager)=='undefined')
        die("NetworkAccessManager is not accessible try to create new browser with browser()! command")
    return NetworkAccessManager;
}

function header(name, value, callback)
{
    _get_network_access_manager().AddHeader(name, value, _get_target(), _get_function_body(callback));
}

function header_order(json, callback)
{
    _get_network_access_manager().SetHeaderList(JSON.stringify(json), _get_function_body(callback));
}

function clear_header(callback)
{
    _get_network_access_manager().CleanHeader(_get_function_body(callback));
}

function proxy(proxy_string, callback)
{
    var proxy_parsed = proxy_parse(proxy_string);
    set_proxy(proxy_parsed["server"], proxy_parsed["Port"], proxy_parsed["IsHttp"], proxy_parsed["name"], proxy_parsed["password"], callback)
}

function set_proxy(server, Port, IsHttp, name, password, callback)
{
    _get_network_access_manager().SetProxy(server, Port, IsHttp, name, password,_get_target(),_get_function_body(callback))
}

function cache_allow(match, callback)
{
    _get_network_access_manager().AddCacheMaskAllow(match,_get_function_body(callback))
}

function cache_deny(match, callback)
{
    _get_network_access_manager().AddCacheMaskDeny(match,_get_function_body(callback))
}

function request_allow(match, callback)
{
    _get_network_access_manager().AddRequestMaskAllow(match,_get_function_body(callback))
}

function request_deny(match, callback)
{
    _get_network_access_manager().AddRequestMaskDeny(match,_get_function_body(callback))
}

function cache_get_base64(match, callback)
{
    _get_network_access_manager().FindCacheByMaskBase64(match,_get_function_body(callback))
}

function cache_get_string(match, callback)
{
    _get_network_access_manager().FindCacheByMaskString(match,_get_function_body(callback))
}

function cache_get_status(match, callback)
{
    _get_network_access_manager().FindStatusByMask(match,_get_function_body(callback))
}

function cache_clear(callback)
{
    _get_network_access_manager().ClearAll(_get_function_body(callback))
}

function cache_data_clear(callback)
{
    _get_network_access_manager().ClearData(_get_function_body(callback))
}

function cache_masks_clear(callback)
{
    _get_network_access_manager().ClearMasks(_get_function_body(callback))
}

function is_load(match, callback)
{
    _get_network_access_manager().IsUrlLoadedByMask(match,_get_function_body(callback))
}

function get_load_stats(callback)
{
    _get_network_access_manager().GetLoadStats(_get_function_body(callback))
}

function _restrict_popups(callback)
{
    _get_network_access_manager().RestrictPopups(_get_function_body(callback))
}

function _allow_popups(callback)
{
    _get_network_access_manager().AllowPopups(_get_function_body(callback))
}

function _restrict_downloads(callback)
{
    _get_network_access_manager().RestrictDownloads(_get_function_body(callback))
}

function _allow_downloads(callback)
{
    _get_network_access_manager().AllowDownloads(_get_function_body(callback))
}
