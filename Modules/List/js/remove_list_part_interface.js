<div class="container-fluid">
	<%= _.template($('#variable_constructor').html())({id:"Variable", description:tr("Variable With List"), default_variable: ""}) %>
    <%= _.template($('#input_constructor').html())({id:"IndexStart", description:tr("Start Index"), default_selector: "int", disable_string:true, min_number: -999999, value_number: 0}) %>
    <%= _.template($('#input_constructor').html())({id:"IndexEnd", description:tr("End Index"), default_selector: "int", disable_string:true, min_number: -999999, value_number: 10}) %>
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>
