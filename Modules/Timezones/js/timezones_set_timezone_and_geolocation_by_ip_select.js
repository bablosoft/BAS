var Value = GetInputConstructorValue("Value", loader);

if(Value["original"].length == 0)
{
  Invalid("Ip is empty");
  return;
}
 try{
  var code = loader.GetAdditionalData() + _.template($("#timezones_set_timezone_and_geolocation_by_ip_code").html())({value: Value["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}