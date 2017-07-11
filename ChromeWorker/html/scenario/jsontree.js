
var JSONTree = (function() {

  var escapeMap = {
    '&': '&amp;',
    '<': '&lt;',
    '>': '&gt;',
    '"': '&quot;',
    '\'': '&#x27;',
    '/': '&#x2F;'
  };

  var defaultSettings = {
    indent: 2
  };

  var id = 0;
  var instances = 0;

  this.create = function(data, settings) {
    instances += 1;
    id = 0;
    return _span(_jsVal(data, 0, false), {class: 'jstValue'}) + 
    "<script>$('*[dataopen]').each(function(t,el){var id = $(el).attr('id');if(id.split('_')[2]!='0')JSONTree.toggle($(el).attr('id'));$(el).removeAttr('dataopen')})</script>"
  };

  var _escape = function(text) {
    return text.replace(/[&<>'"]/g, function(c) {
      return escapeMap[c];
    });
  };

  var _id = function() {
    return "jsontree_" + instances + '_' + id++;
  };

  var _jsVal = function(value, depth, indent) {
    if (value !== null) {
      var type = typeof value;
      switch (type) {
        case 'boolean':
          return _jsBool(value, indent ? depth : 0);
        case 'number':
          return _jsNum(value, indent ? depth : 0);
        case 'string':
          return _jsStr(value, indent ? depth : 0);
        default:
          if (value instanceof Array) {
            return _jsArr(value, depth, indent);
          } else {
            return _jsObj(value, depth, indent);
          }
      }
    } else {
      return _jsNull(indent ? depth : 0);
    }
  };

  var _jsObj = function(object, depth, indent) {
    var id = _id();
    var content = Object.keys(object).sort(function(a,b){
      var a = a.toUpperCase()
      var b = b.toUpperCase()
      if(a.indexOf("GLOBAL:") == 0 && b.indexOf("GLOBAL:") == 0 || a.indexOf("GLOBAL:") < 0 && b.indexOf("GLOBAL:") < 0)
      {
        if (a > b) {
          return 1;
        }
        if (a < b) {
          return -1;
        }
        return 0
      }

      if(a.indexOf("GLOBAL:") == 0 && b.indexOf("GLOBAL:") < 0)
      {
        return true
      }

      if(a.indexOf("GLOBAL:") < 0 && b.indexOf("GLOBAL:") == 0)
      {
        return false
      }

      return true;

    })

    content = content.map(function(property) {
      return _property(property, object[property], depth + 1, true);
    }).join(_comma());

    

    var body = [
      _openBracket('{', indent ? depth : 0, id),
      _span(content, {id: id, dataopen: "true"}),
      _closeBracket('}', depth)
    ].join('\n');
    return _span(body, {})
  };

  var _jsArr = function(array, depth, indent) {
    var id = _id();
    var body = array.map(function(element) {
      return _jsVal(element, depth + 1, true);
    }).join(_comma());
    var arr = [
      _openBracket('[', indent ? depth : 0, id),
      _span(body, {id: id, dataopen: "true"}),
      _closeBracket(']', depth)
    ].join('\n');
    return arr;
  };

  var _jsStr = function(value, depth) {
    var cut = _cut(value)
    var id = _id()
    var clip = ""
    if(cut["cut"])
    {
      clip = " <i class='fa fa-plus-circle' aria-hidden='true' style='cursor:pointer' onclick='$(\"#" + id + "\").text(b64_to_utf8(" + _quote(utf8_to_b64(_quote(value))) + "));$(this).hide()'></i>"
      //clip = " <i class='fa fa-plus-circle' aria-hidden='true' style='cursor:pointer' onclick='alert(\"" + id + "\");document.getElementById(" + id + ").innerHTML=\"jgjg\"'></i>"
    }
    return _span(_indent(_quote(_escape(cut["data"])), depth), {class: 'jstStr',id: id}) + clip;
  };

  var _jsNum = function(value, depth) {
    return _span(_indent(value, depth), {class: 'jstNum'});
  };

  var _jsBool = function(value, depth) {
    return _span(_indent(value, depth), {class: 'jstBool'});
  };

  var _jsNull = function(depth) {
    return _span(_indent('null', depth), {class: 'jstNull'});
  };

  var _property = function(name, value, depth) {
    var property = _indent(_escape(name) + ': ', depth);
    var propertyValue = _span(_jsVal(value, depth, false), {});
    return _span(property + propertyValue, {class: 'jstProperty'});
  }

  var _quote = function(value) {
    return '"' + value + '"';
  }

  var _cut = function(value) {
    return {data: (value.length > 100) ? value.substr(0,97) + "..." : value, cut: value.length > 100};
  }

  var _comma = function() {
    return _span(',\n', {class: 'jstComma'});
  }

  var _span = function(value, attrs) {
    return _tag('span', attrs, value);
  }

  var _tag = function(tag, attrs, content) {
    return '<' + tag + Object.keys(attrs).map(function(attr) {
          return ' ' + attr + '="' + attrs[attr] + '"';
        }).join('') + '>' +
        content +
        '</' + tag + '>';
  }

  var _openBracket = function(symbol, depth, id) {
    return (
    _span(_indent(symbol, depth), {class: 'jstBracket'}) +
    _span('', {class: 'jstFold', onclick: 'JSONTree.toggle(\'' + id + '\')'})
    );
  }

  this.toggle = function(id) {
    var element = document.getElementById(id);
    var parent = element.parentNode;
    var toggleButton = element.previousElementSibling;
    if (element.className === '') {
      element.className = 'jstHiddenBlock';
      parent.className = 'jstFolded';
      toggleButton.className = 'jstExpand';
    } else {
      element.className = '';
      parent.className = '';
      toggleButton.className = 'jstFold';
    }
  }

  var _closeBracket = function(symbol, depth) {
    return _span(_indent(symbol, depth), {});
  }

  var _indent = function(value, depth) {
    return Array((depth * 2) + 1).join(' ') + value;
  };

  return this;
})();
