var File = GetInputConstructorValue("File",loader)
var Save = this.$el.find("#Save").val().toUpperCase();
var append = $("#Check").is(':checked')
var eol = $("#Check2").is(':checked')



if(File["original"].length <= 0)
{
  Invalid("File is empty");
  return;
}

if(Save.length <= 0)
{
  Invalid("List is empty");
  return;
}

 try{
  var code = loader.GetAdditionalData() + _.template($('#list_to_file_code').html())({path:File["updated"],save:"VAR_" + Save,append:append,eol:eol})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{
}