var Save = this.$el.find("#Save").val().toUpperCase();
var Command = GetInputConstructorValue("Command", loader);
var waitfinish = $("#Check").is(':checked')


if(Save.length == 0)
{
  Invalid("Variable is empty");
  return;
}
if(Command["original"].length == 0)
{
  Invalid("Command is empty");
  return;
}
 try{
  var code = loader.GetAdditionalData() + _.template($('#execute_process_code').html())({variable:"VAR_" + Save,command: Command["updated"], waitfinish:waitfinish})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}