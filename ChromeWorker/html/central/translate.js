_L = 
{
	"Proxies reconnect" :{"ru": "Восстановление соединения"},
	"Emulate mouse movements" :{"ru": "Эмулировать движения мыши"},
	"Settings" :{"ru": "Настройки"},
	"Top Panel Height (pixels)" :{"ru": "Высота Верхней Панели (пикселей)"},
	"Left Panel Width (pixels)" :{"ru": "Ширина Левой Панели (пикселей)"},
	"Zoom (%)" :{"ru": "Масштаб"},
	"Enable Flash" :{"ru": "Использовать Флеш"},
	"Skip Frames" :{"ru": "Пропуск Кадров"},
	"Number of frames to skip in run mode. The higher the value, the lower the use of resources. 1 - means no skip, 75 is default value." :{"ru": "Пропуск кадров в рабочем режиме. Чем больше это значение, тем меньше используется ресурсов. 1 - означает отрисовывать все кадры, 75 - стандартное значение."},
	"Force UTF-8 Encoding" :{"ru": "Преобразовывать все страницы в UTF-8"},
	"Ok" :{"ru": "Ок"},
	"Cancel" :{"ru": "Отмена"},
	"Defaults" :{"ru": "По Умолчанию"},
	"Disable System Log" :{"ru": "Отключить лог системных сообщений"},
	"Restart browser process on thread start" :{"ru": "Перезапускать процесс в начале работы потока"},
	"Disable webrtc and canvas" :{"ru": "Отключить webrtc и canvas"}
}


function tr(key)
{
	if(typeof(key) == "undefined")
	{

		var all = $(".tr")
		
		for(var i = 0;i< all.length;i++)
		{
			var el = $(all[i])
			if(typeof(el.attr("tr")) == "undefined" || el.attr("tr") != "true" )
			{
				el.html(tr(el.html()))
				el.attr("tr","true")
			}
		}

		all = $(".trtitle")
		
		for(var i = 0;i< all.length;i++)
		{
			var el = $(all[i])
			if(typeof(el.attr("tr")) == "undefined" || el.attr("tr") != "true" )
			{
				el.attr("title",tr(el.attr("title")))
				el.attr("tr","true")
			}
		}

		var all = $("*[placeholder]")
		
		for(var i = 0;i< all.length;i++)
		{
			var el = $(all[i])
			if(typeof(el.attr("tr")) == "undefined" || el.attr("tr") != "true" )
			{
				el.attr("placeholder",tr(el.attr("placeholder")))
				el.attr("tr","true")
			}
		}

		
		
		return;
	}

	
	if(typeof(_K) == "undefined" || _K == "en")
		return key;
	if(key in _L)
	{

		if(_K in _L[key])
		{
			return _L[key][_K]
		}
	}
	return key;
}