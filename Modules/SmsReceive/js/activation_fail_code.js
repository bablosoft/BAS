_SMS_CONFIRM_DATA = _BAS_SMSCONFIRMDATA[<%= number %>]
if(!_SMS_CONFIRM_DATA)
    fail("No information about this number")


_if(_SMS_CONFIRM_DATA["method"] == "sms-reg.com", function(){
	_call(_BAS_SMSREGAPIREQUEST,{method: "setOperationOver", number: _SMS_CONFIRM_DATA["number"]})!
	var json = _result()
	_SMS_CONFIRM_DATA["id"] = json["tzid"]
	_SMS_CONFIRM_DATA["originalid"] = json["tzid"]
    _BAS_SMSCONFIRMDATA[ _SMS_CONFIRM_DATA["number"] ] = _SMS_CONFIRM_DATA
})!