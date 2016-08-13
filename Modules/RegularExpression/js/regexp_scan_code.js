<%= variable %> = (function(){var rs = []; var r = new RegExp(<%= regexp %>,"g"); var s = <%= string %>; var m; while(m = r.exec(s)){rs.push((m.length>1) ? m[1] : m[0]);} return rs;})()

