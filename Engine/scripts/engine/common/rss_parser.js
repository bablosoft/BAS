function rss_item_parse(item)
{
    if(item.indexOf("<rss") >= 0)
        return null;


    var i = item.replace("<![CDATA[","").replace("]]>","");

    var link = "";
    var title = "";
    var m = i.match(/<link>\s*(.*?)\s*<\/link>/);
    if(m)
        link = m[1]

    m = i.match(/<title>\s*(.*?)\s*<\/title>/);
    if(m)
        title = m[1]


    if(link.length>0 && title.length>0)
        return {link:link,title:title}
    else
        return null;

}
