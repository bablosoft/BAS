<div class="container-fluid">
  <%= _.template($('#input_constructor').html())({id:"Value", description:tr("File path"), default_selector: "string", disable_int:true}) %>
  <%= _.template($('#variable_constructor').html())({id:"Save", description:tr("Variable To Save"), default_variable: "FILE_CONTENT"}) %>

  <%= _.template($('#input_constructor').html())({id:"From", description:tr("Start position"), default_selector: "int", disable_string:true, value_number: 0,size:3}) %>
  <%= _.template($('#input_constructor').html())({id:"To", description:tr("End position. Leave 0 to read all file."), default_selector: "int", disable_string:true, value_number: 0,size:3}) %>

  <span data-preserve="true" data-preserve-type="check" data-preserve-id="Check">
    <input type="checkbox" id="Check"/> <label for="Check" class="tr">Save In Base64 Format</label>
  </span>

</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>