var Variable = this.$el.find("#Variable").val().toUpperCase();
var VariableLength = this.$el.find("#VariableLength").val().toUpperCase();


if(VariableLength.length == 0)
{
  Invalid("VariableLength is empty");
  return;
}

if(Variable.length == 0)
{
  Invalid("Variable is empty");
  return;
}

try{
  var code = loader.GetAdditionalData() +  _.template($("#list_length_code").html())({variable:"VAR_" + Variable,variable_length:"VAR_" + VariableLength})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}