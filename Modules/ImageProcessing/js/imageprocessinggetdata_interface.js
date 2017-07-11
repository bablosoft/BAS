<div class="container-fluid" style="margin-top:30px">
  <%= _.template($('#input_constructor').html())({id:"Id", description:tr("Image id"), default_selector: "string", disable_int:true}) %>
  <%= _.template($('#variable_constructor').html())({id:"Save", description:tr("Variable to save image data"), default_variable: "IMAGE_DATA"}) %>

</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>