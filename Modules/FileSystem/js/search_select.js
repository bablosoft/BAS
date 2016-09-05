var Folder = GetInputConstructorValue("Folder",loader)
var Mask = GetInputConstructorValue("Mask",loader)
var FileContains = GetInputConstructorValue("FileContains",loader)
var IncludeFiles = $("#Check2").is(':checked')
var IncludeFolders = $("#Check").is(':checked')
var RecursiveSearch = $("#Check3").is(':checked')
var Save = this.$el.find("#Save").val().toUpperCase();



if(Folder["original"].length <= 0)
{
  Invalid("Folder is empty");
  return;
}

if(Mask["original"].length <= 0)
{
  Invalid("Mask is empty");
  return;
}

if(Save.length == 0)
{
  Invalid("Variable is empty");
  return;
}


 try{
  var code = loader.GetAdditionalData() + _.template($('#search_code').html())(
	  	{
	  		variable:"VAR_" + Save,
	  		folder:Folder["updated"],
	  		mask:Mask["updated"],
	  		contains:FileContains["updated"],
	  		include_folders:IncludeFolders,
	  		include_files:IncludeFiles,
	  		recursive:RecursiveSearch
	  	}
  	)
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{
}