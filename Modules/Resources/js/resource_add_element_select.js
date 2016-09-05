var ResourceName = $("#ResourceName").val();
var Sync = $("#Check").is(':checked')
var OnlyWrite = $("#Check2").is(':checked')
var Data = GetInputConstructorValue("Data",loader)


if(ResourceName.length == 0)
{
  Invalid("Resource name is empty");
  return;
}

if(Data["original"].length <= 0)
{
  Invalid("Data is empty");
  return;
}

try{
  var code = loader.GetAdditionalData() + _.template($("#resource_add_element_code").html())({key: "\"" + je(ResourceName) + "\"",sync:Sync,data:Data["updated"],onlywrite:OnlyWrite})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}