<%= variable %> = (function(){var rs = []; var r = new RegExp(<%= regexp %>,"gm"); var s = <%= string %>; var m; var i = -1; while(m = r.exec(s)){if(i == m.index) break; i = m.index; rs.push((m.length>1) ? m[1] : m[0]);} return rs;})()

