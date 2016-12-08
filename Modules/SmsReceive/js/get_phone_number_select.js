var Service = GetInputConstructorValue("Service", loader);
var Apikey = GetInputConstructorValue("Apikey", loader);
var Site = $("#Select").val()
var Save = this.$el.find("#Save").val().toUpperCase();


if(Service["original"].length == 0)
{
  Invalid("Service is empty");
  return;
}
if(Apikey["original"].length == 0)
{
  Invalid("Apikey is empty");
  return;
}

try{
  var code = loader.GetAdditionalData() + _.template($("#get_phone_number_code").html())({service: Service["updated"], apikey: Apikey["updated"], site: "\"" + Site + "\"", variable:"VAR_" + Save})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}