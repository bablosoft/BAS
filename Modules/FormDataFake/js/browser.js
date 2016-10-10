(function(append,set) {
    FormData.prototype.BlobToBase64 = function(blob)
    {
           var res = URL.createObjectURL(blob)
           var request = new XMLHttpRequest();
           request.open('GET', res, false);
           request.overrideMimeType("text/plain; charset=x-user-defined");
           request.send();

           res = "BrowserAutomationStudioBase64DataStart" + (function base64Encode(str) {
            var CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
            var out = "", i = 0, len = str.length, c1, c2, c3;
            while (i < len) {
                c1 = str.charCodeAt(i++) & 0xff;
                if (i == len) {
                    out += CHARS.charAt(c1 >> 2);
                    out += CHARS.charAt((c1 & 0x3) << 4);
                    out += "==";
                    break;
                }
                c2 = str.charCodeAt(i++);
                if (i == len) {
                    out += CHARS.charAt(c1 >> 2);
                    out += CHARS.charAt(((c1 & 0x3)<< 4) | ((c2 & 0xF0) >> 4));
                    out += CHARS.charAt((c2 & 0xF) << 2);
                    out += "=";
                    break;
                }
                c3 = str.charCodeAt(i++);
                out += CHARS.charAt(c1 >> 2);
                out += CHARS.charAt(((c1 & 0x3) << 4) | ((c2 & 0xF0) >> 4));
                out += CHARS.charAt(((c2 & 0xF) << 2) | ((c3 & 0xC0) >> 6));
                out += CHARS.charAt(c3 & 0x3F);
            }
            return out;
          })(request.responseText) + "BrowserAutomationStudioBase64DataEnd"
          return res;
    }

    FormData.prototype.append = function()
    {
        if(arguments.length > 1 && arguments[1] instanceof Blob && !(arguments[1] instanceof File))
        {
          arguments[1] = this.BlobToBase64(arguments[1])
        }
      return append.apply(this, arguments);
    };
    FormData.prototype.set = function()
    {
        if(arguments.length > 1 && arguments[1] instanceof Blob && !(arguments[1] instanceof File))
        {
          arguments[1] = this.BlobToBase64(arguments[1])
        }
      return set.apply(this, arguments);
    };
})(FormData.prototype.append,FormData.prototype.set);