<div class="container-fluid captcha2">
  <%= _.template($('#path').html())({selector:selector}) %>
  <%= _.template($('#input_constructor').html())({id:"TimesToSolve", description:tr("How many times try to solve"), default_selector: "int", disable_string:true, value_number: 10, size: 3}) %>
  <%= _.template($('#input_constructor').html())({id:"Method", description:tr("Solve Method"), default_selector: "string", disable_int:true, value_string: "manual", variants: ["manual","rucaptcha-newapi","2captcha-newapi","antigate-newapi","capmonsterimage","capmonsteraudio","dbc", "rucaptcha", "2captcha", "antigate"], size: 3}) %>
  <%= _.template($('#input_constructor').html())({id:"Rucaptcha", description:tr("Antigate/Rucaptcha/2captcha/DBC Key. Can be blank"), default_selector: "string", disable_int:true}) %>
  <%= _.template($('#input_constructor').html())({id:"Server", description:tr("Server url. Can be blank"), default_selector: "string", disable_int:true}) %>

</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true, name: tr("Solve Recaptcha 2.0")}) %>
