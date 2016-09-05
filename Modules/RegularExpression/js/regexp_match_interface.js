<div class="container-fluid">
    <%= _.template($('#input_constructor').html())({id:"Value", description:tr("String To Apply Regexp"), default_selector: "string", disable_int:true}) %>
    <%= _.template($('#input_constructor').html())({id:"Regexp", description:tr("Regular Expression"), default_selector: "string", disable_int:true}) %>
    <%= _.template($('#variable_constructor').html())({id:"Result", description:tr("Result"), default_variable: "STRING_MATCHES"}) %>

    <a href="#" style="margin-left:25px" onclick="BrowserAutomationStudio_OpenUrl('https://bablosoft.github.io/RegexpConstructor/'); return false;"><span class="tr">Regular Expression Constructor</span></a> <span class="tr">can help you to create regexp.</span>
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>
