var GroupId = GetInputConstructorValue("GroupId", loader);
var Variable = this.$el.find("#Record").val().toUpperCase();

var Table = $("#Table").val();

var params = []

var els = $("*[data-table-id=" + Table + "]")
for(var i = 0;i<els.length;i++)
{
	var el = els[i]
	var id = el.attributes["data-id"]["value"]
	var p = GetInputConstructorValue("Table_" + Table + "_Column_" + id, loader);
	params.push(id)
	params.push(p["updated"])
}


try{
  var code = loader.GetAdditionalData() + _.template($("#database_insert_record_code").html())({variable: "VAR_" + Variable,group:GroupId["updated"],table: Table, params: params})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}