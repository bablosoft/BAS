<%= variable_result %> = (<%= variable %>)[0];
<% if(remove){ %>
	<%= variable %>.splice(0,1)
<% } %>