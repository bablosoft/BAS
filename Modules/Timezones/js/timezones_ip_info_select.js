var SaveValid = this.$el.find("#SaveValid").val().toUpperCase();
var SaveCountry = this.$el.find("#SaveCountry").val().toUpperCase();
var SaveCity = this.$el.find("#SaveCity").val().toUpperCase();
var SaveLatitude = this.$el.find("#SaveLatitude").val().toUpperCase();
var SaveLongitude = this.$el.find("#SaveLongitude").val().toUpperCase();
var SaveTimezone = this.$el.find("#SaveTimezone").val().toUpperCase();
var SaveOffset = this.$el.find("#SaveOffset").val().toUpperCase();
var SaveDstOffset = this.$el.find("#SaveDstOffset").val().toUpperCase();

var Value = GetInputConstructorValue("Value", loader);


if(SaveValid.length == 0 || SaveCountry.length == 0 || SaveCity.length == 0 || SaveLatitude.length == 0 || SaveLongitude.length == 0 || SaveTimezone.length == 0 || SaveOffset.length == 0 || SaveDstOffset.length == 0)
{
  Invalid("Variable is empty");
  return;
}

if(Value["original"].length == 0)
{
  Invalid("Ip is empty");
  return;
}

 try{
  var code = loader.GetAdditionalData() + _.template($("#timezones_ip_info_code").html())({
  	variable_valid:"VAR_" + SaveValid,
  	variable_country:"VAR_" + SaveCountry,
  	variable_city:"VAR_" + SaveCity,
  	variable_latitude:"VAR_" + SaveLatitude,
  	variable_longitude:"VAR_" + SaveLongitude,
  	variable_timezone:"VAR_" + SaveTimezone,
  	variable_offset:"VAR_" + SaveOffset,
    variable_dst_offset:"VAR_" + SaveDstOffset,
  	value: Value["updated"]
  })
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}