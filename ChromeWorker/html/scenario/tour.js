function BrowserAutomationStudio_Tour()
{
	var AlreadyDone = false;
	this.Start = function()
	{
		if(typeof(_DoTour) == "undefined" || _DoTour == false)
		{
			AlreadyDone = true
			return
		}


		if(AlreadyDone)
			return;



		var tour = new Tour({
			steps: 
			[
				{
					element: "#runproperties",
					title: tr("Task repetitions."),
					content: tr("Set success and fail number to big values if you want to repeat script several times with different data."),
					placement: "bottom",
					backdrop: false
					
					
				},
				{
					element: ".toolinsertdata:has(.toolselected)",
					title: tr("Insert indicator."),
					content: tr("This is insert indicator, new actions will be added here. You can shift indicator before adding new actions or move them later."),
					placement: "right",
					backdrop: true
				},
				{
					element: "#debugbuttoncontainer",
					title: tr("Variables list."),
					content: tr("Click here to see variables list and values."),
					placement: "left",
					backdrop: true
				},
			
			],
			smartPlacement: false,
			onShown: function()
					{
						$("*[data-role=prev]").html('<i class="fa fa-arrow-left" aria-hidden="true"></i>')
						$("*[data-role=next]").html('<i class="fa fa-arrow-right" aria-hidden="true"></i>')
						$("*[data-role=end]").html(tr("Skip"))
					},
		});
		
		tour.init();
		tour.start();
		AlreadyDone = true;
	}


}
