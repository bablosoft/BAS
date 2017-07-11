<div class="container-fluid">
  <%= _.template($('#input_constructor').html())({id:"Fingerprint", description:tr("Fingerprint"), default_selector: "string", disable_int:true}) %>

  <div class="tooltipinternal tr">This action will restart browser process and thereby reset all settings(proxies, headers, etc), so the best place to use this action is thread start.</div>
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>
