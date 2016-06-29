<div class="container-fluid" style="padding-top:35px;">
    <%= _.template($('#resource_constructor').html())({id:"ResourceName", description:tr("Resource name")}) %>
    <%= _.template($('#input_constructor').html())({id:"Data", description:tr("Data"), default_selector: "string", disable_int:true}) %>


    <span data-preserve="true" data-preserve-type="check" data-preserve-id="Check">
         <input type="checkbox" id="Check" checked="checked"/> <label for="Check" class="tr">Add to file/database instantly</label>
	</span>
	<span data-preserve="true" data-preserve-type="check" data-preserve-id="Check2">
         <input type="checkbox" id="Check2"/> <label for="Check2" class="tr">Only write to file/database</label>
	</span>
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true, name: tr("Add Element")}) %>
