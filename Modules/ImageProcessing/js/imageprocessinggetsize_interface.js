<div class="container-fluid" style="margin-top:30px">
  <%= _.template($('#input_constructor').html())({id:"Id", description:tr("Image id"), default_selector: "string", disable_int:true}) %>
  <%= _.template($('#variable_constructor').html())({id:"Width", description:tr("Variable to save width"), default_variable: "IMAGE_WIDTH"}) %>
  <%= _.template($('#variable_constructor').html())({id:"Height", description:tr("Variable to save height"), default_variable: "IMAGE_HEIGHT"}) %>

</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>