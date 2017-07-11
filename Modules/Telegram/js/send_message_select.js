var Token = GetInputConstructorValue("Token", loader);
var IdChat = GetInputConstructorValue("IdChat", loader);
var Message = GetInputConstructorValue("Message", loader);
var IsNumberThread = $("#Check").is(':checked');
var IsTime = $("#Check1").is(':checked');

if(Token["original"].length == 0)
{
  Invalid("Token is empty");
  return;
}

if(IdChat["original"].length == 0)
{
  Invalid("IdChat is empty");
  return;
}

if(Message["original"].length == 0)
{
  Invalid("Message is empty");
  return;
}

try{
  var code = loader.GetAdditionalData() + _.template($("#send_message_code").html())({token:Token["updated"], chat_id:IdChat["updated"], message:Message["updated"], is_num_thread:IsNumberThread, is_time:IsTime});
  code = Normalize(code,0);
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}