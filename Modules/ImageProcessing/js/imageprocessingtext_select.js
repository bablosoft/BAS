var Id = GetInputConstructorValue("Id", loader);
var X = GetInputConstructorValue("X", loader);
var Y = GetInputConstructorValue("Y", loader);
var Width = GetInputConstructorValue("Width", loader);
var Height = GetInputConstructorValue("Height", loader);
var FontFamily = GetInputConstructorValue("FontFamily", loader);
var FontSize = GetInputConstructorValue("FontSize", loader);
var TextString = GetInputConstructorValue("Text", loader);
var ColorR = GetInputConstructorValue("ColorR", loader);
var ColorG = GetInputConstructorValue("ColorG", loader);
var ColorB = GetInputConstructorValue("ColorB", loader);
var ColorA= GetInputConstructorValue("ColorA", loader);


if(FontFamily["original"].length == 0)
{
  Invalid("FontFamily is empty");
  return;
}
if(FontSize["original"].length == 0)
{
  Invalid("FontSize is empty");
  return;
}
if(TextString["original"].length == 0)
{
  Invalid("Text is empty");
  return;
}
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
if(Width["original"].length == 0)
{
  Invalid("Width is empty");
  return;
}
if(Height["original"].length == 0)
{
  Invalid("Height is empty");
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
  var code = loader.GetAdditionalData() + _.template($("#imageprocessingtext_code").html())(
    {
      x: X["updated"],
      y: Y["updated"],
      width: Width["updated"],
      height: Height["updated"],
      fontfamily: FontFamily["updated"],
      fontsize: FontSize["updated"],
      text: TextString["updated"],
      r: ColorR["updated"],
      g: ColorG["updated"],
      b: ColorB["updated"],
      a: ColorA["updated"],
      id: Id["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{

}