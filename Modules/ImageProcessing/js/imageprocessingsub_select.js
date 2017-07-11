var Id = GetInputConstructorValue("Id", loader);
var X = GetInputConstructorValue("X", loader);
var Y = GetInputConstructorValue("Y", loader);
var Width = GetInputConstructorValue("Width", loader);
var Height = GetInputConstructorValue("Height", loader);
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

if(Save.length == 0)
{
  Invalid("Save is empty");
  return;
}



 try{
  var code = loader.GetAdditionalData() + _.template($("#imageprocessingsub_code").html())({id: Id["updated"],x: X["updated"],y: Y["updated"],width: Width["updated"],height: Height["updated"],variable: "VAR_" + Save})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}