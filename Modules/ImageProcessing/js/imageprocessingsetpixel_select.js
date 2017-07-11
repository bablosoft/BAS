var Id = GetInputConstructorValue("Id", loader);
var X = GetInputConstructorValue("X", loader);
var Y = GetInputConstructorValue("Y", loader);
var ColorR = GetInputConstructorValue("ColorR", loader);
var ColorG = GetInputConstructorValue("ColorG", loader);
var ColorB = GetInputConstructorValue("ColorB", loader);
var ColorA= GetInputConstructorValue("ColorA", loader);


if(Id["original"].length == 0)
{
  Invalid("Id is empty");
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
if(ColorR["original"].length == 0)
{
  Invalid("ColorR is empty");
  return;
}
if(ColorG["original"].length == 0)
{
  Invalid("ColorG is empty");
  return;
}
if(ColorB["original"].length == 0)
{
  Invalid("ColorB is empty");
  return;
}
if(ColorA["original"].length == 0)
{
  Invalid("ColorA is empty");
  return;
}



 try{
  var code = loader.GetAdditionalData() + _.template($("#imageprocessingsetpixel_code").html())({x: X["updated"],y: Y["updated"],r: ColorR["updated"],g: ColorG["updated"],b: ColorB["updated"],a: ColorA["updated"],id: Id["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}