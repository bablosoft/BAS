var File = GetInputConstructorValue("File",loader)
var Value = GetInputConstructorValue("Value",loader)
var append = $("#Check").is(':checked')
var base64 = $("#Check2").is(':checked')
var eol = $("#Check3").is(':checked')


if(File["original"].length <= 0)
{
  Invalid("File is empty");
  return;
}

if(Value["original"].length <= 0)
{
  Invalid("Data is empty");
  return;
}

 try{
  var code = loader.GetAdditionalData() + _.template($('#writefile_code').html())({path:File["updated"],value:Value["updated"],append:append,base64:base64,eol:eol})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{
}