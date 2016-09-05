var Value = GetInputConstructorValue("Value", loader);

if(Value["original"].length == 0)
{
  Invalid("Dir path is empty");
  return;
}
 try{
  var code = loader.GetAdditionalData() + _.template($("#createdir_code").html())({value: Value["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}