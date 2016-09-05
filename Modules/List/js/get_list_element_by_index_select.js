var Variable = this.$el.find("#Variable").val().toUpperCase();
var VariableResult = this.$el.find("#VariableResult").val().toUpperCase();
var Index = GetInputConstructorValue("Index", loader);
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

if(Index["original"].length == 0)
{
  Invalid("Index is empty");
  return;
}

try{
  var code = loader.GetAdditionalData() + _.template($("#get_list_element_by_index_code").html())({variable:"VAR_" + Variable,variable_result:"VAR_" + VariableResult,index: Index["updated"],remove:RemoveAfterUse})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}