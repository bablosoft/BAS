<div class="container-fluid">
    <%= _.template($('#resource_constructor').html())({id:"ResourceName", description:tr("Resource name")}) %>
    <%= _.template($('#variable_constructor').html())({id:"Save", description:tr("List To Save"), default_variable: "RESOURCE_AS_LIST"}) %>
    
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>
