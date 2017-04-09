var Tags = GetInputConstructorValue("Tags", loader);
var Key = GetInputConstructorValue("Key", loader);
var Save = this.$el.find("#Save").val().toUpperCase();


if(Tags["original"].length == 0)
{
  Invalid("Tags are empty");
  return;
}

try{
  var code = loader.GetAdditionalData() + _.template($("#get_fingerprint_code").html())({tags: Tags["updated"], variable:"VAR_" + Save, key: Key["updated"]})

  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}