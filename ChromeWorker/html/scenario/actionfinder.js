function ActionFinder()
{

	var LastSearch = ""
	var ActionMark = null;

	var ScrollSearchId = -1;
	var ScrollSearchLastTerm = "";

	this.ResetSearch = function()
	{
		ScrollSearchId = -1
	}


	this.Initialize = function()
	{
		var self = this

		$( document ).ready(function() {

			self.Hide()			

			ActionMark = new Mark("div.main");

			$("#findinput").keyup(function(event){
				if(LastSearch != $("#findinput").val())
				{
					ScrollSearchId = -1;
					LastSearch = $("#findinput").val()
					self.Search(LastSearch)
				}
				event.stopPropagation();			
			})


			$("#findinput").keydown(function(event){
				event.stopPropagation();			
			})


			$("#findinput").keypress(function(event){
				event.stopPropagation();			
			})


		    $("#findbutton").click(function(){
				self.Show()			
			})


			$("#findhide").click(function(){
				self.Hide()
			})

			$("#findnext").click(function(){
				self.FindNext(true)
			})

			$("#findprev").click(function(){
				self.FindNext(false)
			})
		});
		
		

	}

	this.FindNext = function(next)
	{
		var search = $("#findinput").val().toLowerCase();
		
		if(search.length == 0)
			return

		var function_name = _GobalModel.get("function_name")

		var found = false
		var nextok = false
		var anything = false
		var task;

		//Find where to search first

		if(ScrollSearchId == -1)
		{
			if(function_name == "Main" && GetFirstNotFunctionId() == 0)
			{
				anything = true
			}

			task = FindTaskById(0)

			while(true)
			{
				if(!task)
					break
			
				var id = parseInt(task.get("id"))
				var funcdata = GetFunctionData(id)

				if(anything && !IsFunctionNode(id) && id != 0)
				{
					found = true
					break	
				}

				if(id != 0 && (funcdata["id"] == 0 && function_name == "Main" ))
				{
					found = true
					break
				}

				if(function_name != "Main" && funcdata["name"] == function_name)
				{
					nextok = true
				}


				if(function_name != "Main" && !IsFunctionNode(id) && nextok)
				{
					found = true
					break	
				}
				if(next)
					task = FindNextTask(id)
				else
					task = FindPrevTask(id)
			}
			if(!found)
			{
				ScrollSearchId = -1
				return
			}
		}else
		{
			task = FindTaskById(ScrollSearchId)
		}

		if(!task)
		{
			ScrollSearchId = -1
			return
		}

		var id = parseInt(task.get("id"))
		ScrollSearchId = id
		found = false
		var total = 0;
		
		while(true)
		{
			
			if(!task)
			{
				task = FindTaskById(0)
			}
		
			var id = parseInt(task.get("id"))
			var funcdata = GetFunctionData(id)

			var searchcurrent = task.search().join(" , ").toLowerCase();

			if(searchcurrent.indexOf(search) >= 0 && !IsFunctionNode(id))
			{
				BrowserAutomationStudio_UnfoldParents(id)
				BrowserAutomationStudio_FocusAction(id)


				var i = id
				while(true)
				{
					if(next)
						t = FindNextTask(i)
					else
						t = FindPrevTask(i)
					if(!t)
					{
						ScrollSearchId = 0
						break;
					}
					i = parseInt(t.get("id"))
					if(!IsFunctionNode(i))
					{
						ScrollSearchId = i
						break	
					}
				}

				found = true
				break	
			}

			if(total >= _TaskCollection.models.length)
			{
				ScrollSearchId = -1
				found = false
				break
			}
			total += 1
			

			if(next)
				task = FindNextTask(id)
			else
				task = FindPrevTask(id)
		}
	}

	this.Show = function()
	{
		LastShow = true
		$(".findtoolbox").show()
		$("#findbutton").hide()
		$("#paddinfind").show()
		$("#findinput").focus()
		$("#findinput").select();

		$("#container").addClass("containerwithfind")
		this.SearchLast()

	}

	this.Search = function(search)
	{
		if(ActionMark)
		{
			ActionMark.unmark();
			if(search.length > 0)
				ActionMark.mark(search, {"separateWordSearch": false});
			else
				ActionMark.unmark();
		}
	}
	this.SearchLast = function()
	{
		this.Search(LastSearch);
	}

	this.Hide = function()
	{
		LastShow = false
		$(".findtoolbox").hide()
		$("#findbutton").show()
		$("#paddinfind").hide()

		$("#container").removeClass("containerwithfind")
		this.Search("")
	}

}