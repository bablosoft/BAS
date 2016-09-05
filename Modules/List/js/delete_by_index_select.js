var Variable = this.$el.find("#Variable").val().toUpperCase();
var Value = GetInputConstructorValue("Value", loader);

if(Value["original"].length == 0)
{
  Invalid("Index is empty");
  return;
}

if(Variable.length == 0)
{
  Invalid("Variable is empty");
  return;
}

try{
  var code = loader.GetAdditionalData() + _.template($("#delete_by_index_code").html())({variable:"VAR_" + Variable,index: Value["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}