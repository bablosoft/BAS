var Value = GetInputConstructorValue("Value", loader);

if(Value["original"].length == 0)
{
  Invalid("File path is empty");
  return;
}
 try{
  var code = loader.GetAdditionalData() + _.template($("#removefile_code").html())({value: Value["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("Remove File/Dir " + Value["original"], BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}