<div class="container-fluid" style="margin-top:30px">
  <%= _.template($('#input_constructor').html())({id:"Id", description:tr("Image id"), default_selector: "string", disable_int:true}) %>
  <%= _.template($('#input_constructor').html())({id:"Width", description:tr("Width"), default_selector: "int", disable_string:true, value_number:100, min_number:1}) %>
  <%= _.template($('#input_constructor').html())({id:"Height", description:tr("Height"), default_selector: "int", disable_string:true, value_number:100, min_number:1}) %>
  
  
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>