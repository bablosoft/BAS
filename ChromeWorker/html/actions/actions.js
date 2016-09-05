_A = {
   "addtab":{
      "name":"Add Tab",
      "description":"Add Tab",
      "template" : "{{Url}}"
   },
   "selecttab":{
      "name":"Select Tab",
      "description":"Select Tab",
      "template" : "{{Index}}"
   },
   "closetab":{
      "name":"Close Tab",
      "description":"Close Tab",
      "template" : "{{Index}}"
   },
   "load":{
      "name":"Load",
      "description":"Load specific url",
      "class": "browser",
      "template" : "{{LoadUrl}}"
   },
   "url":{
      "name":"Current Url",
      "description":"Get current url",
      "template":"{{SaveUrl}}"
   },
   "html":{
      "name":"Page Html",
      "description":"Save page html to variable",
      "template":"{{Save}}"
   },
   "type":{
      "name":"Type",
      "class": "browser",
      "description":"Type text on page. For example, put email in input field",
      "template":"{{TypeData}}"
   },
   "resize":{
      "name":"Resize",
      "description":"Change browser size",
      "template":"{{ResizeX}} : {{ResizeY}}"
   },
   "proxy":{
      "name":"Proxy",
      "description":"Set proxy",
      "template":"{{ProxyText}}"
   },
   "javascript":{
      "name":"Javascript",
      "description":"Execute javascript",
      "template":"{{Value}} -> {{Save}}"
   },
   "onloadjavascript":{
      "name":"Execute On Every Page Load In Browser",
      "description":"Execute javascript on every page load in browser",
      "template":"{{Value}}"
   },
   "reset":{
      "name":"Reset",
      "class": "browser",
      "description":"Clear all browser data",
      "template":""
   },
   "openfile":{
      "name":"Open File Result",
      "description":"Set open file dialog result",
      "template":"{{Value}}"
   },
   "promptresult":{
      "name":"Prompt Result",
      "description":"Set prompt result",
      "template":"{{Value}}"
   },
   "httpauth":{
      "name":"Http Auth",
      "description":"Set http auth login and password",
      "template":"{{Login}}:{{Password}}"
   },
   "scroll":{
      "name":"Scroll",
      "class": "browser",
      "description":"Scroll to position",
      "template":"{{X}},{{Y}}"
   },
   "renderscreen":{
      "name":"Render",
      "description":"Render screen part to variable as png base64 encoded",
      "template":"{{X}},{{Y}},{{Width}},{{Height}} -> {{Save}}"
   },
   "solvecaptcha":{
      "name":"Solve Captcha",
      "description":"Solve captcha",
      "template":"{{Value}} -> {{Save}}"
   },
   "solverfailed":{
      "name":"Captcha Failed",
      "description":"Captcha Failed",
      "template":""
   },
   "timeout":{
      "name":"Timeout",
      "description":"Set Timeout",
      "template":"{{Value}}"
   },
   "if":{
      "name":"If",
      "description":"Execute conditional actions",
      "template":"{{IfExpression}}"
   },
   "while":{
      "name":"While",
      "description":"Execute while loop",
      "template":"{{WhileExpression}}"
   },
   "for":{
      "name":"For",
      "description":"Execute for loop",
      "template":"{{ForFrom}} : {{ForTo}}"
   },
   "foreach":{
      "name":"Foreach",
      "description":"Execute foreach loop",
      "template":"{{ForArray}}"
   },
   "break":{
      "name":"Break",
      "description":"Stop loop",
      "template":""
   },
   "continue":{
      "name":"Continue",
      "description":"Next loop iteration",
      "template":""
   },
   "success":{
      "name":"Success",
      "class": "logic",
      "description":"Finish script with success result",
      "template":"{{SuccessMessage}}"
   },
   "fail":{
      "name":"Fail",
      "class": "logic",
      "description":"Finish script with fail result",
      "template":"{{FailMessage}}"
   },
   "die":{
      "name":"End Script",
      "class": "logic",
      "description":"Immediately End Script",
      "template":"{{FailMessage}}"
   },
   "ignoreerrors":{
      "name":"Ignore Errors",
      "description":"Ignore errors",
      "template":""
   },
   "setvariable":{
      "name":"Set Variable",
      "description":"Sets or creates variable",
      "template":"{{SetVariableValue}} -> {{SetVariableName}}"
   },
   "incvariable":{
      "name":"Increase Variable",
      "description":"Increase Variable",
      "template":"{{IncVariableValue}} -> {{SetVariableName}}"
   },
   "executefunction":{
      "name":"Call Function",
      "class": "logic",
      "description":"Call function",
      "template":"{{FunctionName}}"
   },
   "log":{
      "name":"Log",
      "description":"Output string to log",
      "template":"{{LogText}}"
   },
   "result":{
      "name":"Result",
      "description":"Save result",
      "template":"{{Value}}"
   },
   "custom":{
      "name":"Custom",
      "description":"Execute custom code",
      "template":"{{Code}}"
   },
   "base64":{
      "name":"Base64 Encode/Decode",
      "description":"Base64 encode or decode",
      "template":"{{Value}} -> {{Save}}"
   },
   "globalset":{
      "name":"Set Global Variable",
      "description":"Set global variable",
      "template":"{{Value}} -> {{Name}}"
   },
   "globalget":{
      "name":"Get Global Variable",
      "description":"Get global variable",
      "template":"{{Name}} -> {{Save}}"
   },
   "parseline":{
      "name":"Parse Line",
      "description":"Parse line like this 'a1:a2:a3' and save to variables",
      "template":"{{Value}} -> {{VariablesList}}"
   },
   "template":{
      "name":"Template",
      "description":"Use Template",
      "template":"{{Template}} -> {{Save}}"
   },
   "replacestring":{
      "name":"Replace String",
      "description":"Replace all occurrences of one string to another",
      "template":"{{Value}} -> {{Save}}"
   },
   "randomstring":{
      "name":"Random String",
      "description":"Generate random string",
      "template":"{{Save}}"
   },
   "randomint":{
      "name":"Random Number",
      "description":"Generate random integer",
      "template":"{{Save}}"
   },
   "setheader":{
      "name":"Set Header",
      "description":"Set HTTP Headers, like user agent, accept language, etc",
      "template":"{{Value}} -> {{Name}}"
   },
   "getcookiesforurl":{
      "name":"Get Cookies For Url",
      "description":"Get cookies for url",
      "template":"{{Value}} -> {{Save}}"
   },
   "savecookies":{
      "name":"Save Cookies",
      "description":"Save all cookies to variable",
      "template":"{{Save}}"
   },
   "restorecookies":{
      "name":"Restore Cookies",
      "description":"Restore cookies, which is saved with Save Cookies command",
      "template":"{{Value}}"
   },
   "cachemaskallow":{
      "name":"Cache Mask Allow",
      "description":"Allow save loaded url content to cache",
      "template":"{{Value}}"
   },
   "cachemaskdeny":{
      "name":"Cache Mask Deny",
      "description":"Deny save loaded url content to cache",
      "template":"{{Value}}"
   },
   "requestmaskallow":{
      "name":"Request Mask Allow",
      "description":"Allow load url, which matching mask",
      "template":"{{Value}}"
   },
   "requestmaskdeny":{
      "name":"Request Mask Deny",
      "description":"Deny load url, which matching mask",
      "template":"{{Value}}"
   },
   "cleardata":{
      "name":"Clear Cached Data",
      "description":"Clear loaded cache data",
      "template":""
   },
   "clearmasks":{
      "name":"Clear Cache Masks",
      "description":"Clear cache masks",
      "template":""
   },
   "getstatus":{
      "name":"Get Status",
      "description":"Get url load status",
      "template":"{{Value}} -> {{Save}}"
   },
   "isloaded":{
      "name":"Is Loaded",
      "description":"Check if url is loaded",
      "template":"{{Value}} -> {{Save}}"
   },
   "getfromcache":{
      "name":"Get Cached Item",
      "description":"Get base64 encoded cached page",
      "template":"{{Value}} -> {{Save}}"
   },
   "waitfullload":{
      "name":"Wait Full Page Load",
      "description":"Wait for full page load",
      "template":""
   },
   "waitload":{
      "name":"Wait Url Loaded",
      "description":"Wait until browser will load url",
      "template":"{{Wait}}"
   },
   "waiturl":{
      "name":"Wait Address Bar",
      "description":"Wait address bar will contain url",
      "template":"{{Wait}}"
   },
   "waitcontent":{
      "name":"Wait Text",
      "description":"Wait until specific text will be present on page",
      "template":"{{Wait}}"
   },
   "waitcss":{
      "name":"Wait Css",
      "description":"Wait until specific css selector will return non empty result",
      "template":"{{Wait}}"
   },
   "sleep":{
      "name":"Sleep",
      "description":"Sleep for a specific time",
      "template":"{{sleepfromto}}"
   },
   "emailsettings":{
      "name":"Configure",
      "description":"Configure email settings",
      "template":"{{Host}}"
   },
   "emailproxy":{
      "name":"Email Proxy",
      "description":"Configure email proxy",
      "template":"{{ProxyText}}"
   },
   "emaillength":{
      "name":"Messages Length",
      "description":"Get messages length",
      "template":"{{Save}}"
   },
   "emailsearchfirst":{
      "name":"Search First",
      "description":"Search for first message",
      "template":"{{Save}}"
   },
   "emailsearchall":{
      "name":"Search All",
      "description":"Search for all messages",
      "template":"{{Save}}"
   },
   "emailpull":{
      "name":"Get Message",
      "description":"Pull message",
      "template":"{{Save}}"
   },
   "httpclientproxy":{
      "name":"HTTP-Client Proxy",
      "description":"Set proxy for http client",
      "template":"{{ProxyText}}"
   },
   "httpclientreset":{
      "name":"HTTP-Client Reset",
      "description":"Reset http client",
      "template":""
   },
   "httpclientget":{
      "name":"Get",
      "description":"Make GET request",
      "template":"{{Value}}"
   },
   "httpclientpost":{
      "name":"Post",
      "description":"Make POST request",
      "template":"{{Value}}"
   },
   "httpclientdownload":{
      "name":"Download",
      "description":"Download to file",
      "template":"{{Value}} -> {{File}}"
   },
   "httpclienturl":{
      "name":"Current Url",
      "description":"Get http client current url",
      "template":"{{Save}}"
   },
   "httpclientcontent":{
      "name":"Content",
      "description":"Get http client request result",
      "template":"{{Save}}"
   },
   "httpclientstatus":{
      "name":"Status",
      "description":"Get http client request status",
      "template":"{{Save}}"
   },
   "httpclientgetheader":{
      "name":"Get Header",
      "description":"Get http client header",
      "template":"{{Value}} -> {{Save}}"
   },
   "httpclientsetheader":{
      "name":"HTTP-Client Set Header",
      "description":"Set http client header",
      "template":"{{Value}} -> {{Name}}"
   },
   "httpclientclearheader":{
      "name":"Clear Headers",
      "description":"Clear http client request headers",
      "template":""
   },
   "httpclientgetcookiesforurl":{
      "name":"Get Cookies For Url",
      "description":"Get cookies for url",
      "template":"{{Value}} -> {{Save}}"
   },
   "httpclientsavecookies":{
      "name":"HTTP-Client Save Cookies",
      "description":"Save all cookies to variable",
      "template":"{{Save}}"
   },
   "httpclientrestorecookies":{
      "name":"HTTP-Client Restore Cookies",
      "description":"Restore cookies, which is saved with Save Cookies command",
      "template":"{{Value}}"
   },
   "httpclientfailonerror":{
      "name":"Set Fail On Error",
      "description":"Fail if error during http request",
      "template":"{{SetFailed}}"
   },
   "httpclientiserror":{
      "name":"Is Error",
      "description":"Check if error",
      "template":"{{Save}}"
   },
   "httpclientgeterrorstring":{
      "name":"Get Error String",
      "description":"Get last error string",
      "template":"{{Save}}"
   },
   "httpclientxpathxml":{
      "name":"Xpath Get Xml",
      "description":"Execute xpath query and get result xml",
      "template":"{{Value}} -> {{Save}}"
   },
   "httpclientxpathxmllist":{
      "name":"Xpath Get Xml List",
      "description":"Execute xpath query and get result xml list",
      "template":"{{Value}} -> {{Save}}"
   },
   "httpclientxpathtext":{
      "name":"Xpath Get Text",
      "description":"Execute xpath query and get result text",
      "template":"{{Value}} -> {{Save}}"
   },
   "httpclientxpathtextlist":{
      "name":"Xpath Get Text List",
      "description":"Execute xpath query and get result text list",
      "template":"{{Value}} -> {{Save}}"
   },
   "httpclientxpathcount":{
      "name":"Xpath Get Count",
      "description":"Execute xpath query and get result count",
      "template":"{{Value}} -> {{Save}}"
   },
   "httpclientxpathexists":{
      "name":"Xpath Get Exists",
      "description":"Execute xpath query and check if exists",
      "template":"{{Value}} -> {{Save}}"
   },
   "click":{
      "name":"Click",
      "class": "browser",
      "description":"Click",
      "template":"{{ClickX}},{{ClickY}}"
   },
   "move":{
      "name":"Move",
      "class": "browser",
      "description":"Move",
      "template":"{{MoveX}},{{MoveY}}"
   },
   "moveandclick":{
      "name":"Move And Click",
      "class": "browser",
      "description":"Move And Click",
      "template":"{{X}},{{Y}}"
   },
   "loopelement":{
      "name":"Start Loop",
      "description":"Start Loop",
      "template":"{{PATH}}"
   },
   "waitelement":{
      "name":"Wait While Element Exists",
      "description":"Wait While Element Exists",
      "template":"{{PATH}}"
   },
   "xml":{
      "name":"Get Element Content",
      "description":"Get Element Content",
      "template":"{{PATH}} -> {{SaveXml}}"
   },
   "text":{
      "name":"Get Element Text",
      "description":"Get Element Text",
      "template":"{{PATH}} -> {{SaveText}}"
   },
   "script":{
      "name":"Execute Javascript On Element",
      "description":"Execute Javascript On Element",
      "template":"{{ScriptValue}} -> {{PATH}}"
   },
   "clickelement":{
      "name":"Click On Element",
      "class": "browser",
      "description":"Click On Element",
      "template":"{{PATH}}"
   },
   "moveelement":{
      "name":"Move On Element",
      "class": "browser",
      "description":"Move On Element",
      "template":"{{PATH}}"
   },
   "moveandclickelement":{
      "name":"Move And Click On Element",
      "class": "browser",
      "description":"Move And Click On Element",
      "template":"{{PATH}}"
   },
   "clear":{
      "name":"Clear Edit",
      "class": "browser",
      "description":"Clear Edit",
      "template":"{{PATH}}"
   },
   "typeelement":{
      "name":"Type Text",
      "class": "browser",
      "description":"Type Text",
      "template":"{{TypeData}} -> {{PATH}}"
   },
   "exist":{
      "name":"Is Element Exists",
      "description":"Is Element Exists",
      "template":"{{PATH}} -> {{Save}}"
   },
   "style":{
      "name":"Get Element Style",
      "class": "browser",
      "description":"Get Element Style",
      "template":"{{PATH}} -> {{Save}}"
   },
   "check":{
      "name":"Set Checkbox",
      "class": "browser",
      "description":"Set Checkbox",
      "template":"{{PATH}}"
   },
   "focus":{
      "name":"Scroll To Element",
      "class": "browser",
      "description":"Scroll To Element",
      "template":"{{PATH}}"
   },
   "set":{
      "name":"Set Combobox Value",
      "class": "browser",
      "description":"Set Combobox Value",
      "template":"{{Value}} -> {{PATH}}"
   },
   "set_integer":{
      "name":"Set Combobox Index",
      "class": "browser",
      "description":"Set Combobox Index",
      "template":"{{Value}} -> {{PATH}}"
   },
   "set_random":{
      "name":"Set Combobox To Random",
      "class": "browser",
      "description":"Set Combobox To Random",
      "template":"{{PATH}}"
   },
   "attr":{
      "name":"Get Element Attribute",
      "class": "browser",
      "description":"Get Element Attribute",
      "template":"{{PATH}} -> {{Save}}"
   },
   "set_attr":{
      "name":"Set Element Attribute",
      "class": "browser",
      "description":"Set Element Attribute",
      "template":"{{Value}} -> {{PATH}}"
   },
   "captcha":{
      "name":"Solve Captcha",
      "description":"Solve Captcha",
      "template":"{{PATH}} -> {{Save}}"
   },
   "length":{
      "name":"Get Element Count",
      "description":"Get Element Count",
      "template":"{{PATH}} -> {{Save}}"
   }
}


