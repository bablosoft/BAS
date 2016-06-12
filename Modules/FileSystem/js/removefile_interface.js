<div class="container-fluid" style="margin-top:30px">
  <%= _.template($('#input_constructor').html())({id:"Value", description:tr("File/Folder Name"), default_selector: "string", disable_int:true}) %>
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>