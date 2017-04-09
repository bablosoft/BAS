function Filter()
{
	var Schema = null
	var self = this
	var TypePrev = ""
	var IdNext = 0
	var Models = []

	this.GetModels = function()
	{
		return Models;
	}

	this.RestoreModels = function(models)
	{
		Models = []
		models.forEach(function(model){
			IdNext += 1;
			model["id"] = IdNext


        	var text = self.GenerateModelText(model)
        	$("#database-filters-data")
        		.append($("<button type='button'></button>")
				.attr("model-id",model["id"])
				.attr("class","btn btn-default btn-sm filteritem")
				.attr("onclick","_Filter.RemoveFilter(this)")
				.text(text));	

			Models.push(model)

		})
		

	}

	this.GetFilters = function()
	{
		var res = Models.map(function(el){var res = [el["columnid"],el["type"]]; if(el["val"]){res.push(el["val"])} return res; });

		return res
	}


	this.Install = function(schema)
	{
		Schema = schema
		$( document ).ready(function() {
			self.InstallDocument()
		});

	}

	this.FilterTableInputChange = function()
	{
		try
		{
			$('#FilterFieldInput').html("")

			var columns = Schema.find(function(el){return el["id"] == $("#Table").val()})

			if(columns)
			{
				columns = columns["columns"]

				for(var i = 0;i<columns.length;i+=1)
				{
					$('#FilterFieldInput')
					.append($("<option></option>")
					.attr("value",columns[i]["id"])
					.text(columns[i]["description"]));	
				}

			}
		}catch(e)
		{

		}

		

	}

	this.FilterFieldInputChange = function()
	{

		try
		{
			var type = Schema.find(function(el){return el["id"] == $("#Table").val()})["columns"].find(function(el){return el["id"] == $("#FilterFieldInput").val()})["type"]
			if(type!=TypePrev)
			{
				$('#FilterTypeInput').html("")
				if(type == "string")
				{
					
					$('#FilterTypeInput')
					.append($("<option></option>")
					.attr("value","StringNotEmpty")
					.text(tr("Not empty")));	

					$('#FilterTypeInput')
					.append($("<option></option>")
					.attr("value","StringEmpty")
					.text(tr("Is empty")));	

					$('#FilterTypeInput')
					.append($("<option></option>")
					.attr("value","StringContains")
					.text(tr("Contains")));	

				}

				if(type == "int")
				{

				
					$('#FilterTypeInput')
					.append($("<option></option>")
					.attr("value","IntEquals")
					.text(tr("Equals")));	

					$('#FilterTypeInput')
					.append($("<option></option>")
					.attr("value","IntNotEquals")
					.text(tr("Not equals")));	

					$('#FilterTypeInput')
					.append($("<option></option>")
					.attr("value","IntGreaterOrEqual")
					.text(tr(">=")));	

					$('#FilterTypeInput')
					.append($("<option></option>")
					.attr("value","IntGreater")
					.text(tr(">")));	

					$('#FilterTypeInput')
					.append($("<option></option>")
					.attr("value","IntLessThan")
					.text(tr("<")));	

					$('#FilterTypeInput')
					.append($("<option></option>")
					.attr("value","IntLessThanOrEqual")
					.text(tr("<=")));	

				}

				if(type == "bool")
				{
					
					$('#FilterTypeInput')
					.append($("<option></option>")
					.attr("value","BoolIsTrue")
					.text(tr("Is true")));	

					$('#FilterTypeInput')
					.append($("<option></option>")
					.attr("value","BoolIsFalse")
					.text(tr("Is false")));	
					
				}

				if(type == "date")
				{

				
					$('#FilterTypeInput')
					.append($("<option></option>")
					.attr("value","DateIsLessThan")
					.text(tr("Earlier then")));	

					$('#FilterTypeInput')
					.append($("<option></option>")
					.attr("value","DateGreaterThan")
					.text(tr("Later then")));	

					$('#FilterTypeInput')
					.append($("<option></option>")
					.attr("value","DateIsSameYear")
					.text(tr("Same year")));	

					$('#FilterTypeInput')
					.append($("<option></option>")
					.attr("value","DateIsSameMonth")
					.text(tr("Same month")));	

					$('#FilterTypeInput')
					.append($("<option></option>")
					.attr("value","DateIsSameDay")
					.text(tr("Same day")));	

					$('#FilterTypeInput')
					.append($("<option></option>")
					.attr("value","DateIsSameHour")
					.text(tr("Same hour")));	

				}

				TypePrev = type
				self.FilterTypeInputChange();
			}
		}catch(e)
		{

		}
		
	}

	this.FilterTypeInputChange = function()
	{
		//alert("FilterTypeInputChange")
		
		try{
			var val = $("#FilterTypeInput").val()
			if(val)
			{
				if(["StringNotEmpty","StringEmpty","BoolIsTrue","BoolIsFalse"].indexOf(val) >=0 )
				{
					$("#FiledValueInput").hide()
				}else
				{
					$("#FiledValueInput").show()
				}
			}
		}catch(e)
		{

		}
		
	}


	

	this.InstallDocument = function()
	{
		
	}

	this.GenerateModelText = function(model)
	{
		try{
			var text = "";
			var table = Schema.find(function(el){return el["id"] == model["tableid"]})
			var column = table["columns"].find(function(el){return el["id"] == model["columnid"]})

			text += column["description"]
			text += " "



			if(model["type"] == "StringNotEmpty")
			{
				text += tr("Not empty")
			}
			if(model["type"] == "StringEmpty")
			{
				text += tr("Is empty")
			}
			if(model["type"] == "StringContains")
			{
				text += tr("Contains")
			}
			if(model["type"] == "IntEquals")
			{
				text += tr("Equals")
			}
			if(model["type"] == "IntNotEquals")
			{
				text += tr("Not equals")
			}
			if(model["type"] == "IntGreaterOrEqual")
			{
				text += tr(">=")
			}
			if(model["type"] == "IntGreater")
			{
				text += tr(">")
			}
			if(model["type"] == "IntLessThan")
			{
				text += tr("<")
			}
			if(model["type"] == "IntLessThanOrEqual")
			{
				text += tr("<=")
			}
			if(model["type"] == "BoolIsTrue")
			{
				text += tr("Is true")
			}
			if(model["type"] == "BoolIsFalse")
			{
				text += tr("Is false")
			}
			if(model["type"] == "DateIsLessThan")
			{
				text += tr("Earlier then")
			}
			if(model["type"] == "DateGreaterThan")
			{
				text += tr("Later then")
			}
			if(model["type"] == "DateIsSameYear")
			{
				text += tr("Same year")
			}
			if(model["type"] == "DateIsSameMonth")
			{
				text += tr("Same month")
			}
			if(model["type"] == "DateIsSameDay")
			{
				text += tr("Same day")
			}
			if(model["type"] == "DateIsSameHour")
			{
				text += tr("Same hour")
			}
			
			if(model["val"])
			{
				text += " "
				text += model["val"]
			}
			return text
		}catch(e)
		{
		}
		return ""

	}

	this.RemoveFilter = function(btn)
	{
        bootbox.confirm(tr("Remove this filter?"), function(res){
        	if(res)
        	{
				var modelid = $(btn).attr("model-id")
				$(".filteritem[model-id=" + modelid + "]").remove()
				Models = Models.filter(function(el){return el["id"] != modelid})
			}
        })
	}



	this.InstallEvents = function()
	{
		TypePrev = ""
		Models = []
		$("#database-filters-clear").click(function(){
			self.Clear()
		})

		$("#database-filters-add").click(function(){
			self.FilterTableInputChange()
			self.FilterFieldInputChange()
			self.FilterTypeInputChange()
			$("#filter-add").show()
			$("#action-add").hide()
		})

		self.FilterTableInputChange()
		self.FilterFieldInputChange()
		self.FilterTypeInputChange()

		$("#FilterFieldInput").change(function(){
			self.FilterFieldInputChange()
		})

		$("#FilterTypeInput").change(function(){
			self.FilterTypeInputChange()
		})


		$(".filterok").click(function(){

			IdNext += 1;

        	var model = {tableid:$("#Table").val(), columnid: $("#FilterFieldInput").val(), type:$("#FilterTypeInput").val(), id:IdNext}
			if(["StringNotEmpty","StringEmpty","BoolIsTrue","BoolIsFalse"].indexOf(model["type"]) < 0)
			{
				var loader = new ResourceLoader();
	        	loader.SetIsPrerender(true)
    	    	var Value = GetInputConstructorValue("Value",loader)["updated"]

				model["val"] = Value;
			}else
			{
				model["val"] = null;
			}

        	
        	var text = self.GenerateModelText(model)
        	$("#database-filters-data")
        		.append($("<button type='button'></button>")
				.attr("model-id",model["id"])
				.attr("class","btn btn-default btn-sm filteritem")
				.attr("onclick","_Filter.RemoveFilter(this)")
				.text(text));	

			Models.push(model)

			$("#filter-add").hide()
			$("#action-add").show()
		})
		$(".filtercancel").click(function(){
			$("#filter-add").hide()
			$("#action-add").show()
		})
	}
	this.Clear = function()
	{
		$("#database-filters-data").html("")
		Models = []
	}
}


