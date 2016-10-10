<div class="container-fluid" style="margin-top:30px">
  <%= _.template($('#input_constructor').html())({id:"Value", description:tr("Ip string. Ipv6 string should be enclosed with square brackets."), default_selector: "string", disable_int:true}) %>
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>