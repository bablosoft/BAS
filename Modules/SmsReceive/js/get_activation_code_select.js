var NumberVar = GetInputConstructorValue("Number", loader);
var MaxWait = GetInputConstructorValue("MaxWait", loader);
var Save = this.$el.find("#Save").val().toUpperCase();


if(NumberVar["original"].length == 0)
{
  Invalid("Number is empty");
  return;
}

if(MaxWait["original"].length == 0)
{
  Invalid("MaxWait is empty");
  return;
}

try{
  var code = loader.GetAdditionalData() + _.template($("#get_activation_code_code").html())({number: NumberVar["updated"], variable:"VAR_" + Save, max_wait: MaxWait["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}