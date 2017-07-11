function DragAndDrop()
{
	var DeleteAfterInsert = []
	this.Init = function()
	{

		$('*').on('dragstart', function(event) { 

			var target = $(event.currentTarget)
			if(target.hasClass("taskcontainer"))
			{
				var id = parseInt(target.attr("task-id"))
				var task = FindTaskById(id)

				if(task && id != 0)
				{
					var label = "\"" + target.find(".tooltitle").text().trim() + "\"";
					var selectedtext = "";
					

					if(!task.get("is_selected"))
					{
						//Single
						var Ids = [id]
						var dat = task.dat()
						if(dat)
						{
							if(dat["role"] == "master")
							{
								Ids.push(dat["slave"])
							}else if(dat["role"] == "slave")
							{
								Ids.push(dat["master"])
							}
						}
						DeleteAfterInsert = Ids.slice(0);

						selectedtext = _MainView.CopyToString(Ids)

					}else
					{
						//All selection

						var selection = _MainView.GetSelection()
						DeleteAfterInsert = selection.slice(0);


						if(selection.length > 1)
						{
							label += tr(" and ") + (selection.length - 1).toString() + tr(" more")
						}

						selectedtext = _MainView.CopyToString()
					}
					var dragelement = $("#draganddrop")
					
					dragelement.html(label)
	    			event.originalEvent.dataTransfer.setDragImage(dragelement[0], 0, 0);
	    			//console.log(selectedtext)
	    			event.originalEvent.dataTransfer.setData('bas/draganddrop', selectedtext);

	    			$("#container").addClass("dragactive")

				}
				
				
			}
		});

		$('*').on('dragend', function(event) { 
			$(".toolinsert").removeClass("toolinsertdrop")
			$("#container").removeClass("dragactive")
		});

		$('.toolinsertdata').on('dragenter', function(event) { 
			var target = $(event.currentTarget)

			if(target.hasClass("toolinsertdata"))
			{
				target.find(".toolinsert").addClass("toolinsertdrop")
			}

		});

		$('.toolinsertdata').on('dragleave', function(event) { 
			var target = $(event.currentTarget)
			if(target.hasClass("toolinsertdata"))
			{
				target.find(".toolinsert").removeClass("toolinsertdrop")
			}
		});


		$('.toolinsertdata').on('dragover', function(event) { 
			var target = $(event.currentTarget)
			if(target.hasClass("toolinsertdata"))
			{
				var data = event.originalEvent.dataTransfer.getData('bas/draganddrop')
				data = data.trim()
				if(data.length > 0)
				{
					event.preventDefault();
				}
			}
		});


		$('.toolinsertdata').on('drop', function(event) { 
			var target = $(event.currentTarget)
			if(target.hasClass("toolinsertdata"))
			{
				BrowserAutomationStudio_StopSaveToUndoManager = true

				var datainsertindex = parseInt(target.attr("data-insert-index"))
				var datainsertparent = parseInt(target.attr("data-insert-parent"))
				var data = event.originalEvent.dataTransfer.getData('bas/draganddrop')

        		_MainView.model.attributes["insert_index"] = datainsertindex
            	_MainView.model.attributes["insert_parent"] = datainsertparent
            	_MainView.UpdateInsertDataInterface()
        		
				var new_ids = _MainView.PasteFinal(data, true)
				var needclear = DeleteAfterInsert.length > 0
				if(needclear && new_ids.length > 0)
				{
					var new_id = new_ids[0]
					needclear = !IsAnsectorOfAny(DeleteAfterInsert,new_id)
				}

				if(needclear)
				{
					_MainView.model.set("dontsend",true)
			        _CacheLoader.SetDontUpdate(true)

					var stillexists = true

					while(stillexists)
					{
						stillexists = false
						_.every(_MainView.collection.models, function(task,index){
							if(DeleteAfterInsert.indexOf(parseInt(task.get("id"))) >= 0)
							{
								stillexists = true
								_MainView.currentTargetId = index
								_MainView.Delete()
								return false
							}
							return true
						})
					}
				    _CacheLoader.SetDontUpdate(false)
    			    _CacheLoader.Start()


					_MainView.model.set("dontsend",false)
					BrowserAutomationStudio_StopSaveToUndoManager = false
					BrowserAutomationStudio_SaveToUndoManager()
					BrowserAutomationStudio_AskForVariablesUpdateIfNeeded()
					_MainView.send()
					_MainView.render()
				}else
				{
					BrowserAutomationStudio_StopSaveToUndoManager = false
					BrowserAutomationStudio_SaveToUndoManager()
				}

				DeleteAfterInsert = []

				$(".toolinsert").removeClass("toolinsertdrop")
				$("#container").removeClass("dragactive")

				new_ids.forEach(function(id){
					BrowserAutomationStudio_FocusActionFast(parseInt(id))
				})

			}
		});



	}

}