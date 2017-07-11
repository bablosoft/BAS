<div class="container-fluid">
	<%= _.template($('#input_constructor').html())({id:"Token", description:tr("Token Bot"), default_selector: "string", disable_int:true, value_string: ""}) %>
	<%= _.template($('#input_constructor').html())({id:"IdChat", description:tr("Id chat"), default_selector: "string", disable_int:true, value_string: ""}) %>
	<%= _.template($('#input_constructor').html())({id:"Message", description:tr("Message text"), default_selector: "string", disable_int:true, default_variable: ""}) %>
	<span data-preserve="true" data-preserve-type="check" data-preserve-id="Check">
		<div><input type="checkbox" id="Check"/> <label for="Check" class="tr">Add thread number to the beginning of the message</label></div>
	</span>
	<span data-preserve="true" data-preserve-type="check" data-preserve-id="Check1">
		<div style='margin-left:20px;'><input type="checkbox" id="Check1"/> <label for="Check1" class="tr">Add time to the beginning of the message [hh:mm:ss]</label></div>
	</span>

	<div style='margin-left:20px;' class="tr">How to <a href="#" onclick="BrowserAutomationStudio_OpenUrl('https://core.telegram.org/bots#3-how-do-i-create-a-bot')">create bot</a> token and <a href="#" onclick="BrowserAutomationStudio_OpenUrl('http://stackoverflow.com/questions/32423837/telegram-bot-how-to-get-a-group-chat-id-ruby-gem-telegram-bot')">get chat id</a></div>
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>
