<div class="container-fluid">
  <%= _.template($('#input_constructor').html())({id:"Tags", description:tr("Tags. Can use several values separated by commas"), default_selector: "string", disable_int:true, value_string:"Microsoft Windows,Chrome", variants: ["*", 'Desktop', 'Mobile', 'Microsoft Windows', 'Microsoft Windows Phone', 'Apple Mac', 'Android', 'Linux', 'iPad', 'iPhone', 'Edge', 'Chrome', 'Safari', 'Firefox', 'IE'] }) %>
  <%= _.template($('#input_constructor').html())({id:"Key", description:tr("Service key. Can be empty"), default_selector: "string", disable_int:true }) %>
  <div style="margin-bottom:5px"><a href="#" style="margin-left:25px;" onclick="BrowserAutomationStudio_OpenUrl('https://fingerprints.bablosoft.com'); return false;"><span class="tr">Fingerprint switcher service</span></a></div>

  <%= _.template($('#variable_constructor').html())({id:"Save", description:tr("Variable To Save"), default_variable: "FINGERPRINT"}) %>

</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>
