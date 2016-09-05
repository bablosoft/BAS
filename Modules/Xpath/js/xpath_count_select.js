var Save = this.$el.find("#Save").val().toUpperCase();
var Value = GetInputConstructorValue("Value", loader);
var TextValue = GetInputConstructorValue("Text", loader);


if(TextValue["original"].length == 0)
{
  Invalid("Text is empty");
  return;
}

if(Save.length == 0)
{
  Invalid("Variable is empty");
  return;
}
if(Value["original"].length == 0)
{
  Invalid("Query is empty");
  return;
}
 try{
  var code = loader.GetAdditionalData() + _.template($('#xpath_count_code').html())({variable:"VAR_" + Save,value: Value["updated"], text: TextValue["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}
