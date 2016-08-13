<div class="container-fluid">
	<%= _.template($('#variable_constructor').html())({id:"Variable", description:tr("Variable With List"), default_variable: ""}) %>
	<%= _.template($('#variable_constructor').html())({id:"VariableSecond", description:tr("List To Compare"), default_variable: ""}) %>
	<%= _.template($('#variable_constructor').html())({id:"VariableResult", description:tr("Result"), default_variable: "LIST_COMPARE_RESULT"}) %>


</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>
