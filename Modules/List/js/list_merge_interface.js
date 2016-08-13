<div class="container-fluid" style="padding-top:35px">
	<%= _.template($('#variable_constructor').html())({id:"Variable", description:tr("Variable With List"), default_variable: ""}) %>
	<%= _.template($('#variable_constructor').html())({id:"VariableSecond", description:tr("List To Merge"), default_variable: ""}) %>
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>
