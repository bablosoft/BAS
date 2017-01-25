var Save = this.$el.find("#Save").val().toUpperCase();
if(Save.length == 0)
{
	Invalid("Variable is empty");
	return;
}
try{
	var code = loader.GetAdditionalData() + _.template($("#script_stats_project_path_code").html())({variable:"VAR_" + Save})
	code = Normalize(code,0)
	BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}