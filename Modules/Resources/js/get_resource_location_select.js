var ResourceName = $("#ResourceName").val();
var Save = $("#Save").val().toUpperCase();

if(ResourceName.length == 0)
{
  Invalid("Resource name is empty");
  return;
}

if(Save.length <= 0)
{
  Invalid("Save variable is empty");
  return;
}

try{
  var code = loader.GetAdditionalData() + _.template($("#get_resource_location_code").html())({key: "\"" + je(ResourceName) + "\"",save: "VAR_" + Save})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}