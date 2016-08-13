<div class="container-fluid">
    <%= _.template($('#input_constructor').html())({id:"File", description:tr("File path"), default_selector: "string", disable_int:true}) %>
    <%= _.template($('#input_constructor').html())({id:"Value", description:tr("Data"), default_selector: "string", disable_int:true}) %>
    <div class="tooltipinternal tr">It is better to use <a href="#!/result">Result</a> action to output result.</div>
    <span data-preserve="true" data-preserve-type="check" data-preserve-id="Check3">
      <div><input type="checkbox" id="Check3"/> <label for="Check3" class="tr">Add line ending symbol</label></div>
    </span>
    <span data-preserve="true" data-preserve-type="check" data-preserve-id="Check">
      <div><input type="checkbox" id="Check"/> <label for="Check" class="tr">Append</label></div>
    </span>
    <span data-preserve="true" data-preserve-type="check" data-preserve-id="Check2">
      <div><input type="checkbox" id="Check2"/> <label for="Check2" class="tr">Data Is In Base64 Format</label></div>
    </span>

</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>