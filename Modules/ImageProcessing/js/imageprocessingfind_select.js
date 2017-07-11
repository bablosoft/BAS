var Id1 = GetInputConstructorValue("Id1", loader);
var Id2 = GetInputConstructorValue("Id2", loader);
var X = this.$el.find("#X").val().toUpperCase();
var Y = this.$el.find("#Y").val().toUpperCase();
var Threshold = this.$el.find("#Threshold").val().toUpperCase();


if(Id1["original"].length == 0)
{
  Invalid("Id1 is empty");
  return;
}

if(Id2["original"].length == 0)
{
  Invalid("Id2 is empty");
  return;
}

if(X.length == 0)
{
  Invalid("X is empty");
  return;
}

if(Y.length == 0)
{
  Invalid("Y is empty");
  return;
}

if(Threshold.length == 0)
{
  Invalid("Threshold is empty");
  return;
}


 try{
  var code = loader.GetAdditionalData() + _.template($("#imageprocessingfind_code").html())({id1: Id1["updated"],id2: Id2["updated"],x: "VAR_" + X,y: "VAR_" + Y,threshold: "VAR_" + Threshold})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}