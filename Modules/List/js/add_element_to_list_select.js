var Variable = this.$el.find("#Variable").val().toUpperCase();
var Value = GetInputConstructorValue("Value", loader);

if(Variable.length == 0)
{
  Invalid("Variable is empty");
  return;
}

try{
  var code = loader.GetAdditionalData() + _.template($("#add_element_to_list_code").html())({variable:"VAR_" + Variable,value: Value["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}