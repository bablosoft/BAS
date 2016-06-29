<div class="container-fluid" style="padding-top:35px;">
    <%= _.template($('#resource_constructor').html())({id:"ResourceName", description:tr("Resource name")}) %>
    <span data-preserve="true" data-preserve-type="check" data-preserve-id="Check">
         <input type="checkbox" id="Check" checked="checked"/> <label for="Check" class="tr">Delete from file/database instantly</label>
	</span>

    <div class="tooltipinternal tr">In order to manage resource lifetime manually, you should first set resource success and fail number to a big value.</div>

</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true, name: tr("Delete Current Element")}) %>
