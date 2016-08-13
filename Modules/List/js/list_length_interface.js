<div class="container-fluid" style="padding-top:35px;">
	<%= _.template($('#variable_constructor').html())({id:"Variable", description:tr("Variable With List"), default_variable: ""}) %>
    <%= _.template($('#variable_constructor').html())({id:"VariableLength", description:tr("Variable To Save Length"), default_variable: "LIST_LENGTH"}) %>
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>
