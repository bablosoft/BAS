var Save = this.$el.find("#Save").val().toUpperCase();
var LocationValue = GetInputConstructorValue("Location", loader);
var Arguments = GetInputConstructorValue("Arguments", loader);
var waitfinish = $("#Check").is(':checked')


if(Save.length == 0)
{
  Invalid("Variable is empty");
  return;
}
if(LocationValue["original"].length == 0)
{
  Invalid("Location is empty");
  return;
}
 try{
  var code = loader.GetAdditionalData() + _.template($('#execute_process_code').html())({variable:"VAR_" + Save,location: LocationValue["updated"], waitfinish:waitfinish, arguments: Arguments["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}