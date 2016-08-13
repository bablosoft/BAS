<div class="container-fluid">
	<%= _.template($('#variable_constructor').html())({id:"Variable", description:tr("Variable To Save List"), default_variable: "NEW_LIST"}) %>
    <%= _.template($('#input_constructor').html())({id:"Value1", description:tr("Value 1. Can be empty"), default_selector: "string"}) %>
    <%= _.template($('#input_constructor').html())({id:"Value2", description:tr("Value 2. Can be empty"), default_selector: "string"}) %>
    <%= _.template($('#input_constructor').html())({id:"Value3", description:tr("Value 3. Can be empty"), default_selector: "string"}) %>
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>
