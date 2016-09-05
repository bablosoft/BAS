var Variable = this.$el.find("#Variable").val().toUpperCase();
var VariableSecond = this.$el.find("#VariableSecond").val().toUpperCase();

if(Variable.length == 0)
{
  Invalid("Variable is empty");
  return;
}

if(VariableSecond.length == 0)
{
  Invalid("VariableSecond is empty");
  return;
}

try{
  var code = loader.GetAdditionalData() + _.template($("#list_merge_code").html())({variable:"VAR_" + Variable,variable_second:"VAR_" + VariableSecond})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}