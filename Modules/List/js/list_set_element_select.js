var Variable = this.$el.find("#Variable").val().toUpperCase();
var Index = GetInputConstructorValue("Index", loader);
var Value = GetInputConstructorValue("Value", loader);


if(Index["original"].length == 0)
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
  var code = loader.GetAdditionalData() + _.template($("#list_set_element_code").html())({variable:"VAR_" + Variable,index:Index["updated"],value: Value["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{
  alert(e)
}