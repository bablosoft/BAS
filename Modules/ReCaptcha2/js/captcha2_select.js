var Method = GetInputConstructorValue("Method", loader);
var Rucaptcha = GetInputConstructorValue("Rucaptcha", loader);
var TimesToSolve = GetInputConstructorValue("TimesToSolve", loader);
var Server = GetInputConstructorValue("Server", loader);

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
  var code = loader.GetAdditionalData() + _.template($("#ReCaptcha2_code").html())({path: path["path"],waiter: path["waiter"],method: Method["updated"], rucaptcha: Rucaptcha["updated"], timestosolve:TimesToSolve["updated"], serverurl: Server["updated"], query: path["query"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}