var Id = GetInputConstructorValue("Id", loader);
var Save = this.$el.find("#Save").val().toUpperCase();


if(Id["original"].length == 0)
{
  Invalid("Id is empty");
  return;
}

if(Save.length == 0)
{
  Invalid("Save is empty");
  return;
}



 try{
  var code = loader.GetAdditionalData() + _.template($("#imageprocessinggetdata_code").html())({id: Id["updated"],variable: "VAR_" + Save})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}