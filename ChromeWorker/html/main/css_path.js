(function() {
    var t, e, n = [].indexOf || function(t) {
        for (var e = 0, n = this.length; n > e; e++)
            if (e in this && this[e] === t) return e;
        return -1
    };
    t = function() {
        function t(t) {
            null == t && (t = {}), this.options = {}, this.setOptions(this.default_options), this.setOptions(t)
        }
        return t.prototype.default_options = {
            selectors: ["id", "class", "tag", "nthchild"]
        }, t.prototype.setOptions = function(t) {
            var e, n, r;
            null == t && (t = {}), n = [];
            for (e in t) r = t[e], this.default_options.hasOwnProperty(e) ? n.push(this.options[e] = r) : n.push(void 0);
            return n
        }, t.prototype.isElement = function(t) {
            return !(1 !== (null != t ? t.nodeType : void 0))
        }, t.prototype.getParents = function(t) {
            var e, n;
            if (n = [], this.isElement(t))
                for (e = t; this.isElement(e);) n.push(e), e = e.parentNode;
            return n
        }, t.prototype.getTagSelector = function(t) {
            return this.sanitizeItem(t.tagName.toLowerCase())
        }, t.prototype.sanitizeItem = function(t) {
            var e, isfirst = true;
            var res = t.split("").map(function(t) {
                var isfirstcopy = isfirst;
                isfirst = false;
                return (":" === t || (isfirstcopy && /[^A-Za-z]/.test(t))) ? "\\" + t.charCodeAt(0).toString(16).toUpperCase() + " " 
                    : (/[ !"#$%&'()*+,.\/;<=>?@\[\\\]^`{|}~]/.test(t)) ? "\\" + t : escape(t).replace(/\%/g, "\\")
            });
            res = res.join("")
            return res;
        }, t.prototype.getIdSelector = function(t) {
            var e, n;
            return e = t.getAttribute("id"), null == e || "" === e || /\s/.exec(e) || (n = "#" + this.sanitizeItem(e), 1 !== document.querySelectorAll(n).length) ? null : n
        }, t.prototype.getClassSelectors = function(t) {
            var e, n, r;
            return r = [], e = t.getAttribute("class"), null != e && (e = e.replace(/\s+/g, " "), e = e.replace(/^\s|\s$/g, ""), "" !== e && (r = function() {
                var t, r, o, i;
                for (o = e.split(/\s+/), i = [], t = 0, r = o.length; r > t; t++) n = o[t], i.push("." + this.sanitizeItem(n));
                return i
            }.call(this))), r
        }, t.prototype.getAttributeSelectors = function(t) {
            var e, r, o, i, s, l, u;
            for (u = [], r = ["id", "class"], s = t.attributes, o = 0, i = s.length; i > o; o++) e = s[o], l = e.nodeName, n.call(r, l) < 0 && u.push("[" + e.nodeName + "=" + e.nodeValue + "]");
            return u
        }, t.prototype.getNthChildSelector = function(t) {
            var e, n, r, o, i, s;
            if (o = t.parentNode, null != o)
                for (e = 0, s = o.childNodes, n = 0, r = s.length; r > n; n++)
                    if (i = s[n], this.isElement(i) && (e++, i === t)) return ":nth-child(" + e + ")";
            return null
        }, t.prototype.testSelector = function(t, e) {
            var n, r;
            return n = !1, null != e && "" !== e && (r = t.ownerDocument.querySelectorAll(e), 1 === r.length && r[0] === t && (n = !0)), n
        }, t.prototype.getAllSelectors = function(t) {
            var e;
            return e = {
                t: null,
                i: null,
                c: null,
                a: null,
                n: null
            }, n.call(this.options.selectors, "tag") >= 0 && (e.t = this.getTagSelector(t)), n.call(this.options.selectors, "id") >= 0 && (e.i = this.getIdSelector(t)), n.call(this.options.selectors, "class") >= 0 && (e.c = this.getClassSelectors(t)), n.call(this.options.selectors, "attribute") >= 0 && (e.a = this.getAttributeSelectors(t)), n.call(this.options.selectors, "nthchild") >= 0 && (e.n = this.getNthChildSelector(t)), e
        }, t.prototype.testUniqueness = function(t, e) {
            var n, r;
            return r = t.parentNode, n = r.querySelectorAll(e), 1 === n.length && n[0] === t
        }, t.prototype.testCombinations = function(t, e, n) {
            var r, o, i, s, l, u, c;
            for (u = this.getCombinations(e), o = 0, s = u.length; s > o; o++)
                if (r = u[o], this.testUniqueness(t, r)) return r;
            if (null != n)
                for (c = e.map(function(t) {
                        return n + t
                    }), i = 0, l = c.length; l > i; i++)
                    if (r = c[i], this.testUniqueness(t, r)) return r;
            return null
        }, t.prototype.getUniqueSelector = function(t) {
            var e, n, r, o, i, s;
            for (s = this.getAllSelectors(t), o = this.options.selectors, n = 0, r = o.length; r > n; n++) switch (i = o[n]) {
                case "id":
                    if (null != s.i) return s.i;
                    break;
                case "tag":
                    if (null != s.t && this.testUniqueness(t, s.t)) return s.t;
                    break;
                case "class":
                    if (null != s.c && 0 !== s.c.length && (e = this.testCombinations(t, s.c, s.t))) return e;
                    break;
                case "attribute":
                    if (null != s.a && 0 !== s.a.length && (e = this.testCombinations(t, s.a, s.t))) return e;
                    break;
                case "nthchild":
                    if (null != s.n) return s.n
            }
            return "*"
        }, t.prototype.getSelector = function(t) {
            var e, n, r, o, i, s, l, u, c, a;
            for (e = [], l = this.getParents(t), r = 0, i = l.length; i > r; r++) n = l[r], c = this.getUniqueSelector(n), null != c && e.push(c);
            for (a = [], o = 0, s = e.length; s > o; o++)
                if (n = e[o], a.unshift(n), u = a.join(" > "), this.testSelector(t, u)) return u;
            return null
        }, t.prototype.getCombinations = function(t) {
            var e, n, r, o, i, s, l;
            for (null == t && (t = []), l = [
                    []
                ], e = r = 0, i = t.length - 1; i >= 0 ? i >= r : r >= i; e = i >= 0 ? ++r : --r) {
                for (n = o = 0, s = l.length - 1;
                    (s >= 0 ? s >= o : o >= s) && (l.push(l[n].concat(t[e])), !(l.length > 1e3)); n = s >= 0 ? ++o : --o);
                if (l.length > 1e3) break
            }
            return l.shift(), l = l.sort(function(t, e) {
                return t.length - e.length
            }), l = l.map(function(t) {
                return t.join("")
            })
        }, t
    }(), ("undefined" != typeof define && null !== define ? define.amd : void 0) ? define([], function() {
        return t
    }) : (e = "undefined" != typeof exports && null !== exports ? exports : this, e.CssSelectorGenerator = t)
}).call(this);