<%= variable_result %> = (<%= variable %>)[<%= index %>];
<% if(remove){ %>
	<%= variable %>.splice(<%= index %>,1)
<% } %>