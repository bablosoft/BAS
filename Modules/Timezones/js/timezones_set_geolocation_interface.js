<div class="container-fluid" style="margin-top:30px">
  <%= _.template($('#input_constructor').html())({id:"Latitude", description:tr("Latitude"), default_selector: "expression", disable_int:true, value_string: "51.4997398" }) %>
  <%= _.template($('#input_constructor').html())({id:"Longitude", description:tr("Longitude"), default_selector: "expression", disable_int:true, value_string: "-0.0898039" }) %>
  
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>