var Variable = this.$el.find("#Variable").val().toUpperCase();
var VariableSecond = this.$el.find("#VariableSecond").val().toUpperCase();
var Result = this.$el.find("#VariableResult").val().toUpperCase();


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

if(Result.length == 0)
{
  Invalid("Result is empty");
  return;
}

try{
  var code = loader.GetAdditionalData() + _.template($("#list_compare_code").html())({variable:"VAR_" + Variable,variable_second:"VAR_" + VariableSecond, result: "VAR_" + Result})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}