<div class="container-fluid" style="margin-top:40px">
  <%= _.template($('#input_constructor').html())({id:"IddleTime", description:tr("Time spent on page(seconds)"), default_selector: "int", disable_string:true, value_number: 5}) %>
  <%= _.template($('#input_constructor').html())({id:"Distribution", description:tr("Action distribution. 1 - scroll, 2 - long move, 3 - short move, 4 - sleep"), default_selector: "expression", disable_string:true,disable_int:true, value_string: "[1,1,2,3,3,3,4,4]"}) %>
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>
