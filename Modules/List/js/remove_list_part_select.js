var Variable = this.$el.find("#Variable").val().toUpperCase();
var IndexStart = GetInputConstructorValue("IndexStart", loader);
var IndexEnd = GetInputConstructorValue("IndexEnd", loader);


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

try{
  var code = loader.GetAdditionalData() + _.template($("#remove_list_part_code").html())({variable:"VAR_" + Variable,index_start: IndexStart["updated"],index_end: IndexEnd["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}