if(<%= variable %>.length > 0)
{
	<%= variable_result %> = (<%= variable %>)[<%= variable %>.length - 1];
	<% if(remove){ %>
		<%= variable %>.splice(<%= variable %>.length - 1,1)
	<% } %>
}else
{
	<%= variable_result %> = null;
}