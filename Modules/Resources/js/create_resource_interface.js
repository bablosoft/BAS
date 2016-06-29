<div class="container-fluid">
    <%= _.template($('#input_constructor').html())({id:"Name", description:tr("Resource name"), default_selector: "string", disable_int:true, disable_expression:true}) %>
    <%= _.template($('#input_constructor').html())({id:"SuccessNumber", description:tr("Success Usage"), default_selector: "int", disable_string:true, value_number:1}) %>
    <%= _.template($('#input_constructor').html())({id:"FailNumber", description:tr("Fail Usage"), default_selector: "int", disable_string:true, value_number:1}) %>
	<%= _.template($('#input_constructor').html())({id:"SimultaneousUsage", description:tr("Simultaneous Usage"), default_selector: "int", disable_string:true, value_number:1}) %>
	<%= _.template($('#input_constructor').html())({id:"Interval", description:tr("Interval Between Usage"), default_selector: "int", disable_string:true, value_number:5000}) %>
	<span data-preserve="true" data-preserve-type="check" data-preserve-id="Check">
         <input type="checkbox" id="Check"/> <label for="Check" class="tr">Greedy Usage Algorithm</label>
	</span>
	<span data-preserve="true" data-preserve-type="check" data-preserve-id="Check2">
         <input type="checkbox" id="Check2"/> <label for="Check2" class="tr">Wait For Resource</label>
	</span>
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true, name: tr("Create Resource")}) %>
