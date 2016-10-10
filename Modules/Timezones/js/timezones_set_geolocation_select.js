var Latitude = GetInputConstructorValue("Latitude", loader);
var Longitude = GetInputConstructorValue("Longitude", loader);

if(Latitude["original"].length == 0)
{
  Invalid("Latitude is empty");
  return;
}

if(Longitude["original"].length == 0)
{
  Invalid("Longitude is empty");
  return;
}
 try{
  var code = loader.GetAdditionalData() + _.template($("#timezones_set_geolocation_code").html())({latitude: Latitude["updated"],longitude: Longitude["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}