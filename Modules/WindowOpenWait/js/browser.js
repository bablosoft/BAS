window.BrowserAutomationStudio_Open = window.open;
window.open = function(u,n,d,r)
{
  BrowserAutomationStudio_Sleep(100);
  return window.BrowserAutomationStudio_Open(u,n,d,r);
}



