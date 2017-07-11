var Id1 = GetInputConstructorValue("Id1", loader);
var Id2 = GetInputConstructorValue("Id2", loader);
var X = GetInputConstructorValue("X", loader);
var Y = GetInputConstructorValue("Y", loader);


if(Id1["original"].length == 0)
{
  Invalid("Id1 is empty");
  return;
}

if(Id2["original"].length == 0)
{
  Invalid("Id2 is empty");
  return;
}

if(X["original"].length == 0)
{
  Invalid("X is empty");
  return;
}

if(Y["original"].length == 0)
{
  Invalid("Y is empty");
  return;
}


 try{
  var code = loader.GetAdditionalData() + _.template($("#imageprocessinginsert_code").html())({id1: Id1["updated"],id2: Id2["updated"],x: X["updated"],y: Y["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}