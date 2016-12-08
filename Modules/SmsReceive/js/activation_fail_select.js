var NumberVar = GetInputConstructorValue("Number", loader);

if(NumberVar["original"].length == 0)
{
  Invalid("Number is empty");
  return;
}

try{
  var code = loader.GetAdditionalData() + _.template($("#activation_fail_code").html())({number: NumberVar["updated"]})

  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}