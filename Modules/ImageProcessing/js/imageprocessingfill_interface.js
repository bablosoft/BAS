<div class="container-fluid" style="margin-top:30px">
  <%= _.template($('#input_constructor').html())({id:"Id", description:tr("Image id"), default_selector: "string", disable_int:true}) %>
  <%= _.template($('#input_constructor').html())({id:"X", description:tr("X"), default_selector: "int", disable_string:true, value_number:0, min_number:0}) %>
  <%= _.template($('#input_constructor').html())({id:"Y", description:tr("Y"), default_selector: "int", disable_string:true, value_number:0, min_number:0}) %>
  <%= _.template($('#input_constructor').html())({id:"Width", description:tr("Width"), default_selector: "int", disable_string:true, value_number:100, min_number:1}) %>
  <%= _.template($('#input_constructor').html())({id:"Height", description:tr("Height"), default_selector: "int", disable_string:true, value_number:100, min_number:1}) %>
  <%= _.template($('#input_constructor').html())({id:"ColorR", description:tr("Color Red"), default_selector: "int", disable_string:true, value_number:255, min_number:0, max_number:255}) %>
  <%= _.template($('#input_constructor').html())({id:"ColorG", description:tr("Color Green"), default_selector: "int", disable_string:true, value_number:255, min_number:0, max_number:255}) %>
  <%= _.template($('#input_constructor').html())({id:"ColorB", description:tr("Color Blue"), default_selector: "int", disable_string:true, value_number:255, min_number:0, max_number:255}) %>
  <%= _.template($('#input_constructor').html())({id:"ColorA", description:tr("Color Transparency"), default_selector: "int", disable_string:true, value_number:255, min_number:0, max_number:255}) %>

</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>