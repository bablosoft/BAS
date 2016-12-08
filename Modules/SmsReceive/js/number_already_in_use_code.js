_SMS_CONFIRM_DATA = _BAS_SMSCONFIRMDATA[<%= number %>]
if(!_SMS_CONFIRM_DATA)
    fail("No information about this number")


_if(_SMS_CONFIRM_DATA["method"] == "sms-reg.com", function(){
	_call(_BAS_SMSREGAPIREQUEST,{method: "setOperationUsed", number: _SMS_CONFIRM_DATA["number"]})!
	var json = _result()
	_SMS_CONFIRM_DATA["id"] = json["tzid"]
	_SMS_CONFIRM_DATA["originalid"] = json["tzid"]
    _BAS_SMSCONFIRMDATA[ _SMS_CONFIRM_DATA["number"] ] = _SMS_CONFIRM_DATA
})!

_if(_SMS_CONFIRM_DATA["method"] == "sms-activate.ru", function(){

	_call(_BAS_SMSACTIVATEPIREQUEST,{api_key: _SMS_CONFIRM_DATA["api"], action: "setStatus", status: "8", id: _SMS_CONFIRM_DATA["id"]})!
	var arr = _result()
    if(arr[0].indexOf("ACCESS_") != 0)
    {
        fail("Error during sms-activate setStatus(8) " + arr.join(":"))
    }
})!

_if(_SMS_CONFIRM_DATA["method"] == "smspva.com", function(){

	_call(_BAS_SMSPVAREQUEST,{apikey: _SMS_CONFIRM_DATA["api"], id: _SMS_CONFIRM_DATA["id"], metod: "ban", service: _SMS_CONFIRM_DATA["service"]})!
    var json = _result()
    if(json["response"] != "1")
    {
        fail("failed to ban from smspva " + JSON.stringify(json))
    }

})!


