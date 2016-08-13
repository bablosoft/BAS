{
	var r = Math.floor(Math.random() * (<%= variable %>.length));
	<%= variable_result %> = (<%= variable %>)[r];
	<% if(remove){ %>
		<%= variable %>.splice(r,1)
	<% } %>
}