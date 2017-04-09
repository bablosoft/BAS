(function(append,set) {

    FormData.prototype.MakeAttachment = function(blob, filename)
    {
      var id = Math.floor(Math.random() * (1000000)) + 1
      var reader = new FileReader();
      reader.onload = function() {
        var dataUrl = reader.result;
        var filename_string = ""
        if(filename)
        {
          filename_string = filename.toString()
        }
        var base64 = dataUrl.split(',')[1]
        BrowserAutomationStudio_SaveBlob(id, base64, blob.type, filename_string);
      };
      reader.readAsDataURL(blob);
      return new TextEncoder("UTF-8").encode("BrowserAutomationStudioAttachmentStart" + id + "BrowserAutomationStudioAttachmentEnd");
    }

    FormData.prototype.append = function()
    {
        if(arguments.length > 1 && arguments[1] instanceof Blob && !(arguments[1] instanceof File))
        {
          arguments[1] = this.MakeAttachment(arguments[1],arguments[2])
          arguments = [arguments[0],arguments[1]]
        }
      return append.apply(this, arguments);
    };

    FormData.prototype.set = function()
    {
        if(arguments.length > 1 && arguments[1] instanceof Blob && !(arguments[1] instanceof File))
        {
          arguments[1] = this.MakeAttachment(arguments[1],arguments[2])
          arguments = [arguments[0],arguments[1]]
        }
      return set.apply(this, arguments);
    };
})(FormData.prototype.append,FormData.prototype.set);


(function(send) {

    XMLHttpRequest.prototype.MakeAttachment = function(blob)
    {
      var id = Math.floor(Math.random() * (1000000)) + 1
      var reader = new FileReader();
      reader.onload = function() {
        var dataUrl = reader.result;
        var base64 = dataUrl.split(',')[1]
        BrowserAutomationStudio_SaveBlob(id, base64, blob.type, "");
      };
      reader.readAsDataURL(blob);
      return new TextEncoder("UTF-8").encode("BrowserAutomationStudioAttachmentStart" + id + "BrowserAutomationStudioAttachmentEnd");
    }
    

    XMLHttpRequest.prototype.send = function()
    {
        if(arguments.length > 0 && arguments[0] instanceof Blob && !(arguments[0] instanceof File))
        {
          arguments[0] = this.MakeAttachment(arguments[0])
        }
        return send.apply(this, arguments);
    }

    
   
})(XMLHttpRequest.prototype.send);



(function(fetchOriginal) {

    var MakeAttachment = function(blob)
    {
      var id = Math.floor(Math.random() * (1000000)) + 1
      var reader = new FileReader();
      reader.onload = function() {
        var dataUrl = reader.result;
        var base64 = dataUrl.split(',')[1]
        BrowserAutomationStudio_SaveBlob(id, base64, blob.type, "");
      };
      reader.readAsDataURL(blob);
      return new TextEncoder("UTF-8").encode("BrowserAutomationStudioAttachmentStart" + id + "BrowserAutomationStudioAttachmentEnd");
    }
    

    window.fetch = function()
    {
        console.log(arguments)

        if(arguments.length > 1 && typeof(arguments[1]) == "object" && typeof(arguments[1]["body"]) == "object" && arguments[1]["body"] instanceof Blob)
        {
          arguments[1]["body"] = MakeAttachment(arguments[1]["body"])
        }
        return fetchOriginal.apply(window, arguments);
    }

    
   
})(window.fetch);