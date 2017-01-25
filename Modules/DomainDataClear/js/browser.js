(function(){
	var parser = document.createElement('a'), searchObject = {}, queries, split, i;
	parser.href = window.location.href;
	queries = parser.search.replace(/^\?/, '').split('&');
	for( i = 0; i < queries.length; i++ ) {
		split = queries[i].split('=');
		searchObject[split[0]] = split[1];
	}
	var url = parser.protocol + "//" +  parser.host + ((parser.port.length > 0) ? ":" + parser.port : "")
	if(BrowserAutomationStudio_DomainDataNeedClear(url))
	{
		try{
		localStorage.clear()}catch(e){}
	}
})();
