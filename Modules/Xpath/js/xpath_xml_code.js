html_parser_xpath_parse(<%= text %>)

if((<%= fail %>) && !html_parser_xpath_exist(<%= value %>))
	fail("Can't resolve query " + <%= value %>);

<%= variable %> = html_parser_xpath_xml(<%= value %>)
