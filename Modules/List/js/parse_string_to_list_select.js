var StringValue = GetInputConstructorValue("String", loader);
var Separator = GetInputConstructorValue("Separator", loader);
var VariableResult = this.$el.find("#VariableResult").val().toUpperCase();



if(StringValue["original"] == 0)
{
  Invalid("String is empty");
  return;
}

if(VariableResult.length == 0)
{
  Invalid("VariableResult is empty");
  return;
}

try{
  var code = loader.GetAdditionalData() + _.template($("#parse_string_to_list_code").html())({stirng:StringValue["updated"],variable_result:"VAR_" + VariableResult,separator: Separator["updated"],})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}