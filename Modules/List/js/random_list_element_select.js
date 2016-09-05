var Variable = this.$el.find("#Variable").val().toUpperCase();
var VariableResult = this.$el.find("#VariableResult").val().toUpperCase();
var RemoveAfterUse = $("#Check").is(':checked')


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
  var code = loader.GetAdditionalData() + _.template($("#random_list_element_code").html())({variable:"VAR_" + Variable,variable_result:"VAR_" + VariableResult,remove:RemoveAfterUse})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}