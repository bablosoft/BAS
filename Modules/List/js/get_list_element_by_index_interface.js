<div class="container-fluid">
	<%= _.template($('#variable_constructor').html())({id:"Variable", description:tr("Variable With List"), default_variable: ""}) %>
    <%= _.template($('#input_constructor').html())({id:"Index", description:tr("Index"), default_selector: "int", disable_string:true, value_number:0,min_number:-9999999}) %>
    <span data-preserve="true" data-preserve-type="check" data-preserve-id="Check">
    	<input type="checkbox" id="Check"/> <label for="Check" class="tr">Remove From List</label>
    </span>
    <%= _.template($('#variable_constructor').html())({id:"VariableResult", description:tr("List Element"), default_variable: "LIST_ELEMENT"}) %>
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>
