var Id = GetInputConstructorValue("Id", loader);
var Width = this.$el.find("#Width").val().toUpperCase();
var Height = this.$el.find("#Height").val().toUpperCase();


if(Id["original"].length == 0)
{
  Invalid("Id is empty");
  return;
}

if(Width.length == 0)
{
  Invalid("Width is empty");
  return;
}

if(Height.length == 0)
{
  Invalid("Height is empty");
  return;
}


 try{
  var code = loader.GetAdditionalData() + _.template($("#imageprocessinggetsize_code").html())({id: Id["updated"],variable_width: "VAR_" + Width,variable_height: "VAR_" + Height})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}