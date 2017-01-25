<div class="container-fluid">
  <%= _.template($('#input_constructor').html())({id:"Command", description:tr("Command"), default_selector: "string", disable_int:true, disable_editor:true, disable_string:true, use_textarea:true, size: 8, disable_type_chooser:true,textarea_height:80}) %>

  <span data-preserve="true" data-preserve-type="check" data-preserve-id="Check">
    <input type="checkbox" id="Check" checked="checked"/> <label for="Check" class="tr">Wait while process will finish</label>
  </span>
  <%= _.template($('#variable_constructor').html())({id:"Save", description:tr("Variable To Save"), default_variable: "PROCESS_OUTPUT"}) %>
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>