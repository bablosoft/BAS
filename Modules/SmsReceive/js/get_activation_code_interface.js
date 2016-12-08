<div class="container-fluid">
  
  <%= _.template($('#input_constructor').html())({id:"Number", description:tr("Number"), default_selector: "string", disable_int:true}) %>

  <%= _.template($('#input_constructor').html())({id:"MaxWait", description:tr("Max wait minutes"), default_selector: "int", disable_string:true, value_number:10}) %>

  <%= _.template($('#variable_constructor').html())({id:"Save", description:tr("Variable To Save"), default_variable: "ACTIVATION_CODE"}) %>

</div>

<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>
