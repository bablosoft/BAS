<div class="container-fluid" style="margin-top:30px">

  <%= _.template($('#input_constructor').html())({id:"Id", description:tr("Image id"), default_selector: "string", disable_int:true}) %>
  <%= _.template($('#input_constructor').html())({id:"X", description:tr("X"), default_selector: "int", disable_string:true, value_number:0, min_number:0}) %>
  <%= _.template($('#input_constructor').html())({id:"Y", description:tr("Y"), default_selector: "int", disable_string:true, value_number:0, min_number:0}) %>
  <%= _.template($('#input_constructor').html())({id:"Width", description:tr("Width"), default_selector: "int", disable_string:true, value_number:800, min_number:0}) %>
  <%= _.template($('#input_constructor').html())({id:"Height", description:tr("Height"), default_selector: "int", disable_string:true, value_number:800, min_number:0}) %>
  <%= _.template($('#variable_constructor').html())({id:"Save", description:tr("Variable to save image id"), default_variable: "CROPPED_IMAGE_ID"}) %>

</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>