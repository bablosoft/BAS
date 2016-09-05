<div class="container-fluid httpclientxpath">
  <%= _.template($('#input_constructor').html())({id:"Text", description:tr("Text To Apply"), default_selector: "string", disable_int:true}) %>
  <%= _.template($('#input_constructor').html())({id:"Value", description:tr("Xpath Query"), default_selector: "string", disable_int:true}) %>
  <%= _.template($('#variable_constructor').html())({id:"Save", description:tr("Variable To Save"), default_variable: "XPATH_TEXT"}) %>
  <span data-preserve="true" data-preserve-type="check" data-preserve-id="Check">
    <input type="checkbox" id="Check" checked="checked"/> <label for="Check" class="tr">Fail on error</label>
  </span>
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>