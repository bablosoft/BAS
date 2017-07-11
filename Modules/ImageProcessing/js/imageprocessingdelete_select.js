var Id = GetInputConstructorValue("Id", loader);


if(Id["original"].length == 0)
{
  Invalid("Id is empty");
  return;
}



 try{
  var code = loader.GetAdditionalData() + _.template($("#imageprocessingdelete_code").html())({id: Id["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}