_AL = 
{
   "Add Tab" : {"ru": "Добавить вкладку"},
   "Close Tab" : {"ru": "Закрыть вкладку"},
   "Select Tab" : {"ru": "Переключиться на вкладку"},

	"Load " : {"ru": "Загрузить "},
	"Wait while element ": {"ru": "Ждать пока элемент "},
	" appear on page": {"ru": " появится на странице"},
   "Email Proxy": {"ru": "Почта Прокси"},
   "HTTP-Client Proxy": {"ru": "HTTP-Клиент Прокси"},
   "HTTP-Client Reset": {"ru": "HTTP-Клиент Сброс"},
   "HTTP-Client Set Header": {"ru": "HTTP-Клиент Установить Заголовок"},
   "HTTP-Client Save Cookies": {"ru": "HTTP-Клиент Сохранить cookies"},
   "HTTP-Client Restore Cookies": {"ru": "HTTP-Клиент Загрузить cookies"},


	"Click" : {"ru": "Кликнуть"},
	"Move" : {"ru": "Двигать Мышь"},
	"Move And Click" : {"ru": "Двигать Мышь И Кликнуть"},
	"Start Loop" : {"ru": "Начать Цикл"},
	"Wait While Element Exists" : {"ru": "Ждать Появления Элемента"},
	"Get Element Content" : {"ru": "Получить Код Элемента"},
	"Get Element Text" : {"ru": "Получить Текст"},
	"Execute Javascript On Element" : {"ru": "Выполнить Javascript На Элементе"},
	"Click On Element" : {"ru": "Кликнуть На Элемент"},
	"Move On Element" : {"ru": "Двигать Мышь Над Элементом"},
	"Move And Click On Element" : {"ru": "Двигать Мышь И Кликнуть На Элемент"},
	"Clear Edit" : {"ru": "Очистить Поле"},
	"Type Text" : {"ru": "Ввод текста"},
	"Is Element Exists" : {"ru": "Проверить Существование"},
	"Get Element Style" : {"ru": "Получить Стиль Элемента"},
	"Set Checkbox" : {"ru": "Установить Чекбокс"},
	"Scroll To Element" : {"ru": "Прокрутка К Элементу"},
	"Set Combobox Value" : {"ru": "Установить Значение Комбобокса"},
	"Set Combobox Index" : {"ru": "Установить Индекс Комбобокса"},
	"Set Combobox To Random" : {"ru": "Выбрать Случайный Элемент Из Комбобокса"},
	"Get Element Attribute" : {"ru": "Получить Атрибут Элемента"},
	"Set Element Attribute" : {"ru": "Установить Атрибут Элемента"},
	"Get Element Count" : {"ru": "Получить Количество Элементов"},

	"Else" : {"ru": "Else"},
	"Initialize" : {"ru": "Инициализация"},
	"Load" : {"ru": "Загрузить"},
	"Current Url" : {"ru": "Текущий Url"},
	"Page Html" : {"ru": "Код страницы"},
	"Type" : {"ru": "Ввод текста"},
	"Resize" : {"ru": "Разрешение"},
	"Proxy" : {"ru": "Прокси"},
	"Javascript" : {"ru": "Яваскрипт"},
	"Execute On Every Page Load In Browser" :{"ru": "Выполнять при каждой загрузке страницы в браузере"},
	"Reset" : {"ru": "Сброс"},
	"Open File Result" : {"ru": "Диалог Открыть Файл"},
	"Prompt Result": {"ru": "Окно \"prompt\""},
	"Http Auth": {"ru": "HTTP Аутентификация"},
	"Scroll" : {"ru": "Прокрутка"},
	"Render" : {"ru": "Скриншот"},
	"Solve Captcha" : {"ru": "Решить Капчу"},
	"Captcha Failed": {"ru": "Решено Неверно"},
	"Timeout": {"ru": "Таймаут"},

	"If" : {"ru": "If"},
	"While" : {"ru": "While"},
	"For" : {"ru": "For"},
	"Break" : {"ru": "Break"},
	"Success" : {"ru": "Success"},
	"Fail" : {"ru": "Fail"},
	"End Script": {"ru": "Прервать Скрипт"},
	"Ignore Errors": {"ru": "Игнорировать Ошибки"},
	"Set Variable" : {"ru": "Установить переменную"},
	"Increase Variable": {"ru": "Увеличить переменную"},
	"Call Function" : {"ru": "Вызов функции"},
	"Log" : {"ru": "Лог"},
	"Result" : {"ru": "Результат"},
	"Custom" : {"ru": "Выполнить код"},
	"Base64 Encode/Decode" : {"ru": "Base64"},
	"Set Global Variable" : {"ru": "Присвоить глобальную переменную"},
	"Get Global Variable" : {"ru": "Читать глобальную переменную"},
	"Parse Line" : {"ru": "Парсить строку"},
	"Template": {"ru": "Шаблон"},
	"Replace String": {"ru": "Заменить Строку"},
	"Random String": {"ru": "Случайная строка"},
	"Random Number": {"ru": "Случайное Число"},

	"Set Header" : {"ru": "Установить заголовок"},
	"Get Cookies For Url" : {"ru": "Получить cookies для url"},
	"Save Cookies" : {"ru": "Сохранить cookies"},
	"Restore Cookies" : {"ru": "Загрузить cookies"},
	"Cache Mask Allow" : {"ru": "Разрешить кэш"},
	"Cache Mask Deny" : {"ru": "Запретить кэш"},
	"Request Mask Allow" : {"ru": "Разрешать запрос"},
	"Request Mask Deny" : {"ru": "Запретить запрос"},
	"Clear Cached Data" : {"ru": "Очистить кэшированные данные"},
	"Clear Cache Masks" : {"ru": "Очистить маски"},
	"Get Status" : {"ru": "Получить статус запроса"},
	"Is Loaded" : {"ru": "Был ли запрос"},
	"Get Cached Item" : {"ru": "Получить элемент кэша"},
	"Wait Full Page Load": {"ru": "Ждать Полной Загрузки"},
	"Wait Url Loaded" : {"ru": "Ждать Загрузки Url"},
	"Wait Address Bar" : {"ru": "Ждать адреса браузера"},
	"Wait Text" : {"ru": "Ждать текст"},
	"Wait Css" : {"ru": "Ждать css"},
	"Sleep" : {"ru": "Спать"},
	"Configure" : {"ru": "Настроить"},
	"Messages Length" : {"ru": "Количество писем"},
	"Search First" : {"ru": "Найти письмо"},
	"Search All" : {"ru": "Найти все письма"},
	"Get Message" : {"ru": "Получить сообщение"},

	"Get" : {"ru": "Get запрос"},
	"Post" : {"ru": "Post запрос"},
	"Download" : {"ru": "Скачать"},
	"Content" : {"ru": "Содержание ответа"},
	"Status" : {"ru": "Статус ответа"},
	"Get Header" : {"ru": "Получить заголовок"},
	"Clear Headers" : {"ru": "Очистить заголовки"},
	"Set Fail On Error" : {"ru": "Завершать работу после ошибки"},
	"Is Error" : {"ru": "Была ли ошибка"},
	"Get Error String" : {"ru": "Получить текст ошибки"},
	"Xpath Get Xml" : {"ru": "Xpath получить xml"},
   "Xpath Get Xml List" : {"ru": "Xpath получить каждый xml"},
	"Xpath Get Text" : {"ru": "Xpath получить текст"},
   "Xpath Get Text List" : {"ru": "Xpath получить каждый текст"},
	"Xpath Get Count" : {"ru": "Xpath получить количество элементов"},
	"Xpath Get Exists" : {"ru": "Xpath проверить существование"},
}

   function max_length(data,len)
    {
      var res = data
      if(res.length > len)
      {
        res = res.substr(0,len - 4)
        res+=" ..."
      }
      return res

    }

 function prepare_styles(code, task_name)
 {
   try
   {
      if(task_name == "Else")
       return /*"tooltitle-red"*/ ""

     var match = code.match("Dat:([^\*]+)")
     if(!match)
       return ""

     var dat = JSON.parse(b64_to_utf8(match[1]))

     var Type = _A[dat["s"]]["class"]
     if(typeof(Type) == "undefined")
      return ""
     else if(Type == "browser")
      return /*"tooltitle-blue"*/ ""
     else
      return "tooltitle-red"

   }catch(e)
   {

   }
   return ""
 }
 
 function prepare_title(code, task_name)
 {
   try
   {
     if(task_name == "Initialize")
       return tr("Initialize")
     if(task_name == "Else")
       return tr("Else")

     var match = code.match("Dat:([^\*]+)")
     if(!match)
       return ""


     var dat = JSON.parse(b64_to_utf8(match[1]))

     return tr(_A[dat["s"]]["name"])
   }catch(e)
   {

   }
   return ""
 }

 function prepare_edit_body(code, task_name)
 {
   try
   {
     var match = code.match("Dat:([^\*]+)")
     if(!match)
       return ""

     var dat = JSON.parse(b64_to_utf8(match[1]))

     if(!("v" in dat))
     {
         return ""
     }

     return task_name;

   }catch(e)
   {
     return e
   }
   return task_name
 }

 function prepare_body(code, task_name)
 {
   try
   {
     if(task_name == "Initialize")
       return tr("Initialize")
     if(task_name == "Else")
       return tr("Else")

     var match = code.match("Dat:([^\*]+)")
     if(!match)
       return ""


     var dat = JSON.parse(b64_to_utf8(match[1]))

     return BrowserAutomationStudio_GenerateActionText(task_name,dat);

   }catch(e)
   {
     return e
   }
   return task_name
 }




