<div class="container-fluid" style="margin-top:30px">
  <%= _.template($('#input_constructor').html())({id:"Id", description:tr("Image id"), default_selector: "string", disable_int:true}) %>

</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>