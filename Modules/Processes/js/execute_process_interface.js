<div class="container-fluid">
  <%= _.template($('#input_constructor').html())({id:"Location", description:tr("Executable location"), default_selector: "string", disable_int:true}) %>
  <%= _.template($('#input_constructor').html())({id:"Arguments", description:tr("Command line"), default_selector: "string", disable_int:true}) %>
  <span data-preserve="true" data-preserve-type="check" data-preserve-id="Check">
    <input type="checkbox" id="Check" checked="checked"/> <label for="Check" class="tr">Wait while process will finish</label>
  </span>
  <%= _.template($('#variable_constructor').html())({id:"Save", description:tr("Variable To Save"), default_variable: "PROCESS_OUTPUT"}) %>
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>