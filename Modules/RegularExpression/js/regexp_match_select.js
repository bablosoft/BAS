var Value = GetInputConstructorValue("Value",loader)
var Regexp = GetInputConstructorValue("Regexp",loader)
var Result = this.$el.find("#Result").val().toUpperCase();


if(Value["original"] == 0)
{
  Invalid("String is empty");
  return;
}

if(Regexp["original"] == 0)
{
  Invalid("Regexp is empty");
  return;
}

if(Result.length == 0)
{
  Invalid("Result is empty");
  return;
}


try{
  var code = loader.GetAdditionalData() + _.template($("#regexp_match_code").html())({variable:"VAR_" + Result,string:Value["updated"],regexp:Regexp["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}