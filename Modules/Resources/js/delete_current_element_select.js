var ResourceName = $("#ResourceName").val();
var Sync = $("#Check").is(':checked')

if(ResourceName.length == 0)
{
  Invalid("Resource name is empty");
  return;
}

try{
  var code = _.template($("#delete_current_element_code").html())({key: "\"" + je(ResourceName) + "\"",sync:Sync})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("Delete resource " + ResourceName, BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}