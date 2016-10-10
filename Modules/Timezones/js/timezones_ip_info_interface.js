<div class="container-fluid">
<%= _.template($('#input_constructor').html())({id:"Value", description:tr("Ip string. Ipv6 string should be enclosed with square brackets."), default_selector: "string", disable_int:true}) %>
<%= _.template($('#variable_constructor').html())({id:"SaveValid", description:tr("Is Valid"), default_variable: "IPINFO_VALID"}) %>
<%= _.template($('#variable_constructor').html())({id:"SaveCountry", description:tr("Country"), default_variable: "IPINFO_SIZE"}) %>
<%= _.template($('#variable_constructor').html())({id:"SaveCity", description:tr("City"), default_variable: "IPINFO_CITY"}) %>
<%= _.template($('#variable_constructor').html())({id:"SaveLatitude", description:tr("Latitude"), default_variable: "IPINFO_LATITUDE"}) %>
<%= _.template($('#variable_constructor').html())({id:"SaveLongitude", description:tr("Longitude"), default_variable: "IPINFO_LONGITUDE"}) %>
<%= _.template($('#variable_constructor').html())({id:"SaveTimezone", description:tr("Timezone"), default_variable: "IPINFO_TIMEZONE"}) %>
<%= _.template($('#variable_constructor').html())({id:"SaveOffset", description:tr("Offset"), default_variable: "IPINFO_OFFSET"}) %>
<%= _.template($('#variable_constructor').html())({id:"SaveDstOffset", description:tr("Dst Offset"), default_variable: "IPINFO_DST_OFFSET"}) %>
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>