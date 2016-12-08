<div class="container-fluid">
   <%= _.template($('#input_constructor').html())({id:"Service", description:tr(""), default_selector: "string", disable_int:true, value_string: "smspva.com", variants: ["smspva.com","sms-activate.ru","sms-reg.com"]}) %>
  
  <div class="col-xs-12">
    <form class="form-horizontal">
      <div class="form-group">
        <div class="col-xs-2">
          <div class="input-group">
            <span data-preserve="true" data-preserve-type="select" data-preserve-id="Select">
              <select class="form-control input-sm" id="Select" placeholder="Site">
                <option value="*" selected="selected">*</option>
                <option value="4game">4game</option>
                <option value="1688.com">1688.com</option>
                <option value="AOL">AOL</option>
                <option value="Auto.RU">Auto.RU</option>
                <option value="Avito">Avito</option>
                <option value="Badoo">Badoo</option>
                <option value="BurgerKing">BurgerKing</option>
                <option value="CenoBoy">CenoBoy</option>
                <option value="COM.NU">COM.NU</option>
                <option value="dodopizza.ru">dodopizza.ru</option>
                <option value="Drom.RU">Drom.RU</option>
                <option value="Drug Vokrug">Drug Vokrug</option>
                <option value="Facebook">Facebook</option>
                <option value="Fiverr">Fiverr</option>
                <option value="Fotostrana">Fotostrana</option>
                <option value="Gem4me">Gem4me</option>
                <option value="GetTaxi">GetTaxi</option>
                <option value="GMail">GMail</option>
                <option value="HotMail">HotMail</option>
                <option value="ICQ">ICQ</option>
                <option value="IMO">IMO</option>
                <option value="Instagram">Instagram</option>
                <option value="JTI Winston">JTI Winston</option>
                <option value="KakaoTalk">KakaoTalk</option>
                <option value="LD-Info.ru">LD-Info.ru</option>
                <option value="like4u">like4u</option>
                <option value="Line Messenger">Line Messenger</option>
                <option value="LinkedIn">LinkedIn</option>
                <option value="Mail.RU">Mail.RU</option>
                <option value="mamba">mamba</option>
                <option value="MeetMe">MeetMe</option>
                <option value="NaSIMke.ru">NaSIMke.ru</option>
                <option value="Naver">Naver</option>
                <option value="OD">OD</option>
                <option value="OLX">OLX</option>
                <option value="Open I Messenger">Open I Messenger</option>
                <option value="Prostockvashino">Prostockvashino</option>
                <option value="Qiwi">Qiwi</option>
                <option value="Rembler">Rembler</option>
                <option value="Royal Canin">Royal Canin</option>
                <option value="SEOsprint.net">SEOsprint.net</option>
                <option value="Sipnet.ru">Sipnet.ru</option>
                <option value="SmartCall">SmartCall</option>
                <option value="Steam">Steam</option>
                <option value="Talk2">Talk2</option>
                <option value="Taxi Maksim">Taxi Maksim</option>
                <option value="Telegram">Telegram</option>
                <option value="The Insiders">The Insiders</option>
                <option value="Tinder">Tinder</option>
                <option value="Twilio">Twilio</option>
                <option value="Twitter">Twitter</option>
                <option value="Ubank.ru">Ubank.ru</option>
                <option value="Uber">Uber</option>
                <option value="Viber">Viber</option>
                <option value="VK">VK</option>
                <option value="VOXOX.COM">VOXOX.COM</option>
                <option value="WebMoney">WebMoney</option>
                <option value="Webtransfer">Webtransfer</option>
                <option value="WeChat">WeChat</option>
                <option value="Weebly">Weebly</option>
                <option value="WhatsAPP">WhatsAPP</option>
                <option value="Yahoo">Yahoo</option>
                <option value="Yandex">Yandex</option>
              </select>
            </span>
          </div>
        </div>
        <label class="control-label text-right tr" style="padding-top:5px !important;">Site</label>
      </div>
    </form>
  </div>

  <%= _.template($('#input_constructor').html())({id:"Apikey", description:tr("Api key"), default_selector: "string", disable_int:true}) %>

  <%= _.template($('#variable_constructor').html())({id:"Save", description:tr("Variable To Save"), default_variable: "PHONE_NUMBER"}) %>

</div>

<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>
