function PreserveMainPosition()
{
	this.url = "main";
	this.scroll = 0
	this.search = ""

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
		this.search =  $("#searchinput").val();
	}

	this.RestoreState = function()
	{
		$("body").hide()
		var self = this
		setTimeout(function(){
			$("#searchinput").val(self.search);
			_MainView.searchinput()
        	$('.actions').scrollTop(self.scroll);
        	$("body").show()
          }, 1)
	}

}