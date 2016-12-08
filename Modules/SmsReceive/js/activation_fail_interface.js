<div class="container-fluid">
  <%= _.template($('#input_constructor').html())({id:"Number", description:tr("Number"), default_selector: "string", disable_int:true}) %>
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>
