var RecordList = this.$el.find("#RecordList").val().toUpperCase();
var PageNumber = GetInputConstructorValue("PageNumber", loader);
var PageSize = GetInputConstructorValue("PageSize", loader);


var Table = $("#Table").val();

var filters = _Filter.GetFilters()
var Filters = " [ " 
filters.forEach(function(filter, item_index_all){
	Filters += " [ " 
	filter.forEach(function(item, item_index){
		if(item_index == 0)
			loader.SetIsString(false)
		if(item_index == 1)
			loader.SetIsString(true)
		if(item_index == 2)
			loader.SetIsString(false)
		
    	var add = loader.Resolve(item);
    	Filters += add
    	
		if(item_index != filter.length - 1)
			Filters += ","
	})
	
	Filters += " ] " 

	if(item_index_all != filters.length - 1)
		Filters += ","	
})

Filters += " ]" 



if(RecordList.length == 0)
{
  Invalid("RecordList is empty");
  return;
}



try{
  var code = loader.GetAdditionalData() + _.template($("#database_select_records_code").html())({page_number: PageNumber["updated"], page_size: PageSize["updated"],filters: Filters,variable:"VAR_" + RecordList,table: Table})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}