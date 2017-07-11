function PreserveMainPosition()
{
	this.url = "main";
	this.scroll = 0
	this.group = ""
	this.tab = ""

	this.BeforUrlChanged = function(url)
	{
		if(this.url != url && this.url == "main")
		{
			this.SaveState()
		}
	}

	this.AfterUrlChanged = function(url)
	{
		if(this.url != url && url == "main")
		{
			this.RestoreState()
		}
		this.url = url;
	}


	this.SaveState = function()
	{
		this.scroll = $(".actions").scrollTop();
		this.group = CurrentGroup 
		this.tab = CurrentTab 
	}

	this.RestoreState = function()
	{
		$("body").hide()
		var self = this
		setTimeout(function(){
			
			try
			{
				if(self.group.length == 0)
	        	{
	        		BrowserAutomationStudio_ReturnToMainFunction();
	        	}else
	        	{
	        		BrowserAutomationStudio_GotoGroup(self.group);
	        	}
			}catch(e)
			{
				
			}
			
			

        	CurrentTab = ""

        	if(self.tab == "history")
        	{
        		BrowserAutomationStudio_ShowHideHistory();
        	}else if (self.tab == "bookmarks")
        	{
        		BrowserAutomationStudio_RenderBookmarks();
        	}

        	$('.actions').scrollTop(self.scroll);
        	$("body").show()
        	
          }, 1)
	}

}