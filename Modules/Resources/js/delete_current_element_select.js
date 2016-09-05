var ResourceName = $("#ResourceName").val();
var Sync = $("#Check").is(':checked')

if(ResourceName.length == 0)
{
  Invalid("Resource name is empty");
  return;
}

try{
  var code = loader.GetAdditionalData() + _.template($("#delete_current_element_code").html())({key: "\"" + je(ResourceName) + "\"",sync:Sync})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}