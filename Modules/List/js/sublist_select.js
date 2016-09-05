var Variable = this.$el.find("#Variable").val().toUpperCase();
var IndexStart = GetInputConstructorValue("IndexStart", loader);
var IndexEnd = GetInputConstructorValue("IndexEnd", loader);
var VariableNewList = this.$el.find("#VariableNewList").val().toUpperCase();


if(IndexEnd["original"].length == 0)
{
  Invalid("IndexEnd is empty");
  return;
}

if(IndexStart["original"].length == 0)
{
  Invalid("IndexStart is empty");
  return;
}

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
  var code = loader.GetAdditionalData() + _.template($("#sublist_code").html())({variable:"VAR_" + Variable,variable_new:"VAR_" + VariableNewList,index_start: IndexStart["updated"],index_end: IndexEnd["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}