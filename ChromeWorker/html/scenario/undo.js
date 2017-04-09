function UndoManager()
{
	this.MaxDataLength = 15
	this.Data = []
	this.DataIndex = 0
	this.CanUndo = function()
	{
		return this.DataIndex > 0 && this.Data.length > 1
	}

	this.CanRedo = function()
	{
		return this.DataIndex < this.Data.length - 1 && this.Data.length > 1
	}

	this.Save = function(data)
	{
		if(this.DataIndex < this.Data.length && this.DataIndex >= 0 && this.Data[this.DataIndex] == data)
			return;

		this.Data = this.Data.splice(0,this.DataIndex + 1)
		this.Data.push(data)

		if(this.Data.length > this.MaxDataLength)
		{
			this.Data = this.Data.slice(this.Data.length - this.MaxDataLength)
		}

		this.DataIndex = this.Data.length - 1

		if(this.DataIndex < 0)
			this.DataIndex = 0

		//alert("Added data to undo manager " + this.Data.length + ":" + this.DataIndex)

	}

	this.Undo = function()
	{
		if(!this.CanUndo())
			return "";

		if(this.Data.length == 0)
			return ""

		this.DataIndex--;

		if(this.DataIndex >= this.Data.length)
			this.DataIndex = this.Data.length - 1

		if(this.DataIndex < 0)
			this.DataIndex = 0

		//alert("Undo " + this.Data.length + ":" + this.DataIndex)

		return this.Data[this.DataIndex]

	}

	this.Redo = function()
	{
		if(!this.CanRedo())
			return "";

		if(this.Data.length == 0)
			return ""

		this.DataIndex++;

		if(this.DataIndex >= this.Data.length)
			this.DataIndex = this.Data.length - 1

		if(this.DataIndex < 0)
			this.DataIndex = 0

		//alert("Redo " + this.Data.length + ":" + this.DataIndex)

		return this.Data[this.DataIndex]

	}
}