<div class="container-fluid httpclientgetheader">
      <%= _.template($('#input_constructor').html())({id:"Value", description:tr("File Name"), default_selector: "string", disable_int:true}) %>
      <%= _.template($('#variable_constructor').html())({id:"SaveExists", description:tr("File Exists"), default_variable: "FILEINFO_EXISTS"}) %>
      <%= _.template($('#variable_constructor').html())({id:"SaveSize", description:tr("File Size"), default_variable: "FILEINFO_SIZE"}) %>
      <%= _.template($('#variable_constructor').html())({id:"SaveDirectory", description:tr("File Base Directory"), default_variable: "FILEINFO_BASE_DIRECTORY"}) %>
      <%= _.template($('#variable_constructor').html())({id:"SaveIsDirectory", description:tr("Is Directory"), default_variable: "FILEINFO_IS_DIRECTORY"}) %>
      <%= _.template($('#variable_constructor').html())({id:"SaveLastModified", description:tr("Last Modified"), default_variable: "FILEINFO_LAST_MODIFIED"}) %>
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>