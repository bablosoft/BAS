<div class="container-fluid" style="margin-top:30px">
  <%= _.template($('#input_constructor').html())({id:"Id1", description:tr("Image target id"), default_selector: "string", disable_int:true}) %>
  <%= _.template($('#input_constructor').html())({id:"Id2", description:tr("Image source id"), default_selector: "string", disable_int:true}) %>
  <%= _.template($('#input_constructor').html())({id:"X", description:tr("X"), default_selector: "int", disable_string:true, value_number:100, min_number:0}) %>
  <%= _.template($('#input_constructor').html())({id:"Y", description:tr("Y"), default_selector: "int", disable_string:true, value_number:100, min_number:0}) %>
  
  
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>