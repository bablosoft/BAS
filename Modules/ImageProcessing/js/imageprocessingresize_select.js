var Id = GetInputConstructorValue("Id", loader);
var Width = GetInputConstructorValue("Width", loader);
var Height = GetInputConstructorValue("Height", loader);


if(Id["original"].length == 0)
{
  Invalid("Id is empty");
  return;
}

if(Width["original"].length == 0)
{
  Invalid("Width is empty");
  return;
}

if(Height["original"].length == 0)
{
  Invalid("Height is empty");
  return;
}


 try{
  var code = loader.GetAdditionalData() + _.template($("#imageprocessingresize_code").html())({id: Id["updated"],width: Width["updated"],height: Height["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}