<div class="container-fluid" style="margin-top:30px">
  <%= _.template($('#input_constructor').html())({id:"Value", description:tr("Timezone UTC offset."), default_selector: "int", disable_string:true, value_number: 60 , variants: ["-840","-780","-765","-720","-660","-630","-600","-570","-540","-525","-510","-480","-420","-390","-360","-345","-330","-300","-270","-240","-210","-180","-120","-60","0","60","120","180","210","240","300","360","420","480","540","570","600","660","720"] }) %>
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>