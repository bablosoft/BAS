<div class="container-fluid" style="padding-top:35px;">
	<%= _.template($('#variable_constructor').html())({id:"Variable", description:tr("Variable With List"), default_variable: ""}) %>
    <%= _.template($('#input_constructor').html())({id:"Value", description:tr("Value to add"), default_selector: "string"}) %>
    <%= _.template($('#input_constructor').html())({id:"Index", description:tr("Index"), default_selector: "int", value_number: 0, min_number: -999999}) %>
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>
