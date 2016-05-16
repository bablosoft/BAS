function sms_reg(apikey)
{
    SMS_REG_API_KEY = apikey;
}

function sms_reg_set_transaction(tz)
{
    SMS_REG_TZ = tz;
}

function sms_reg_get_number(country, service, callback)
{
    SMS_REG_CALLBACK = callback
    _ensure_http_client();
    http_client_get("http://api.sms-reg.com/getNum.php?country=" + country + "&service=" + service + "&apikey=" + SMS_REG_API_KEY, function(){
        json = parse_json(http_client_content())
        if(json["response"].toString() !== "1")
            fail("Sms Reg Error: during getNum " + json["error_msg"])
        SMS_REG_TZ = json["tzid"]

        _do(function(){
            if(_iterator()>350)
                fail("Sms Reg Error: Timeout for getNum");

            http_client_get("http://api.sms-reg.com/getState.php?tzid=" + SMS_REG_TZ + "&apikey=" + SMS_REG_API_KEY, function(){
                json = parse_json(http_client_content())
                if(json["response"] === "TZ_NUM_PREPARE")
                {
                    _set_result(json["number"]);
                    _break();
                }
                if(json["response"] !== "TZ_INPOOL")
                {
                    fail("Sms Reg Error: " + json["response"] + " for getNum");
                }

                sleep(4000, function(){})
            })


        }, SMS_REG_CALLBACK )


    });

}


function sms_reg_solve(callback)
{
    SMS_REG_CALLBACK = callback
    _ensure_http_client();
    http_client_get("http://api.sms-reg.com/setReady.php?tzid=" + SMS_REG_TZ + "&apikey=" + SMS_REG_API_KEY, function(){
        json = parse_json(http_client_content())
        if(json["response"].toString() !== "1")
            fail("Sms Reg Error: during setReady " + json["error_msg"])

        _do(function(){
            if(_iterator()>350)
                fail("Sms Reg Error: Timeout for solve");

            http_client_get("http://api.sms-reg.com/getState.php?tzid=" + SMS_REG_TZ + "&apikey=" + SMS_REG_API_KEY, function(){
                json = parse_json(http_client_content())
                if(json["response"] === "TZ_NUM_ANSWER")
                {
                    _set_result(json["msg"]);
                    _break();
                }
                if(json["response"] !== "TZ_NUM_WAIT")
                {
                    fail("Sms Reg Error: " + json["response"] + " for solve");
                }

                sleep(4000, function(){})
            })


        }, SMS_REG_CALLBACK )


    });

}



function sms_reg_revise(callback)
{
    SMS_REG_CALLBACK = callback
    _ensure_http_client();
    http_client_get("http://api.sms-reg.com/setOperationRevise.php?tzid=" + SMS_REG_TZ + "&apikey=" + SMS_REG_API_KEY, function(){
        json = parse_json(http_client_content())
        if(json["response"].toString() !== "1")
            fail("Sms Reg Error: during setOperationRevise " + json["error_msg"])
        SMS_REG_TZ = json["tzid"]

        _do(function(){
            if(_iterator()>350)
                fail("Sms Reg Error: Timeout for revise");

            http_client_get("http://api.sms-reg.com/getState.php?tzid=" + SMS_REG_TZ + "&apikey=" + SMS_REG_API_KEY, function(){
                json = parse_json(http_client_content())
                if(json["response"] === "TZ_NUM_ANSWER2")
                {
                    _set_result(json["msg"]);
                    _break();
                }
                if(json["response"] !== "TZ_NUM_WAIT2")
                {
                    fail("Sms Reg Error: " + json["response"] + " for revise");
                }

                sleep(4000, function(){})
            })


        }, SMS_REG_CALLBACK )


    });

}

function sms_reg_success(callback)
{
    SMS_REG_CALLBACK = callback;
    http_client_get("http://api.sms-reg.com/setOperationOk.php?tzid=" + SMS_REG_TZ + "&apikey=" + SMS_REG_API_KEY, function(){
        json = parse_json(http_client_content())
        if(json["response"].toString() !== "1")
            fail("Sms Reg Error: during setOperationOk " + json["error_msg"])


        SMS_REG_CALLBACK();
    });

}

function sms_reg_failed(callback)
{
    SMS_REG_CALLBACK = callback;
    http_client_get("http://api.sms-reg.com/setOperationOver.php?tzid=" + SMS_REG_TZ + "&apikey=" + SMS_REG_API_KEY, function(){
        json = parse_json(http_client_content())
        if(json["response"].toString() !== "1")
            fail("Sms Reg Error: during setOperationOver " + json["error_msg"])


        SMS_REG_CALLBACK();
    });

}

function sms_reg_used(callback)
{
    SMS_REG_CALLBACK = callback;
    http_client_get("http://api.sms-reg.com/setOperationUsed.php?tzid=" + SMS_REG_TZ + "&apikey=" + SMS_REG_API_KEY, function(){
        json = parse_json(http_client_content())
        if(json["response"].toString() !== "1")
            fail("Sms Reg Error: during setOperationUsed " + json["error_msg"])


        SMS_REG_CALLBACK();
    });

}

