<div class="container-fluid">
    <%= _.template($('#input_constructor').html())({id:"Label", description:tr("Label which is hown to user"), default_selector: "string"}) %>
    <%= _.template($('#variable_constructor').html())({id:"Variable", description:tr("Variable to save input"), default_variable: "USER_INPUT"}) %>
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>
