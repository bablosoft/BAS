_L = 
{
	"Task Description":{"ru": "Описание задания"},
	"disabled" :{"ru": "отключено"},
	"(This button will only change task description)" :{"ru": "(Эта кнопка изменит только описание задания)"},
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
	"Fail Number" :{"ru": "Неудачных выполнений"},
	"Selected" :{"ru": "Выбрано"},
	"Copy (Ctrl-C)" :{"ru": "Копировать (Ctrl-C)"},
	"Cut (Ctrl-X)" :{"ru": "Вырезать (Ctrl-X)"},
	"Paste (Ctrl-V)" :{"ru": "Вставить (Ctrl-V)"},
	"Check All" :{"ru": "Выделить Все"},
	"Clear Selection" :{"ru": "Очистить Выделение"},
	"Execute only this action" :{"ru": "Выполнить только это действие"},
	"Move Execution Point Here" :{"ru": "Переместить точку выполнения"},
	"Variable Inspector" :{"ru": "Инспектор Переменных"},
	"Variables will be loaded on next script pause" :{"ru": "Переменные будут загружены при следующей паузе сценария"},
	"Previous" :{"ru": "Предыдущий"},
	"Next" :{"ru": "Следующий"},
	"Search" :{"ru": "Поиск"},
	" and " :{"ru": " и "},
	" more" :{"ru": " других"},
	"Enable selected":{"ru": "Включить выбранные"},
	"Disable selected":{"ru": "Отключить выбранные"},
	"Set color":{"ru": "Установить цвет"},
	"Clear color":{"ru": "Очистить цвет"},
	"for selected actions":{"ru": "для выбранных действий"},
	"Color":{"ru": "Цвет"},
	"Select all":{"ru": "Выбрать все"},
	"Unfold all":{"ru": "Развернуть все"},
	"Fold all":{"ru": "Cвернуть все"},
	"Task repetitions.":{"ru": "Повторение заданий."},
	"Set success and fail number to big values if you want to repeat script several times with different data.":{"ru": "Установите количество успешных и неудачных выполнений большими числами, если вы хотите повторить скрипт несколько раз с разными данными."},
	"Insert indicator.":{"ru": "Индикатор вставки."},
	"This is insert indicator, new actions will be added here. You can shift indicator before adding new actions or move them later.":{"ru": "Это индикатор вставки, сюда будут добавляться новые действия. Вы можете сдвинуть индикатор перед добавлением новых действий или переместить их позже."},
	"Variables list.":{"ru": "Список переменных."},
	"Click here to see variables list and values.":{"ru": "Нажмите сюда, чтобы увидеть список переменных и их значений."},
	"Skip":{"ru": "Пропустить"},
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

		var all = $("*[title]")
		
		for(var i = 0;i< all.length;i++)
		{
			var el = $(all[i])
			el.attr("title",tr(el.attr("title")))
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