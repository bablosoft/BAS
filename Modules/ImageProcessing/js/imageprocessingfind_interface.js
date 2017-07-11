<div class="container-fluid" style="margin-top:30px">
  <%= _.template($('#input_constructor').html())({id:"Id1", description:tr("Image target id"), default_selector: "string", disable_int:true}) %>
  <%= _.template($('#input_constructor').html())({id:"Id2", description:tr("Image source id"), default_selector: "string", disable_int:true}) %>
  <%= _.template($('#variable_constructor').html())({id:"X", description:tr("Found x coordinate in target image"), default_variable: "FOUND_SUBIMAGE_X"}) %>
  <%= _.template($('#variable_constructor').html())({id:"Y", description:tr("Found y coordinate in target image"), default_variable: "FOUND_SUBIMAGE_Y"}) %>
  <%= _.template($('#variable_constructor').html())({id:"Threshold", description:tr("How well the image fits. 100 - exactly fits, 0 - does not fit at all."), default_variable: "FOUND_THRESHOLD"}) %>
  
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>