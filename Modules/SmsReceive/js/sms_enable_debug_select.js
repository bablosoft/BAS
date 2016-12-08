var EnableDebug = GetInputConstructorValue("EnableDebug", loader);

if(EnableDebug["original"].length == 0)
{
  Invalid("EnableDebug is empty");
  return;
}

try{
  var code = loader.GetAdditionalData() + _.template($("#sms_enable_debug_code").html())({enable: EnableDebug["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}