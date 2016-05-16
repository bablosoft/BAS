

function _ensure_imap_client()
{
    if(typeof(ImapClient)=='undefined')
        new_imap_client();
}

function new_imap_client()
{
    ScriptWorker.NewImapClient()
}

function imap_client_set_config(host, username, password, port, encryption, inbox)
{
    _ensure_imap_client();
    ImapClient.SetHost(host);
    ImapClient.SetUserName(username);
    ImapClient.SetPassword(password);

    if(port)
        ImapClient.SetHostPort(port);

    if(encryption)
        ImapClient.SetEncryptionString(encryption);

    if(inbox)
        ImapClient.SetInboxFolder(inbox);


}

function imap_client_set_proxy(server, Port, IsHttp, name, password)
{
    _ensure_imap_client();
    ImapClient.SetProxy(server, Port, IsHttp, name, password);
}

function imap_client_proxy(proxy_string)
{
    _ensure_imap_client();
    var proxy_parsed = proxy_parse(proxy_string);
    imap_client_set_proxy(proxy_parsed["server"], proxy_parsed["Port"], proxy_parsed["IsHttp"], proxy_parsed["name"], proxy_parsed["password"])
}
function imap_client_was_error()
{
    _ensure_imap_client();
    return !ImapClient.GetStatus();
}

function imap_client_error_string()
{
    _ensure_imap_client();
    return ImapClient.GetLastError();
}

function imap_client_pull_messages_length(callback)
{
    _ensure_imap_client()
    ScriptWorker.ImapClientPullNumberOfMessages(_get_function_body(callback));
}

function imap_client_messages_length()
{
    _ensure_imap_client()
    return ImapClient.GetNumberOfMessages();
}

function imap_client_search(Sender,Subject,Body,callback)
{
    _ensure_imap_client()
    ScriptWorker.ImapClientSearchMessages(Sender,Subject,Body,_get_function_body(callback));
}

function imap_client_custom_search(Query,callback)
{
    _ensure_imap_client()
    ScriptWorker.ImapClientCustomSearchMessages(Query,_get_function_body(callback));
}

function imap_client_search_result()
{
    _ensure_imap_client()
    return ImapClient.GetSearchResult();
}

function imap_client_pull_message(Uid,callback)
{
    _ensure_imap_client()
    ScriptWorker.ImapClientPullMessage(Uid,_get_function_body(callback));
}

function imap_client_message()
{
    _ensure_imap_client()
    return ImapClient.GetLastMessage();
}

function imap_custom_query(url,command,filter,callback)
{
    _ensure_imap_client()
    ScriptWorker.ImapClientCustomQuery(url,command,filter,_get_function_body(callback));
}

function imap_custom_query_result()
{
    _ensure_imap_client()
    return ImapClient.CustomQueryResult();
}

function imap_custom_query_log()
{
    _ensure_imap_client()
    return ImapClient.CustomQueryLog();
}






