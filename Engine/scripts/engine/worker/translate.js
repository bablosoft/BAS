_L = 
{
	"Failed to load page ": {"ru": "Не удалось загрузить страницу "},
	"Failed to wait for changing url ": {"ru": "Не удалось дождаться смены url "},
	"Failed to wait for loading ": {"ru": "Не удалось дождаться загрузки "},
	"Failed to wait for content ": {"ru": "Не удалось дождаться содержимого "},
	"Failed to wait for css ": {"ru": "Не удалось дождаться элемента "},
	"Failed to wait of state complete": {"ru": "Не удалось дождаться полной загрузки страницы"}
}


function tr(key)
{
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