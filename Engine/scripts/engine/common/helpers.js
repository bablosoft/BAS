function _get_function_body(f)
{
    if(!f)
    {
        die("Callback is empty. Did you forget to use '!' after function?")
        return;
    }
    var s = f.toString();
    return s.substring(s.indexOf("{") + 1, s.lastIndexOf("}"));
}

function rand(v1,v2,v3)
{
    if(typeof(v1) == "number" && typeof(v2) == "number" && typeof(v3) == "object")
    {
        var l = Math.floor(Math.random() * (v2 - v1 + 1)) + v1;
        var res = []
        for(var i=0; i<l; i++)
        {
            var max = v3.length - 1;
            if(max<0)
                break;
            var r = Math.floor(Math.random() * (max + 1));
            res.push(v3.splice(r,1)[0])
        }
        return res;

    }else if(typeof(v1) == "number" && typeof(v2) == "number")
        return Math.floor(Math.random() * (v2 - v1 + 1)) + v1;
    else if(typeof(v1) == "number" && typeof(v2) == "undefined" || typeof(v1) == "number" && typeof(v2) == "string" || typeof(v1) == "undefined" && typeof(v2) == "undefined")
    {
        var possible = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        var len = 10;
        if(typeof(v1) == "number")
        {
            len = v1;
        }
        if(typeof(v2) == "string")
        {
            possible = v2;
        }

        var text = "";

        for( var i=0; i < len; i++ )
            text += possible.charAt(Math.floor(Math.random() * possible.length));

        return text;

    }
    return;
}

function _spintax(text)
{
    return ScriptWorker.Spintax(text);
}


function proxy_parse(proxy_string)
{
    var server = "";
    var Port = 0;
    var name = "";
    var password = "";
    var IsHttp = true;
    proxy_string = proxy_string
    proxy_string = proxy_string.replace(new RegExp("@",'g'),":");
    proxy_string = proxy_string.replace(new RegExp("\\\\",'g'),":");
    proxy_string = proxy_string.replace(new RegExp("\\/",'g'),":");
    proxy_string = proxy_string.replace(new RegExp("\\s",'g'),"");

    var ipv6regexp = new RegExp("\\[[^\\]]+\\]");
    var ipv6match = proxy_string.match(ipv6regexp)
    var ipv6addr = ""
    if(ipv6match)
    {
        ipv6addr = ipv6match[0]
        proxy_string = proxy_string.replace(ipv6regexp,"127.0.0.1");
    }


    var list = proxy_string.split(":")
    for(var i = 0;i<list.length;i++)
    {
        var el = list[i]
        if(el.toLowerCase() === "sock" || el.toLowerCase() === "socks5" || el.toLowerCase() === "socks4" || el.toLowerCase() === "socks")
        {
           IsHttp = false;
           continue;
        }
        if(el.toLowerCase() === "http" || el.toLowerCase() === "https" || el.toLowerCase() === "ftp")
        {
           IsHttp = true;
           continue;
        }

        if(el.length > 0 && el.length <= 5 && /^\d+$/.test(el))
        {
           Port = parseInt(el);
           continue;
        }
        if(server.length == 0 && el.indexOf(".")>=0)
        {
            server = el
            if(ipv6addr.length>0)
            {
                server = server.replace("127.0.0.1",ipv6addr)
            }
            continue;
        }
        if(el.length>0)
        {
            if(name.length == 0)
            {
                name = el;
            }else if(password.length == 0)
            {
                password = el;
            }
        }

    }
    return {server: server, Port: Port, IsHttp: IsHttp, name: name, password: password};

}

function proxy_pack(proxy_hash)
{
    var res = "";
    if(proxy_hash.IsHttp === false)
    {
        res += "socks5@"
    }
    res += proxy_hash.server + "@" + proxy_hash.Port.toString()
    if(proxy_hash.name.length > 0)
    {
        res += "@" + proxy_hash.name + "@" + proxy_hash.password
    }
    return res;
}

function parse_json(json)
{
    try
    {
        return JSON.parse(json)
    }catch(e)
    {
        var o = json
        if(json.length > 300)
            o = json.substring(0,300) + "..."
        fail("error parsing json " + o)
    }

}

function md5(string)
{
    return Helper.md5(string);
}

function base64_encode(string)
{
    return Helper.base64_encode(string);
}

function base64_decode(string)
{
    return Helper.base64_decode(string);
}

function file_read(filename)
{
    return Helper.file_read(filename);
}

function file_read_base64(filename)
{
    return Helper.file_read_base64(filename);
}

function file_write(filename, data)
{
    Helper.file_write(filename, data);
}

function file_write_base64(filename, data)
{
    Helper.file_write_base64(filename, data);
}

function file_append(filename, data)
{
    Helper.file_append(filename, data);
}

function file_append_base64(filename, data)
{
    Helper.file_append_base64(filename, data);
}

function directory_of(filename)
{
    return Helper.directory_of(filename);
}

function directory_create(dir)
{
    return Helper.directory_create(dir);
}

function filename_of(filename)
{
    return Helper.filename_of(filename);
}


function combine_path(path1, path2)
{
    return Helper.combine_path(path1, path2);
}

function encode_string(string,codec)
{
    return Helper.encode_string(string, codec);
}

function image_get_dimension(image_data_base64)
{
    return Helper.image_get_dimension(image_data_base64);
}

function image_central_crop(image_data_base64, x, y)
{
    return Helper.image_central_crop(image_data_base64,x,y);
}

function oauth1_header(auth_token, consumer_secret_key, consumer_public_key, url, method, realm, params)
{
    return Helper.oauth1_header(auth_token, consumer_secret_key, consumer_public_key, url, method, realm, params);
}

function csv_parse(line)
{
    return CsvHelper.Parse(line);
}

function csv_generate(string_array, separator)
{
    return CsvHelper.Generate(string_array, separator);
}

function date_format(date, format)
{
    return Helper.date_format(date, format);
}

function date_format_now(format)
{
    return Helper.date_format(new Date(), format);
}

function db_date_now()
{
    return Helper.date_format(new Date(), "yyyy-MM-ddTHH:mm:ss");
}
