<div class="container-fluid">
	<%= _.template($('#input_constructor').html())({id:"String", description:tr("String To Parse"), default_selector: "string", disable_int:true}) %>
	<%= _.template($('#input_constructor').html())({id:"Separator", description:tr("Separator"), default_selector: "string", disable_int:true, value_string: ","}) %>
	<%= _.template($('#variable_constructor').html())({id:"VariableResult", description:tr("Result List"), default_variable: "PARSED_LIST"}) %>
    
    
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>
