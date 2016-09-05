var Name = GetInputConstructorValue("Name",loader)
var SuccessNumber = GetInputConstructorValue("SuccessNumber",loader)
var FailNumber = GetInputConstructorValue("FailNumber",loader)
var SimultaneousUsage = GetInputConstructorValue("SimultaneousUsage",loader)
var Interval = GetInputConstructorValue("Interval",loader)
var Greedy = $("#Check").is(':checked')
var DontGiveUp = $("#Check2").is(':checked')


if(Name["original"].length == 0)
{
  Invalid("Resource is empty");
  return;
}

if(SuccessNumber["original"].length == 0)
{
  Invalid("SuccessNumber is empty");
  return;
}

if(FailNumber["original"].length == 0)
{
  Invalid("FailNumber is empty");
  return;
}

if(SimultaneousUsage["original"].length == 0)
{
  Invalid("SimultaneousUsage is empty");
  return;
}

if(Interval["original"].length == 0)
{
  Invalid("Interval is empty");
  return;
}


try{
  var code = loader.GetAdditionalData() + _.template($("#create_resource_code").html())({name: Name["updated"],success: SuccessNumber["updated"],fail: FailNumber["updated"],simultaneous: SimultaneousUsage["updated"],interval: Interval["updated"],greedy: Greedy,dontgiveup: DontGiveUp})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}