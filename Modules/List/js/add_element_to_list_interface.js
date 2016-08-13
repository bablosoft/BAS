<div class="container-fluid" style="padding-top:35px;">
	<%= _.template($('#variable_constructor').html())({id:"Variable", description:tr("Variable With List"), default_variable: ""}) %>
    <%= _.template($('#input_constructor').html())({id:"Value", description:tr("Value to add"), default_selector: "string"}) %>
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>
