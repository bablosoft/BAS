<div class="container-fluid" style="padding-top:35px">
	<%= _.template($('#variable_constructor').html())({id:"Variable", description:tr("Variable With List"), default_variable: ""}) %>
    <%= _.template($('#variable_constructor').html())({id:"VariableNewList", description:tr("New List"), default_variable: "NEW_LIST"}) %>

</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>
