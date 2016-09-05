var Variable = this.$el.find("#Variable").val().toUpperCase();
var Value = GetInputConstructorValue("Value", loader);
var Index = GetInputConstructorValue("Index", loader);

if(Index.length == 0)
{
  Invalid("Index is empty");
  return;
}

if(Variable.length == 0)
{
  Invalid("Variable is empty");
  return;
}

try{
  var code = loader.GetAdditionalData() + _.template($("#insert_element_to_list_code").html())({variable:"VAR_" + Variable,value: Value["updated"], index: Index["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}