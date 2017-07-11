<div class="container-fluid" style="margin-top:30px">
  <%= _.template($('#input_constructor').html())({id:"Data", description:tr("Image data as base64"), default_selector: "string", disable_int:true}) %>
  <%= _.template($('#variable_constructor').html())({id:"Save", description:tr("Variable to save image id"), default_variable: "LOADED_IMAGE_ID"}) %>

</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>