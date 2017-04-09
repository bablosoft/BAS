var GroupId = this.$el.find("#GroupId").val().toUpperCase();
var Name = GetInputConstructorValue("Name", loader);
var Description = GetInputConstructorValue("Description", loader);
var Table = $("#Table").val();


if(GroupId.length == 0)
{
  Invalid("GroupId is empty");
  return;
}

if(Name["original"].length == 0)
{
  Invalid("Name is empty");
  return;
}

if(Description["original"].length == 0)
{
  Invalid("Description is empty");
  return;
}


try{
  var code = loader.GetAdditionalData() + _.template($("#database_create_group_code").html())({group:"VAR_" + GroupId,name: Name["updated"],description: Description["updated"],table: Table})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}