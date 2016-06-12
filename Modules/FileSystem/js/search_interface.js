<div class="container-fluid filewrite">
	<%= _.template($('#input_constructor').html())({id:"Folder", description:tr("Search In Folder"), default_selector: "string", disable_int:true}) %>
    <%= _.template($('#input_constructor').html())({id:"Mask", description:tr("Filename Mask"), default_selector: "string", disable_int:true, value_string:"*"}) %>
    <%= _.template($('#input_constructor').html())({id:"FileContains", description:tr("File Data Must Contain. Can Be Blank"), default_selector: "string", disable_int:true}) %>
    <div>
	    <span data-preserve="true" data-preserve-type="check" data-preserve-id="Check">
	      <input type="checkbox" id="Check" checked/> <label for="Check" class="tr">Include Folders</label>  
	    </span>
		<span data-preserve="true" data-preserve-type="check" data-preserve-id="Check2">
	    	<input type="checkbox" id="Check2" checked/> <label for="Check2" class="tr">Include Files</label>
	    </span>
	    <span data-preserve="true" data-preserve-type="check" data-preserve-id="Check3">
	    	<input type="checkbox" id="Check3" checked/> <label for="Check3" class="tr">Search In Subfolders</label> 
	    </span>
    </div>
    <%= _.template($('#variable_constructor').html())({id:"Save", description:tr("Variable To Save Result"), default_variable: "FILE_SEARCH_RESULT"}) %>

</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>