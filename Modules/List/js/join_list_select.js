var Variable = this.$el.find("#Variable").val().toUpperCase();
var Separator = GetInputConstructorValue("Separator", loader);
var VariableResult = this.$el.find("#VariableResult").val().toUpperCase();



if(Variable.length == 0)
{
  Invalid("Variable is empty");
  return;
}

if(VariableResult.length == 0)
{
  Invalid("VariableResult is empty");
  return;
}

try{
  var code = loader.GetAdditionalData() + _.template($("#join_list_code").html())({variable:"VAR_" + Variable,variable_result:"VAR_" + VariableResult,separator: Separator["updated"],})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}