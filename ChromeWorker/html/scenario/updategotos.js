function UpdateGotos()
{
	try
	{
		var cache = {}
		var models = _TaskCollection.models
		var len = models.length
		for(var i = 0;i<len;i++)
		{
			var task = models[i]
			var code = task.get("code")
			if(code.indexOf("_goto(") >= 0)
			{
				code = code.split("_goto(")[1]
		        code = code.split(")!")[0]
		        var label = JSON.parse(code)
		        var parentid = task.get("parentid")
		        var parent_hash = {}

		        if(cache[parentid])
					parent_hash = cache[parentid]
				else
					cache[parentid] = parent_hash

				var label_hash = {is_set: false, "goto": []}

				if(parent_hash[label])
					label_hash = parent_hash[label]
				else
					parent_hash[label] = label_hash

				
				label_hash["goto"].push(task)

			}else if(code.indexOf("_set_goto_label(") >= 0)
			{
				code = code.split("_set_goto_label(")[1]
		        code = code.split(")!")[0]

		        var label = JSON.parse(code)
		        var parentid = task.get("parentid")
		        var parent_hash = {}

		        if(cache[parentid])
					parent_hash = cache[parentid]
				else
					cache[parentid] = parent_hash

				var label_hash = {is_set: false, "goto": []}

				if(parent_hash[label])
					label_hash = parent_hash[label]
				else
					parent_hash[label] = label_hash

				label_hash["is_set"] = true

			}
		}

		Object.keys(cache).forEach(function(parentId){
			var parent_hash = cache[parentId]

			Object.keys(parent_hash).forEach(function(label){
				var label_hash = parent_hash[label]
				var is_set = label_hash["is_set"]

				label_hash["goto"].forEach(function(task){
					if(is_set)
					{
						var code = task.get("code")
						code = code.replace(new RegExp("(\_fast)?\_goto\(.*?\)\!","g"),"_fast_goto(" + JSON.stringify(label) + ")!")
						task.attributes["code"] = code
					}else
					{
						var code = task.get("code")
						code = code.replace(new RegExp("(\_fast)?\_goto\(.*?\)\!","g"),"_goto(" + JSON.stringify(label) + ")!")
						task.attributes["code"] = code
					}

				})				
			})

		})
	}catch(e){}
	
}