function MultiSelect()
{
	this.Init = function()
	{

		var div = null, x1 = 0, y1 = 0, x2 = 0, y2 = 0;
		var last = []
		var active = false
		var changed = false
		function reCalc() {
			var x3 = Math.min(x1,x2);
			var x4 = Math.max(x1,x2);
			var y3 = Math.min(y1,y2);
			var y4 = Math.max(y1,y2);
			div.style.left = x3 + 'px';
			div.style.top = y3 + 'px';
			div.style.width = x4 - x3 + 'px';
			div.style.height = y4 - y3 + 'px';
			if(x4 - x3 > 10 && y4 - y3 > 10 && active)
				$(div).show();
			else
				$(div).hide();
		}

		function RectangleSelect(selector, x1, y1, x2, y2) {
			var elements = [];
			jQuery(selector).each(function() {
				var $this = jQuery(this);
				var offset = $this.offset();
				var x = offset.left;
				var y = offset.top;
				var w = $this.width();
				var h = $this.height();

				if (!(x+w<x1 || x2<x || y+h<y1 || y2<y))
				{
					var add = $this.attr("task-id")
					if(add != "0")
				    	elements.push(add);
				}
			});
			return elements;
		}

		function FindSelectedActions()
		{
			var tx1, tx2, ty1, ty2;
			if(x1 > x2)
			{
				tx1 = x2
				tx2 = x1
			}else
			{
				tx1 = x1
				tx2 = x2
			}
			if(y1 > y2)
			{
				ty1 = y2
				ty2 = y1
			}else
			{
				ty1 = y1
				ty2 = y2
			}

			var nxt = RectangleSelect(".taskcontainer",tx1,ty1,tx2,ty2)

			var remove = $(last).not(nxt).get()
			var add = $(nxt).not(last).get()
			if(add.length > 0)
			{

				add.forEach(function(id){

					var task = FindTaskById(parseInt(id))

					if(task)
					{

						if(!task.get("is_selected"))
						{
							changed = true
							_MainView.currentTargetId = IndexOf(parseInt(id))
							_MainView.ToggleSelection()
						}
					}

				})

				

			}
			if(remove.length > 0)
			{

				remove.forEach(function(id){

					var task = FindTaskById(parseInt(id))

					if(task)
					{
						if(task.get("is_selected"))
						{
							changed = true
							_MainView.currentTargetId = IndexOf(parseInt(id))
							_MainView.ToggleSelection()
						}
					}

				})				
			}
				
			last = nxt
		}

		$( document ).ready(function() {
			


			div = document.getElementById('multiselect')
			$("html").mousedown(function(e) {

				if($('.modal.in').length == 0 && e.button == 0)
        		{
        			var target = $(e.target)
        			if(target.hasClass("main") || target.hasClass("tool-margin") || (target.prop("tagName") == "HTML" && e.clientX < document.documentElement.offsetWidth) )
        			{
        				BrowserAutomationStudio_StopSaveToUndoManager = true
						active = true
						changed = false
						
						last = []

						if(!e.shiftKey)
							_MainView.ClearSelection()

						
						x1 = e.clientX + document.body.scrollLeft;
						y1 = e.clientY + document.body.scrollTop;
						x2 = x1;
						y2 = y1;
						
						reCalc();
					}
				}
			});
			$("html").mousemove(function(e) {
				if($('.modal.in').length == 0 && e.button == 0)
        		{
					x2 = e.clientX + document.body.scrollLeft;
					y2 = e.clientY + document.body.scrollTop;
					if(y2 > document.body.scrollHeight - 1)
						y2 = document.body.scrollHeight - 1
					if(x2 > document.body.scrollWidth - 1)
						x2 = document.body.scrollWidth - 1
					if(active)
					{
						FindSelectedActions();
						reCalc();
					}
				}
			});

			$("html").mouseup(function(e) {
				if($('.modal.in').length == 0 && e.button == 0)
        		{
					active = false
					$(div).hide();


					BrowserAutomationStudio_StopSaveToUndoManager = false
					if(changed)
					{
						BrowserAutomationStudio_SaveToUndoManager()
					}
					changed = false;
				}
			});

			
		});
	}


}