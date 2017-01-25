(function(append,set) {
    
    FormData.prototype.BlobToUint8Array = function(blob)
    {
      var res = URL.createObjectURL(blob)
      var request = new XMLHttpRequest();
      request.open('GET', res, false);
      request.overrideMimeType("text/plain; charset=x-user-defined");
      request.send();

      var s = "BrowserAutomationStudioBase64DataStart" + blob.type + ";"
      var e = "BrowserAutomationStudioBase64DataEnd"
      
      var res = new Uint8Array(request.responseText.length + s.length + e.length);
      var ir = 0

      for(var i = 0;i<s.length;i++)
      {
        res[ir] = s.charCodeAt(i);ir++
      }

      for(var i = 0;i<request.responseText.length;i++)
      {
        res[ir] = request.responseText.charCodeAt(i);ir++
      }

      for(var i = 0;i<e.length;i++)
      {
        res[ir] = e.charCodeAt(i);ir++
      }

      return res;
    }

    FormData.prototype.append = function()
    {
        if(arguments.length > 1 && arguments[1] instanceof Blob && !(arguments[1] instanceof File))
        {
          arguments[1] = this.BlobToUint8Array(arguments[1])
        }
      return append.apply(this, arguments);
    };

    FormData.prototype.set = function()
    {
        if(arguments.length > 1 && arguments[1] instanceof Blob && !(arguments[1] instanceof File))
        {
          arguments[1] = this.BlobToUint8Array(arguments[1])
        }
      return set.apply(this, arguments);
    };
})(FormData.prototype.append,FormData.prototype.set);


(function(send) {

    XMLHttpRequest.prototype.BlobToUint8Array = function(blob)
    {
      var res = URL.createObjectURL(blob)
      var request = new XMLHttpRequest();
      request.open('GET', res, false);
      request.overrideMimeType("text/plain; charset=x-user-defined");
      request.send();

      var s = "BrowserAutomationStudioBase64DataStart" + blob.type + ";"
      var e = "BrowserAutomationStudioBase64DataEnd"
      
      var res = new Uint8Array(request.responseText.length + s.length + e.length);
      var ir = 0

      for(var i = 0;i<s.length;i++)
      {
        res[ir] = s.charCodeAt(i);ir++
      }

      for(var i = 0;i<request.responseText.length;i++)
      {
        res[ir] = request.responseText.charCodeAt(i);ir++
      }

      for(var i = 0;i<e.length;i++)
      {
        res[ir] = e.charCodeAt(i);ir++
      }

      return res;
    }

    

    XMLHttpRequest.prototype.send = function()
    {
        if(arguments.length > 0 && arguments[0] instanceof Blob && !(arguments[0] instanceof File))
        {
          arguments[0] = this.BlobToUint8Array(arguments[0])
        }
        return send.apply(this, arguments);
    }

    
   
})(XMLHttpRequest.prototype.send);