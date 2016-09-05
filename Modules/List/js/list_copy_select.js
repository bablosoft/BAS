var Variable = this.$el.find("#Variable").val().toUpperCase();
var VariableNewList = this.$el.find("#VariableNewList").val().toUpperCase();


if(Variable.length == 0)
{
  Invalid("Variable is empty");
  return;
}

if(VariableNewList.length == 0)
{
  Invalid("VariableNewList is empty");
  return;
}

try{
  var code = loader.GetAdditionalData() + _.template($("#list_copy_code").html())({variable:"VAR_" + Variable,variable_new:"VAR_" + VariableNewList})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}