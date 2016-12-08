<div class="container-fluid">
    <%= _.template($('#input_constructor').html())({id:"File", description:tr("File path"), default_selector: "string", disable_int:true}) %>
    <%= _.template($('#variable_constructor').html())({id:"Save", description:tr("List To Write To File"), default_variable:""}) %>
    <span data-preserve="true" data-preserve-type="check" data-preserve-id="Check">
      <div><input type="checkbox" id="Check"/> <label for="Check" class="tr">Append</label></div>
    </span>
    <span data-preserve="true" data-preserve-type="check" data-preserve-id="Check2">
      <div><input type="checkbox" id="Check2"/> <label for="Check2" class="tr">Add line ending symbol</label></div>
    </span>

</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>