var IddleTime = GetInputConstructorValue("IddleTime", loader);
var Distribution = GetInputConstructorValue("Distribution", loader);

if(IddleTime["original"].length == 0)
{
  Invalid("Iddle time is empty");
  return;
}

try{
  var code = loader.GetAdditionalData() + _.template($("#idle_emulation_code").html())({iddle:IddleTime["updated"],distribution:Distribution["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}