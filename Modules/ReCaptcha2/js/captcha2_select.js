var Method = GetInputConstructorValue("Method", loader);
var Rucaptcha = GetInputConstructorValue("Rucaptcha", loader);
var Dbc = GetInputConstructorValue("Dbc", loader);
var TimesToSolve = GetInputConstructorValue("TimesToSolve", loader);

if(Method["original"].length == 0)
{
  Invalid("Method is empty");
  return;
}
if(TimesToSolve["original"].length == 0)
{
  Invalid("If captcha appear is empty");
  return;
}

try{
  var path = GetPath(loader)
  var code = loader.GetAdditionalData() + _.template($("#ReCaptcha2_code").html())({path: path["path"],waiter: path["waiter"],method: Method["updated"], rucaptcha: Rucaptcha["updated"], dbc: Dbc["updated"], timestosolve:TimesToSolve["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("Solve captcha2", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}