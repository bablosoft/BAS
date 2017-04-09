var Fingerprint = GetInputConstructorValue("Fingerprint", loader);

if(Fingerprint["original"].length == 0)
{
  Invalid("Fingerprint is empty");
  return;
}

try{
  var code = loader.GetAdditionalData() + _.template($("#apply_fingerprint_code").html())({fingerprint: Fingerprint["updated"]})

  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}