var getTime = function() {

	var checkTime = function (i) {
		return (i < 10) ? "0" + i : i;
	}

	var d = new Date();
	var hh = checkTime(d.getHours());
	var mm = checkTime(d.getMinutes());
	var ss = checkTime(d.getSeconds());
	
	return '[' + hh + ':' + mm + ':' + ss + ']'
}

var mess, url, json, tmp = "";

tmp = encodeURIComponent(<%= message %>)

<% if(is_num_thread && is_time) { %>
	mess = "<b>" + getTime() +" Поток №" + thread_number() + " : </b>" + tmp
<% } else if(is_num_thread) { %>
    mess = "<b>Поток №" + thread_number() + " : </b>" + tmp
<% } else if(is_time) { %>
	mess = "<b>" + getTime() + " </b>" + tmp
<% } else { %>
	mess = tmp
<% } %>	

url = "https://api.telegram.org/bot"+ <%= token %> + "/sendMessage?chat_id=" + <%= chat_id %> + "&text=" + mess + (<%= is_num_thread %> === true || <%= is_time %> === true ? '&parse_mode=HTML' : '')

_switch_http_client_internal()
http_client_get2(url, {method:("GET")})!
var json = JSON.parse(http_client_content())
_switch_http_client_main()
if (!json['ok'])
	fail(json['description'], false)
