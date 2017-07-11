var Data = GetInputConstructorValue("Data", loader);
var Save = this.$el.find("#Save").val().toUpperCase();


if(Data["original"].length == 0)
{
  Invalid("File path is empty");
  return;
}


 try{
  var code = loader.GetAdditionalData() + _.template($("#imageprocessingload_code").html())({data: Data["updated"],variable: "VAR_" + Save})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}