function BrowserAutomationStudio_GenerateActionText(action, data)
{
	var State = data["s"]

   if("v" in data && action.length > 0)
   {
      return max_length(action,50)
   }

	var Data = data["d"]
	var Template = _A[State]["template"]

   if(Template.length == 0)
      return tr(_A[State]["name"])


	var Split = Template.split(/\{\{(.*?)\}\}/g)
	var Res = ""
   var LastArrow = false
   var IsEmpty = true
	for(var i = 0;i<Split.length;i++)
	{
		if(i%2 == 0)
		{
         if(Split[i].length > 0)
            IsEmpty = false

         LastArrow = Split[i].indexOf("->") >= 0
			Res += _.escape(tr(Split[i])).replace("-&gt;","<i class='fa fa-arrow-circle-right ' aria-hidden='true'></i>")

		}else
		{
         var Class = (LastArrow)? "textitemsignificant":""
         
			if(Split[i] == "PATH")
			{
				var Current = data["p"]["current"]
            var DataName = ""
				if(Current != "none")
				{
					DataName = data["p"][Current]	
				}else
				{
					DataName = "body"
				}
            if(DataName.length > 0)
               IsEmpty = false

				Res += "<span class=" + Class + ">" + _.escape(DataName) + "</span>"
			}else
			{
				var El = Data.filter(function(el){return el["id"] == Split[i]})
				if(El.length > 0)
				{
					var DataName = El[0]
               if(DataName["data"].length > 0)
                  IsEmpty = false
					Res += "<span class=" + Class + ">" + _.escape(max_length(DataName["data"].replace(/(?:\r\n|\r|\n)/g," "),50)) + "</span>"
				}			
			}

			
		}
		
	}

   if(IsEmpty)
      Res = tr(_A[State]["name"])

	return Res

	

	
}