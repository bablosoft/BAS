var Variable = this.$el.find("#Variable").val().toUpperCase();
var VariableSave = this.$el.find("#VariableSave").val().toUpperCase();
var Value = GetInputConstructorValue("Value", loader);



if(VariableSave.length == 0)
{
  Invalid("VariableSave is empty");
  return;
}

if(Variable.length == 0)
{
  Invalid("Variable is empty");
  return;
}

try{
  var code = loader.GetAdditionalData() + _.template($("#list_contains_code").html())({variable:"VAR_" + Variable,variable_save:"VAR_" + VariableSave,value:Value["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}