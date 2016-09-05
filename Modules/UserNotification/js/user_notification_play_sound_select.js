 try{
  var code = loader.GetAdditionalData() + _.template($('#user_notification_play_sound_code').html())({})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{
}