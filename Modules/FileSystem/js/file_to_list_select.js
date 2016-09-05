var Save = this.$el.find("#Save").val().toUpperCase();
var Value = GetInputConstructorValue("Value", loader);


if(Save.length == 0)
{
  Invalid("List is empty");
  return;
}
if(Value["original"].length == 0)
{
  Invalid("File path is empty");
  return;
}

 try{
  var code = loader.GetAdditionalData() + _.template($("#file_to_list_code").html())({variable:"VAR_" + Save,value: Value["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}