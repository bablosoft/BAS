var Id = GetInputConstructorValue("Id", loader);
var X = GetInputConstructorValue("X", loader);
var Y = GetInputConstructorValue("Y", loader);
var R = this.$el.find("#R").val().toUpperCase();
var G = this.$el.find("#G").val().toUpperCase();
var B = this.$el.find("#B").val().toUpperCase();
var A = this.$el.find("#A").val().toUpperCase();


if(Id["original"].length == 0)
{
  Invalid("Id is empty");
  return;
}

if(X["original"].length == 0)
{
  Invalid("X is empty");
  return;
}

if(Y["original"].length == 0)
{
  Invalid("Y is empty");
  return;
}

if(R.length == 0)
{
  Invalid("R is empty");
  return;
}

if(G.length == 0)
{
  Invalid("G is empty");
  return;
}
if(B.length == 0)
{
  Invalid("B is empty");
  return;
}
if(A.length == 0)
{
  Invalid("A is empty");
  return;
}


 try{
  var code = loader.GetAdditionalData() + _.template($("#imageprocessinggetpixel_code").html())({id: Id["updated"],x: X["updated"],y: Y["updated"],variable_r: "VAR_" + R,variable_g: "VAR_" + G,variable_b: "VAR_" + B,variable_a: "VAR_" + A})
  code = Normalize(code,0)
  BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e)
{}