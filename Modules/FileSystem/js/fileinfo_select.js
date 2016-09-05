var SaveExists = this.$el.find("#SaveExists").val().toUpperCase();
var SaveSize = this.$el.find("#SaveSize").val().toUpperCase();
var SaveDirectory = this.$el.find("#SaveDirectory").val().toUpperCase();
var SaveIsDirectory = this.$el.find("#SaveIsDirectory").val().toUpperCase();
var SaveLastModified = this.$el.find("#SaveLastModified").val().toUpperCase();

var Value = GetInputConstructorValue("Value", loader);


if(SaveExists.length == 0 || SaveSize.length == 0 || SaveDirectory.length == 0 || SaveIsDirectory.length == 0 || SaveLastModified.length == 0)
{
  Invalid("Variable is empty");
  return;
}

if(Value["original"].length == 0)
{
  Invalid("File path is empty");
  return;
}

 try{
  var code = loader.GetAdditionalData() + _.template($("#fileinfo_code").html())({variable_exists:"VAR_" + SaveExists,variable_size:"VAR_" + SaveSize,variable_directory:"VAR_" + SaveDirectory,variable_is_directory:"VAR_" + SaveIsDirectory,variable_last_modified:"VAR_" + SaveLastModified,value: Value["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}