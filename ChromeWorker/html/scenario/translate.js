_L = 
{
	"Delete this and all upper" :{"ru": "Удалить это действие и предыдущие"},
	"Delete this and all lower" :{"ru": "Удалить это действие и следующие"},
	"Toggle selection" :{"ru": "Выбрать"},
	"Edit" :{"ru": "Редактировать"},
	"Delete this" :{"ru": "Удалить"},
	"Run until this" :{"ru": "Выполнить до этого действия"},
	"Actions" :{"ru": "Действия"},
	"Copy selected" :{"ru": "Копировать выбранные"},
	"Paste selected" :{"ru": "Вставить"},
	"Cut selected" :{"ru": "Вырезать выбранные"},
	"Delete selected" :{"ru": "Удалить выбранные"},
	"Clear selection" :{"ru": "Очистить выделение"},
	"Edit Task" :{"ru": "Редактировать задание"},
	"Task Name" :{"ru": "Имя задания"},
	"Don't run when recording" :{"ru": "Не выполнять в режиме записи"},
	"Ok" :{"ru": "Ok"},
	"Cancel" :{"ru": "Отмена"},
	"Add/Edit Function" :{"ru": "Добавить/Редактировать Функцию"},
	"OnApplicationStart" :{"ru": "OnApplicationStart"},
	"function will be run at first place." :{"ru": "функция будет выполнена первой."},
	"Don't recover after failure" :{"ru": "Не продолжать после ошибки"},
	"Function Name" :{"ru": "Имя функции"},
	"Function" :{"ru": "Функция"},
	"Thread Number" :{"ru": "Количество потоков"},
	"Success Number" :{"ru": "Успешных выполнений"},
	"Fail Number" :{"ru": "Неудачных выполнений"}
}


function tr(key)
{
	if(typeof(key) == "undefined")
	{

		var all = $(".tr")
		
		for(var i = 0;i< all.length;i++)
		{
			var el = $(all[i])
			el.html(tr(el.html()))
		}

		var all = $("*[placeholder]")
		
		for(var i = 0;i< all.length;i++)
		{
			var el = $(all[i])
			el.attr("placeholder",tr(el.attr("placeholder")))
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