var Save = this.$el.find("#Save").val().toUpperCase();
var Value = GetInputConstructorValue("Value", loader);
var From = GetInputConstructorValue("From", loader);
var To = GetInputConstructorValue("To", loader);
var base64 = $("#Check").is(':checked')


if(Save.length == 0)
{
  Invalid("Variable is empty");
  return;
}
if(Value["original"].length == 0)
{
  Invalid("File path is empty");
  return;
}
 try{
  var code = loader.GetAdditionalData() + _.template($("#readfile_code").html())({variable:"VAR_" + Save,value: Value["updated"],base64:base64,from:From["updated"],to:To["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}