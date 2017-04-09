_SMS_CONFIRM_DATA = _BAS_SMSCONFIRMDATA[<%= number %>]
    if(!_SMS_CONFIRM_DATA)
        fail("No information about this number")


_if(_SMS_CONFIRM_DATA["method"] == "sms-reg.com", function(){
    _if(_SMS_CONFIRM_DATA["not_first"], function(){

        var url = "http://api.sms-reg.com/getNumRepeat.php?tzid=" + _SMS_CONFIRM_DATA["originalid"] + "&apikey=" + _SMS_CONFIRM_DATA["api"]
        _call(_BAS_SMSREGAPIREQUEST,{method: "getNumRepeat", url: url})!
        var json = _result()
        
        _SMS_CONFIRM_DATA["id"] = json["tzid"]
        _BAS_SMSCONFIRMDATA[ _SMS_CONFIRM_DATA["number"] ] = _SMS_CONFIRM_DATA

        _SMS_MAX_WAIT = Date.now() + 60000 * (<%= max_wait %>)
        _do(function(){
            if(Date.now() > _SMS_MAX_WAIT)
                fail("Sms Reg Error: Timeout for getState");

            _call(_BAS_SMSREGAPIREQUEST,{method: "getState", number: _SMS_CONFIRM_DATA["number"], dontcheckresp: true})!
            var json = _result()

            if(json["response"] === "TZ_NUM_PREPARE")
            {
                _break();
            }

            if(json["response"] !== "TZ_INPOOL")
            {
                fail("Sms Reg Error: " + json["response"] + " for getNum");
            }

        })!

    })!

	_SMS_MAX_WAIT = Date.now() + 60000 * (<%= max_wait %>)
	_do(function(){
        if(Date.now() > _SMS_MAX_WAIT)
			fail("Sms Reg Error: Timeout during solve");

        _call(_BAS_SMSREGAPIREQUEST,{method: "getState", number: _SMS_CONFIRM_DATA["number"], dontcheckresp: true})!
        var json = _result()

        if(json["response"] === "TZ_NUM_ANSWER")
        {
            <%= variable %> = json["msg"]
            _SMS_CONFIRM_DATA["not_first"] = true
        	_BAS_SMSCONFIRMDATA[ _SMS_CONFIRM_DATA["number"] ] = _SMS_CONFIRM_DATA
            _break();
        }

        if(json["response"] !== "TZ_NUM_WAIT" && json["response"] !== "TZ_NUM_PREPARE")
        {
            fail("Sms Reg Error: " + json["response"] + " for getNum");
        }

           
    })!


})!


_if(_SMS_CONFIRM_DATA["method"] == "sms-activate.ru", function(){
    
    _if(_SMS_CONFIRM_DATA["not_first"], function(){
        _call(_BAS_SMSACTIVATEPIREQUEST,{api_key: _SMS_CONFIRM_DATA["api"], action: "setStatus", status: "3", id: _SMS_CONFIRM_DATA["id"]})!
        var arr = _result()
        if(arr[0].indexOf("ACCESS_") != 0)
        {
            fail("Error during sms-activate setStatus(3) " + arr.join(":"))
        }

    })!
    
    

    _SMS_MAX_WAIT = Date.now() + 60000 * (<%= max_wait %>)
    _do(function(){
        if(Date.now() > _SMS_MAX_WAIT)
            fail("Sms Activate Error: Timeout during solve");

        _call(_BAS_SMSACTIVATEPIREQUEST,{api_key: _SMS_CONFIRM_DATA["api"], action: "getStatus", id: _SMS_CONFIRM_DATA["id"]})!

        var arr = _result()

        if(arr[0] == "STATUS_OK")
        {
            <%= variable %> = arr[1]
            _SMS_CONFIRM_DATA["not_first"] = true
            _BAS_SMSCONFIRMDATA[ _SMS_CONFIRM_DATA["number"] ] = _SMS_CONFIRM_DATA
            _break();
        }


        if(arr[0] != "STATUS_WAIT_CODE" && arr[0] != "STATUS_WAIT_RETRY")
        {
            fail("Error during sms-activate getStatus " + arr.join(":"))
        }


    })!


})!

_if(_SMS_CONFIRM_DATA["method"] == "smspva.com", function(){
    _if(_SMS_CONFIRM_DATA["not_first"], function(){
        _call(_BAS_SMSPVAREQUEST,{apikey: _SMS_CONFIRM_DATA["api"], metod: "get_proverka", service: _SMS_CONFIRM_DATA["service"], number: _SMS_CONFIRM_DATA["number"]})!
        var json = _result()
        if(json["response"] != "ok")
        {
            fail("failed to get_proverka from smspva " + JSON.stringify(json))
        }
        if(parseInt(json["id"]) == 0)
            fail("Fail to get second sms with smspva")
        _SMS_CONFIRM_DATA["id"] = json["id"]
        _BAS_SMSCONFIRMDATA[ "7" + _SMS_CONFIRM_DATA["number"] ] = _SMS_CONFIRM_DATA
    })!

    _SMS_MAX_WAIT = Date.now() + 60000 * (<%= max_wait %>)
    _do(function(){
        if(Date.now() > _SMS_MAX_WAIT)
            fail("SmsPva Error: Timeout during solve");

        _call(_BAS_SMSPVAREQUEST,{apikey: _SMS_CONFIRM_DATA["api"], id: _SMS_CONFIRM_DATA["id"], metod: "get_sms", service: _SMS_CONFIRM_DATA["service"]})!
        var json = _result()
        if(json["response"] == "1")
        {
            <%= variable %> = json["sms"]
            _SMS_CONFIRM_DATA["not_first"] = true
            _BAS_SMSCONFIRMDATA[ "7" + _SMS_CONFIRM_DATA["number"] ] = _SMS_CONFIRM_DATA
            _break();
        }

        if(json["response"] != "2")
        {
            fail("Error during smspva get_sms " +JSON.stringify(json))
        }

    })!


})!


