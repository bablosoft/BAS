var Variable = this.$el.find("#Variable").val().toUpperCase();
var Value1 = GetInputConstructorValue("Value1", loader);
var Value2 = GetInputConstructorValue("Value2", loader);
var Value3 = GetInputConstructorValue("Value3", loader);


if(Variable.length == 0)
{
  Invalid("Variable is empty");
  return;
}

try{
  var code = loader.GetAdditionalData() + _.template($("#create_list_code").html())({variable:"VAR_" + Variable,value1: Value1["updated"],value2: Value2["updated"],value3: Value3["updated"], value1empty: Value1["original"].length == 0, value2empty: Value2["original"].length == 0, value3empty: Value3["original"].length == 0})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}