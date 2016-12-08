_if(<%= service %> == "sms-reg.com", function(){
	var url = "http://api.sms-reg.com/getNum.php?country=all&service=" + _BAS_GETSMSSITECODE(<%= service %>, <%= site %>) + "&apikey=" + (<%= apikey %>)
	_call(_BAS_SMSREGAPIREQUEST,{method: "getNum", url: url})!
    var json = _result()
    _SMS_CONFIRM_DATA = {id: json["tzid"], api: (<%= apikey %>), method: "sms-reg.com", originalid: json["tzid"]}

    _SMS_MAX_WAIT = Date.now() + 600000
	_do(function(){
        if(Date.now() > _SMS_MAX_WAIT)
			fail("Sms Reg Error: Timeout for getState");

        var url = "http://api.sms-reg.com/getState.php?tzid=" + _SMS_CONFIRM_DATA["id"] + "&apikey=" + _SMS_CONFIRM_DATA["api"]
        _call(_BAS_SMSREGAPIREQUEST,{method: "getState", url: url, dontcheckresp: true})!
        var json = _result()

        
        if(json["response"] === "TZ_NUM_PREPARE")
        {
            _SMS_CONFIRM_DATA["number"] = json["number"]
        	_BAS_SMSCONFIRMDATA[json["number"]] = _SMS_CONFIRM_DATA
            _break()
        }

        if(json["response"] !== "TZ_INPOOL")
        {
            fail("Sms Reg Error: " + json["response"] + " for getNum");
        }

    })!

    <%= variable %> = _SMS_CONFIRM_DATA["number"]
})!


_if(<%= service %> == "sms-activate.ru", function(){
    _call(_BAS_SMSACTIVATEPIREQUEST,{api_key: (<%= apikey %>), action: "getNumber", service: _BAS_GETSMSSITECODE(<%= service %>, <%= site %>)})!
    var arr = _result()
    if(arr[0] == "NO_NUMBERS")
    {
        _sms_ban_service(60)
    }

    if(arr[0] != "ACCESS_NUMBER")
    {
        fail("Error during sms-activate getNumber " + arr.join(":"))
    }
    _SMS_CONFIRM_DATA = {id: arr[1], api: (<%= apikey %>), method: "sms-activate.ru", originalid: arr[1], number: arr[2]}
    _BAS_SMSCONFIRMDATA[arr[2] ] = _SMS_CONFIRM_DATA

    <%= variable %> = _SMS_CONFIRM_DATA["number"]
})!

_if(<%= service %> == "smspva.com", function(){
    _call(_BAS_SMSPVAREQUEST,{apikey: (<%= apikey %>), id: 1, metod: "get_number", service: _BAS_GETSMSSITECODE(<%= service %>, <%= site %>), country: "ru"})!
    var json = _result()
    if(json["response"] != "1")
    {
        fail("failed to get number from smspva " + JSON.stringify(json))
    }

    _SMS_CONFIRM_DATA = {id: json["id"], api: (<%= apikey %>), method: "smspva.com", originalid: json["id"], number: json["number"], service: _BAS_GETSMSSITECODE(<%= service %>, <%= site %>)}
    _BAS_SMSCONFIRMDATA[ "7" + json["number"] ] = _SMS_CONFIRM_DATA

    <%= variable %> = "7" + _SMS_CONFIRM_DATA["number"]
})!