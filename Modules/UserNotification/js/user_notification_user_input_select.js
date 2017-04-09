var Variable = this.$el.find("#Variable").val().toUpperCase();
var Label = GetInputConstructorValue("Label", loader);


if(Variable.length == 0)
{
  Invalid("Variable is empty");
  return;
}

if(Label["original"].length == 0)
{
  Invalid("Label is empty");
  return;
}

try{
  var code = loader.GetAdditionalData() + _.template($("#user_notification_user_input_code").html())({variable:"VAR_" + Variable,label: Label["updated"]})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}