var Width = GetInputConstructorValue("Width", loader);
var Height = GetInputConstructorValue("Height", loader);
var ColorR = GetInputConstructorValue("ColorR", loader);
var ColorG = GetInputConstructorValue("ColorG", loader);
var ColorB = GetInputConstructorValue("ColorB", loader);
var ColorA= GetInputConstructorValue("ColorA", loader);
var Save = this.$el.find("#Save").val().toUpperCase();


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

if(Save.length == 0)
{
  Invalid("Save is empty");
  return;
}



 try{
  var code = loader.GetAdditionalData() + _.template($("#imageprocessingcreate_code").html())({width: Width["updated"],height: Height["updated"],r: ColorR["updated"],g: ColorG["updated"],b: ColorB["updated"],a: ColorA["updated"],variable: "VAR_" + Save})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}