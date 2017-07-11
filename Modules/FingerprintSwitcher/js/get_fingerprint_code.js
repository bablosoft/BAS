/*Browser*/
var q = (<%= tags %>).split(",").map(function(el){return el.trim()})
if(q.length == 0 || q.length == 1 && q[0] == "*")
{
    q = ((<%= key %>).length > 0) ? ("?key=" + encodeURIComponent(<%= key %>)) : ""
}else
{
    q = "?tags=" + encodeURIComponent(q.join(",")) + (((<%= key %>).length > 0) ? ("&key=" + encodeURIComponent(<%= key %>)) : "")
}
var api_url = "https://fingerprints.bablosoft.com/prepare" + q

_switch_http_client_internal()

_do(function(){
	if(_iterator()>15)
		fail("Query limit reached")
	
	http_client_get2(api_url,{method:("GET")})!	
	<%= variable %> = http_client_content()

	try
	{
		var json = JSON.parse(<%= variable %>)
		if(!json["trylater"])
			_break()
	}catch(e){}

	sleep(20000)!
})!  

    
_switch_http_client_main()