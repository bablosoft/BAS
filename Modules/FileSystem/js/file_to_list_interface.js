<div class="container-fluid">
  <%= _.template($('#input_constructor').html())({id:"Value", description:tr("File path"), default_selector: "string", disable_int:true}) %>
  <%= _.template($('#variable_constructor').html())({id:"Save", description:tr("List To Save"), default_variable: "LIST_WITH_FILE_CONTENT"}) %>

</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>