

function _ensure_pop3_client()
{
    if(typeof(Pop3Client)=='undefined')
        die("Pop3Client is not accessible, try to create new pop3 client with new_pop3_client() command")
}

function new_pop3_client()
{
    ScriptWorker.NewPop3Client()
}

function pop3_client_set_config(host, port, username, password, encryption)
{
    _ensure_pop3_client();
    Pop3Client.SetHost(host);
    Pop3Client.SetPort(port);
    Pop3Client.SetUserName(username);
    Pop3Client.SetPassword(password);
    Pop3Client.SetEncryptionString(encryption);
}

function pop3_client_proxy(proxy_string)
{
    _ensure_pop3_client();
    var proxy_parsed = proxy_parse(proxy_string);
    pop3_client_set_proxy(proxy_parsed["server"], proxy_parsed["Port"], proxy_parsed["IsHttp"], proxy_parsed["name"], proxy_parsed["password"])
}

function pop3_client_was_error()
{
    return !Pop3Client.GetStatus();
}

function pop3_client_error_string()
{
    return Pop3Client.GetLastError();
}

function pop3_client_set_proxy(server, Port, IsHttp, name, password)
{
    _ensure_pop3_client();
    Pop3Client.SetProxy(server, Port, IsHttp, name, password);
}

function pop3_client_pull_messages_length(callback)
{
    _ensure_pop3_client()
    ScriptWorker.Pop3ClientLoadMessageNumber(_get_function_body(callback));
}

function pop3_client_pull_message(index, callback)
{
    _ensure_pop3_client()
    ScriptWorker.Pop3ClientLoadMessage(index, _get_function_body(callback));
}

function pop3_client_messages_length()
{
    _ensure_pop3_client()
    return Pop3Client.GetNumberOfMessages();
}


function pop3_client_body()
{
    _ensure_pop3_client()
    return Pop3Client.GetMessageBody();
}

function pop3_client_subject()
{
    _ensure_pop3_client()
    return Pop3Client.GetMessageSubject();
}

function pop3_client_sender()
{
    _ensure_pop3_client()
    return Pop3Client.GetMessageSender();
}


