function ResourceLoader()
{
  var AdditionalData = "";
  var IsString = true;
  var IsPrerender = false;

  this.je = function(data)
  {
    return data
    .replace(new RegExp("\\\\","g"),"\\u005c")
    .replace(new RegExp("<","g"),"\\u003c")
    .replace(new RegExp(">","g"),"\\u003e")
    .replace(new RegExp("\"","g"),"\\u0022")
    .replace(new RegExp("'","g"),"\\u0027")
    .replace(new RegExp("&","g"),"\\u0026")
    .replace(new RegExp("\\n","g"),"\\n")
    .replace(new RegExp("\\r","g"),"\\r")
  };



  this.Resolve = function(str)
  {
    var res = this.ResolveResources(str);
    //res = this.ResolveVariables(res);
    return res;
  }

  this.SetIsString = function(value)
  {
    IsString = value;
  }

  this.SetIsPrerender = function(value)
  {
    IsPrerender = value;
  }

  this.ResolveVariables = function(str)
  {
    var res = "";
    var reg = new RegExp("\\[\\[([^\\]]+)\\]\\]")
    var rest = str
    var all = ""
    while(true)
    {
      all = res
      if(res.length > 0 && rest.length > 0)
        all += ((IsString) ? " + " : "")

      if(rest.length > 0)
        all += ((IsString) ? "\"" : "") + ((IsString) ? this.je(rest) : rest) + ((IsString) ? "\"" : "")

      var match = reg.exec(rest)
      if(!match)
        break;

      var i = match.index
      var resnew = "";
      if(i>0)
      {
        resnew += (IsString) ? "\"" : ""
        resnew += (IsString) ? this.je(rest.substr(0,i)) : rest.substr(0,i)
        resnew += (IsString) ? "\" + " : ""
      }

      if(IsPrerender)
        resnew += match[0]
      else
        resnew += "VAR_" + match[1]


      i = match.index + match[0].length
      var j = rest.length - i
      if(j>0)
      {
        rest = rest.substr(i,j)
      }else
        rest = ""

      if(res.length == 0)
        res = resnew
      else
        res +=  ((IsString) ? " + " : "") + resnew


    }
    return all;
  }

  this.ResolveResources = function(str)
  {
    var res = "";
    var reg = new RegExp("\\{\\{([^\\}]+)\\}\\}")
    var rest = str
    var all = ""
    while(true)
    {
      all = res
      if(res.length > 0 && rest.length > 0)
        all += ((IsString) ? " + " : "")

      if(rest.length > 0)
        all += this.ResolveVariables(rest)

      var match = reg.exec(rest)
      if(!match)
        break;
      var Iteration = Math.floor(Math.random() * (999999 - 100000) + 100000)

      var v = "RESOURCE_" + Iteration;
      var m = match[1].split("|")[0]
      var notreuse = match[1].indexOf("|notreuse")>=0
      var onlyfail = match[1].indexOf("|onlyfail")>=0

      var rtemp = "RS(\"resource\", notreuse, onlyfail)!\n" + 
      "variable = _result().get()\n"

      AdditionalData +=  rtemp.replace("resource",this.je(m)).replace("variable",v).replace("notreuse",notreuse).replace("onlyfail",onlyfail)

      var i = match.index
      var resnew = "";
      if(i>0)
      {
        resnew += this.ResolveVariables(rest.substr(0,i))
        resnew += ((IsString) ? " + " : "")
      }

      if(IsPrerender)
        resnew += match[0]
      else
        resnew += v

      i = match.index + match[0].length
      var j = rest.length - i
      if(j>0)
      {
        rest = rest.substr(i,j)
      }else
        rest = ""

      if(res.length == 0)
        res = resnew
      else
        res +=  ((IsString) ? " + " : "") + resnew


    }
    return all;
  }

  this.GetAdditionalData = function()
  {
    return AdditionalData;
  }

}

function _template(template,callback)
{
  var loader = new ResourceLoader()
  var main = loader.Resolve(template)
  var res = loader.GetAdditionalData() + "\n_set_result(" + main + ")\n" + _get_function_body(callback)
  eval(_preprocess(res))
}