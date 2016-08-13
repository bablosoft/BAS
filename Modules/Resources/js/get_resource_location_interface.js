<div class="container-fluid">
    <%= _.template($('#resource_constructor').html())({id:"ResourceName", description:tr("Resource name")}) %>
    <div class="tooltipinternal tr">Resource Location is filename for LinesFromFile resource, url for LinesFromUrl and directory location for FilesFromDirectory resource type.</div>
    <%= _.template($('#variable_constructor').html())({id:"Save", description:tr("Variable To Save"), default_variable: "RESOURCE_LOCATION"}) %>
    
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>
